include_directories(${PROJECT_SOURCE_DIR}/utilities)
# add the main library
add_library(osp_timer SHARED osp_timer_linux.c)
target_link_libraries(utilities)

# install
install (TARGETS osp_timer DESTINATION bin)
install (FILES osp_timer_linux.h DESTINATION include)