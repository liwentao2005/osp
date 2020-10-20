# add the main library

#add_library(socket_client SHARED ss_client.c)

add_executable(SocketServer ss_main.cpp Socket_Server_T.cpp SS_Client_T.cpp)
#target_link_libraries(main MathFunctions)

# install
install (TARGETS SocketServer DESTINATION bin)
install (FILES Socket_Server_T.hpp DESTINATION include)
