# add the main library

add_library(socket_client SHARED ss_client.c)

#add_executable(main ./test/main.cpp)
#target_link_libraries(main MathFunctions)

# install
install (TARGETS socket_client DESTINATION bin)
install (FILES socket_client_api.h DESTINATION include)
