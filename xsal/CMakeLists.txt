include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# add the main library
add_library(xsalc SHARED xsal_ns_thread.c xsal_get_config.c)
#target_link_libraries(ss_client_base socket_client)

# install
install (TARGETS xsalc DESTINATION bin)
install (FILES xsal_ns_thread.h DESTINATION include)


add_subdirectory(xsal_test)