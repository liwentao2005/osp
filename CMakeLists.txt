cmake_minimum_required (VERSION  2.6)
project (Tutorial)

# The version number.
set (Tutorial_VERSION_MAJOR 2)
set (Tutorial_VERSION_MINOR 1)

set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

option (USE_MYMATH
		"Use tutorial provided math implementation" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/project_config/TutorialConfig.h.in"
	"${PROJECT_BINARY_DIR}/TutorialConfig.h"
	)
	
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

if (USE_MYMATH)
	include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
	add_subdirectory(MathFunctions)
	set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

add_executable(Tutorial Tutorial.cpp)
target_link_libraries(Tutorial ${EXTRA_LIBS})

#new directory
include_directories ("${PROJECT_SOURCE_DIR}/xsal_cpp_api")
add_subdirectory(xsal_cpp_api)
add_executable(xsal_test xsal_test.cpp)
target_link_libraries(xsal_test xsal)

#new directory
include_directories ("${PROJECT_SOURCE_DIR}/utilities")
add_subdirectory(utilities)
#target_link_libraries(ss_client_base socket_client)

#new directory
#include_directories ("${PROJECT_SOURCE_DIR}/osp_timer")
#add_subdirectory(osp_timer)
#target_link_libraries(ss_client_base socket_client)
## timer test bin
#include_directories ("${PROJECT_SOURCE_DIR}/osp_timer")
#add_executable(testTimer testTimer_main.cpp)
#target_link_libraries(testTimer osp_timer pthread)

#new directory
#include_directories ("${PROJECT_SOURCE_DIR}/socket_server")
#add_subdirectory(socket_server)
#target_link_libraries(ss_client_base socket_client)

#new directory
#include_directories ("${PROJECT_SOURCE_DIR}/socket_client")
add_subdirectory(socket_client)
#target_link_libraries(ss_client_base socket_client)

#new directory
#include_directories ("${PROJECT_SOURCE_DIR}/socket_client")
add_subdirectory(xsal)
#target_link_libraries(ss_client_base socket_client)

#new directory
include_directories ("${PROJECT_SOURCE_DIR}/ss_client_base")
add_subdirectory(ss_client_base)
add_executable(ss_client_base_test ss_client_base_test.cpp)
target_link_libraries(ss_client_base_test ss_client_base pthread)

install (TARGETS Tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
         DESTINATION include)