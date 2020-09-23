# add the main library
add_library(testFrame testFrame.cpp)

#add_executable(main ./test/main.cpp)
#target_link_libraries(main MathFunctions)

# install
install (TARGETS testFrame DESTINATION bin)
install (FILES testFrame.h DESTINATION include)

# test
#enable_testing()

# 
#add_test (test_run main 5)

# test usage
#add_test (test_usage main)
#set_tests_properties (test_usage
#  PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

# 定义一个宏，用来简化测试工作
#macro (do_test arg1 result)
#  add_test (test_${arg1} main ${arg1})
#  set_tests_properties (test_${arg1}
#    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
#endmacro (do_test)

# use do_test
#do_test (5  "is 25")
#do_test (10  "is 100000")
#do_test (2  "is 1024")