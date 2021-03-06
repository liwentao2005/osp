include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# add the main library
add_library(xsalc SHARED xsal_ns_thread.c xsal_create_thread.c xsal_i_thread.c
            xsal_get_config.c xsal_i_config.c
            xsal_init.c xsal_run.c xsal_i_run.c em_assert.c
            xsal_i_event_property.c xsal_event_names_internal.c
            xsal_create_mutex.c xsal_lock_mutex.c xsal_unlock_mutex.c xsal_destroy_mutex.c
            xsal_signal_semaphore.c xsal_wait_semaphore.c xsal_create_semaphore.c xsal_init_semaphore_attr.c xsal_destroy_semaphore.c xsal_try_wait_semaphore.c
            xsal_signal_ready.c xsal_wait_ready.c
            xsal_i_message_queue.c xsal_i_publish.c
            xsal_i_engine.c xsal_get_app_id.c
            xsal_i_connections.c
            xsal_rpc_linux.c
            xsal_ns_proxy.c xsal_i_buffer_pools.c
            xsal_open_shared_memory.c xsal_create_shared_memory.c xsal_close_shared_memory.c xsal_i_shared_memory.c)
target_link_libraries(xsalc utilities pthread rt)

set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

# install
install (TARGETS xsalc DESTINATION bin)
install (FILES xsal_ns_thread.h DESTINATION include)


add_subdirectory(xsal_test)