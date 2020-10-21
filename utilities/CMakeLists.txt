# include_directories(${PROJECT_SOURCE_DIR}/socket_client)
# add the main library
add_library(utilities SHARED double_linked_list.c)
#target_link_libraries(ss_client_base socket_client)

# install
install (TARGETS utilities DESTINATION bin)
install (FILES double_linked_list.h DESTINATION include)