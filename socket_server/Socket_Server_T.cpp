/*===========================================================================*
 * Header Files
 *===========================================================================*/
#include "Socket_Server_T.hpp"
#include "SS_Client_T.hpp"
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/tcp.h>
#include <signal.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

/*===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/

#ifndef SS_MAX_LISTEN_CONNECTIONS
#   define SS_MAX_LISTEN_CONNECTIONS (128)
#endif

#ifndef SS_PSELECT_TIMEOUT_MS
#   define SS_PSELECT_TIMEOUT_MS (1000)
#endif

/*===========================================================================*
 * Local Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Local Type Declarations
 *===========================================================================*/

/*===========================================================================*
 * Exported Const Object Definitions
 *===========================================================================*/

/*===========================================================================*
 * Local Object Definitions
 *===========================================================================*/

/*===========================================================================*
 * Local Function Prototypes
 *===========================================================================*/

/*===========================================================================*
 * Local Inline Function Definitions and Function-Like Macros
 *===========================================================================*/

/*===========================================================================*
 * Function Definitions
 *===========================================================================*/

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * NOTE: For descriptions of class members, please refer to the comments in
 *       Socket_Server_T.hpp.
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

#define Tr_Cpp_Fault(msg) 		printf(#msg)
#define Tr_Cpp_Info_Lo(msg) 	printf(#msg)


Socket_Server_T::Socket_Server_T(unsigned short port_number,
                                 unsigned short secure_port_number,
                                 char const * log_file,
                                 size_t max_log_file_size)
                :m_accept_fd(-1),
                 m_clients_by_uid(),
                 m_pending_clients(),
                 m_secure_accept_fd(-1),
                 m_non_secure_connections_enabled(true),
                 m_bind_ip_address(INADDR_ANY)
{
}

Socket_Server_T::~Socket_Server_T()
{
}

void Socket_Server_T::accept_new_client(int accept_fd)
{
   Tr_Cpp_Info_Lo("Accepting...");
   struct sockaddr cli_addr;
   socklen_t cli_addr_sz = sizeof(cli_addr);
   /* Accept the connection from the client */
   int client_fd = accept(accept_fd, &cli_addr, &cli_addr_sz);
   /* If accept() failed, emit an error */
   if (client_fd < 0)
   {
      Tr_Cpp_Fault("Could not accept: " << strerror(errno));
   }
   else
   {
      Tr_Cpp_Info_Lo("Accepted on " << client_fd);
      // Configure FD to close on execve() and to not block
      if (fcntl(client_fd, F_SETFD, FD_CLOEXEC) != 0)
      {
         Tr_Cpp_Fault("Could not set FD_CLOEXEC on client FD: " << strerror(errno));
      }
      if (fcntl(client_fd, F_SETFL, O_NONBLOCK) != 0)
      {
         Tr_Cpp_Fault("Could not set O_NONBLOCK on client FD: " << strerror(errno));
      }
      int sock_opt = 1;
      if (setsockopt(client_fd, IPPROTO_TCP, TCP_NODELAY, &sock_opt, sizeof sock_opt) < 0)
      {
         Tr_Cpp_Fault("Could not set TCP_NODELAY: " << strerror(errno));
      }
      if (m_pending_clients[client_fd] != NULL)
      {
         Tr_Cpp_Fault("Second pending client with same FD: " << client_fd);
         delete m_pending_clients[client_fd];
      }
      if (accept_fd == m_secure_accept_fd) // This is an SSL connection
      {/*
         m_pending_clients[client_fd] = new SSL_Client_T(*this, client_fd);
         if(!m_pending_clients[client_fd]->Is_Connected())
         {
            delete m_pending_clients[client_fd];
            m_pending_clients.erase(client_fd);
         }*/
      }
      else // This is an unsecured connection
      {
         m_pending_clients[client_fd] = new SS_Client_T(*this, client_fd);
      }
   }
}

void Socket_Server_T::close_connection(int & accept_fd)
{
   if (accept_fd != -1)
   {
      if (shutdown(accept_fd, SHUT_RDWR) != 0)
      {
         Tr_Cpp_Fault("shutdown() FAILED: " << strerror(errno));
      }
      if (close(accept_fd) != 0)
      {
         Tr_Cpp_Fault("close() FAILED: " << strerror(errno));
      }
      accept_fd = -1;
   }
}

void Socket_Server_T::create_connection(unsigned short port_number, int & accept_fd)
{
   close_connection(accept_fd);

   while (accept_fd < 0)
   {
      /* Create a socket */
      accept_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

      /* If the socket could not be created, emit an error */
      if (accept_fd < 0)
      {
         Tr_Cpp_Fault("Could not open socket: " << strerror(errno));
      }
      else
      {
         /* Make a sockaddr for our port number, and any IP address */
         struct sockaddr_in socket_adr;
         int result = 0;
         int sock_opt = 1;

         Tr_Cpp_Info_Lo("accept_fd = " << accept_fd);
         /*
          * Allow SS address to be reused - gets rid of those "Address already in use"
          * errors if SS is killed and then re-started.
          */
         sock_opt = 1;
         result = setsockopt(accept_fd, SOL_SOCKET, SO_REUSEADDR, &sock_opt, sizeof sock_opt);
         if (result < 0)
         {
            Tr_Cpp_Fault("Could not set SO_REUSEADDR: " << strerror(errno));
         }

         result = setsockopt(accept_fd, IPPROTO_TCP, TCP_NODELAY, &sock_opt, sizeof sock_opt);
         if (result < 0)
         {
            Tr_Cpp_Fault("Could not set TCP_NODELAY: " << strerror(errno));
         }

         memset(&socket_adr, 0, sizeof(socket_adr));

         socket_adr.sin_family = AF_INET;
         socket_adr.sin_port = htons(port_number);
         socket_adr.sin_addr.s_addr = m_bind_ip_address;

         Tr_Cpp_Info_Lo("Binding...");

         /* Bind our socket to the sockaddr */
         result = bind(accept_fd, (struct sockaddr*) (&socket_adr), sizeof(socket_adr));

         /* If the binding failed, emit an error */
         if (result < 0)
         {
            Tr_Cpp_Fault("Could not bind address: " << strerror(errno));
            if (shutdown(accept_fd, SHUT_RDWR) != 0)
            {
               Tr_Cpp_Fault("shutdown(accept_fd) FAILED: " << strerror(errno));
            }
            close(accept_fd);
            accept_fd = -1;
         }
         else
         {
            int listen_result;
            // Configure FD to close on execve() and to not block
            if (fcntl(accept_fd, F_SETFD, FD_CLOEXEC) != 0)
            {
               Tr_Cpp_Fault("Could not set FD_CLOEXEC: " << strerror(errno));
            }
            if (fcntl(accept_fd, F_SETFL, O_NONBLOCK) != 0)
            {
               Tr_Cpp_Fault("Could not set O_NONBLOCK: " << strerror(errno));
            }

            Tr_Cpp_Info_Lo("Listening...");
            /* Listen for a new connection from a client */
            listen_result = listen(accept_fd, SS_MAX_LISTEN_CONNECTIONS);

            /* If listen() was not successful, emit an error */
            if (listen_result < 0)
            {
               Tr_Cpp_Fault("Could not listen: " << strerror(errno));
               if (shutdown(accept_fd, SHUT_RDWR) != 0)
               {
                  Tr_Cpp_Fault("shutdown(accept_fd) FAILED: " << strerror(errno));
               }
               if (close(accept_fd) != 0)
               {
                  Tr_Cpp_Fault("close(accept_fd) FAILED: " << strerror(errno));
               }
               accept_fd = -1;
            }
         } // (result < 0)

      } // if (accept_fd < 0)

      if (accept_fd < 0)
      {
         sleep(1); // try again in 1 second
      }
   } // while (accept_fd < 0)
}

void Socket_Server_T::Run()
{

   while(!m_exit_requested)
   {
      if(m_non_secure_connections_enabled)
      {
         create_connection(m_port_number, m_accept_fd); // doesn't return until valid m_accept_fd obtained
      }

      while (!m_exit_requested)
      {
         fd_set rd_set;
         fd_set wr_set;
         int select_result;

         int nfds = setup_read_set(&rd_set);
         {
         struct timespec select_timeout;

         select_timeout.tv_sec  = (SS_PSELECT_TIMEOUT_MS/1000);
         select_timeout.tv_nsec = (SS_PSELECT_TIMEOUT_MS % 1000) * 1000000;
         select_result = pselect(nfds + 1, &rd_set, &wr_set, NULL, &select_timeout, NULL);
         }

         /*
          * NOTE: ALL FDs that were added to the set must be checked.
          */
         if (-1 == select_result)
         {
            if (!m_exit_requested)
            {
               Tr_Cpp_Fault("pselect() FAILED: " << strerror(errno));
            }
            /****/
            break; // start all over upon failure of select
            /****/
         }
         // Check for new connections via m_accept_fd
         if ((m_accept_fd >= 0) && FD_ISSET(m_accept_fd, &rd_set) && m_non_secure_connections_enabled)
         {
            accept_new_client(m_accept_fd);
         }
         // Check for new connections via m_secure_accept_fd
         if ((m_secure_accept_fd >= 0) && FD_ISSET(m_secure_accept_fd, &rd_set))
         {
            accept_new_client(m_secure_accept_fd);
         }
      } // while (!m_exit_requested) !! NOTE: break; exists !!
   } // while (!m_exit_requested)
}

int Socket_Server_T::setup_read_set(fd_set* rd_set)
{
   int nfds = 0;
   SS_Client_T* client;

   FD_ZERO(rd_set);
   // Add FD for accepting new connections to rd_set
   if(m_non_secure_connections_enabled)
   {
      FD_SET(m_accept_fd, rd_set);
      nfds = MAX(nfds, m_accept_fd);
   }
   if (m_secure_accept_fd >= 0)
   {
      // Add FD for accepting new secure connections to rd_set
      FD_SET(m_secure_accept_fd, rd_set);
      nfds = MAX(nfds, m_secure_accept_fd);
   }
   // Add FDs for all active clients to rd_set
   std::map<uint32_t, SS_Client_T *>::iterator uid_it;
   for (uid_it = m_clients_by_uid.begin(); uid_it != m_clients_by_uid.end(); ++uid_it)
   {
      client = (*uid_it).second;
      int client_fd = client->Get_Socket_FD();
      FD_SET(client_fd, rd_set);
      nfds = MAX(nfds, client_fd);
   }
   // Add FDs for all pending clients to set
   std::map<int, SS_Client_T *>::iterator fd_it;
   for (fd_it = m_pending_clients.begin(); fd_it != m_pending_clients.end(); ++fd_it)
   {
      client = (*fd_it).second;
      int client_fd = client->Get_Socket_FD();
      FD_SET(client_fd, rd_set);
      nfds = MAX(nfds, client_fd);
   }
   return nfds;
}
