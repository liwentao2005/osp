#ifndef SOCKET_SERVER_T_HPP
#   define SOCKET_SERVER_T_HPP
#   include "reuse.h"
#   include "SS_Client_T.hpp"
#   include <arpa/inet.h>
#   include <iostream>
#   include <map>
#   include <netinet/in.h>
#   include <sys/select.h>
#   include <sys/socket.h>



#define SS_FIVE_MEGABYTES (5242880)
/**
 * This is the primary class for creating and running a socket server.
 */
class Socket_Server_T
{
   public:

      /**
       * Constructs a Socket_Server_T object that accepts connections on the
       * specified port.
       *
       * @param port_number
       *   The port on which client connections will be accepted.
       * @param secure_port_number
       *   The port on which secure client connections will be accepted (0 to disable).
       * @param log_file Name of log file (defaults to SocketServer.log).
       * @param max_log_file_size Maximum size of log file (defaults to 5M)
       */
      Socket_Server_T(unsigned short port_number, unsigned short secure_port_number,
                      char const * log_file = "SocketServer.log",
                      size_t max_log_file_size = SS_FIVE_MEGABYTES);
      /**
       * Destroys a Socket_Server_T object. This is virtual to allow for
       * inheritance.
       */
      virtual ~Socket_Server_T();
      /**
       * Executes the socket server logic. This method must be called by the
       * creator of the server in order to "activate" it. The call will not
       * return until the server has been terminated (by another thread calling
       * the Exit() method).
       */
      virtual void Run(void);

      /*
       * Allow SS_Client_T access to private members.
       */
      friend class SS_Client_T;
   private:

      /**
       * Default construct made private to prevent its use.
       */
      Socket_Server_T() {}

      /**
       *  Accepts a connection from a new client.
       *  @param accept_fd File descriptor established for connection.
       */
      void accept_new_client(int accept_fd);
      /**
       * Closes the specified connection point for clients.
       * @param accept_fd Reference to file descriptor for connection point.
       */
      void close_connection(int & accept_fd);
      /**
       * Establishes a connection point for clients.
       * @param port_number Port on which to accept client connections.
       * @param accept_fd File descriptor established for connection.
       */
      void create_connection(unsigned short port_number, int & accept_fd);
      /**
       * Prepares read set for "select" call.
       * @return The maximum file descriptor set in the read set.
       * @param rd_set  Set that method fills with all clients that
       *                         are candidates for reading from.
       */
      int  setup_read_set(fd_set* rd_set);

      /** File descriptor by which server accepts client connections. */
      int m_accept_fd;
      /**
       * Map that provides quick access to a client object via its UID.
       */
      std::map<uint32_t, SS_Client_T *> m_clients_by_uid;

      /** Set to "true" when someone has requested that the server terminate. */
      bool_t m_exit_requested;

     /**
        * Map that provides quick access to a clients that are "pending". The
        * key to the map is the file descriptor. A client is "pending" from
        * the time its connection is accepted by the server until it has
        * identified itself (via the "hello" message). At that time, it is
        * removed from this map and added to m_clients_by_uid.
        */
      std::map<int, SS_Client_T *>  m_pending_clients;

      /** Port on which server accepts client connections. */
      unsigned short m_port_number;


      /** File descriptor by which server accepts secure client connections. */
      int m_secure_accept_fd;
      /**Allows for disabling non secure plain text connections*/
      bool_t m_non_secure_connections_enabled;
      /** Address to bind to */
      in_addr_t m_bind_ip_address;
};
#endif // SOCKET_SERVER_T_HPP
