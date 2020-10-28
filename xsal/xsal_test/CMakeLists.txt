include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
# add the main library
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
add_executable(xsalc_test pm_main.c procman_callouts.c)
target_link_libraries(xsalc_test xsalc)

# install
#install (TARGETS xsalc DESTINATION bin)
#install (FILES double_linked_list.h DESTINATION include)
