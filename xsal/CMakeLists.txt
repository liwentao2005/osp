include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# add the main library
add_library(xsalc SHARED xsal_ns_thread.c xsal_get_config.c 
            xsal_init.c xsal_run.c xsal_i_thread.c xsal_i_config.c 
            xsal_i_event_property.c 
            xsal_create_mutex.c xsal_lock_mutex.c xsal_unlock_mutex.c xsal_destroy_mutex.c)
target_link_libraries(xsalc utilities pthread)

# install
install (TARGETS xsalc DESTINATION bin)
install (FILES xsal_ns_thread.h DESTINATION include)


add_subdirectory(xsal_test)