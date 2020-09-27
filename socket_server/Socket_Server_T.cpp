#include "Socket_Server_T.hpp"
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

#define Tr_Cpp_Fault(msg)
#define Tr_Cpp_Info_Lo(msg)


Socket_Server_T::Socket_Server_T(unsigned short port_number,
                                 unsigned short secure_port_number,
                                 char const * log_file,
                                 size_t max_log_file_size)
                :m_accept_fd(-1),
                 m_non_secure_connections_enabled(true),
                 m_bind_ip_address(INADDR_ANY)
{
}

Socket_Server_T::~Socket_Server_T()
{
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
      } // while (!m_exit_requested) !! NOTE: break; exists !!
   } // while (!m_exit_requested)
}
