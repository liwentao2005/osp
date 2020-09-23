include_directories(${PROJECT_SOURCE_DIR}/socket_client)
# add the main library
add_library(ss_client_base SHARED ss_client_base.c)
target_link_libraries(ss_client_base socket_client)

# install
install (TARGETS ss_client_base DESTINATION bin)
install (FILES ss_client_base_api.h DESTINATION include)