#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <string>
#include <math.h>

#include "testFrame.h"

int add (int a, int b) {
    return a+b;
};

TEST(test, add_funcs) {
	//be equal to
    EXPECT_EQ(add(3, 4), 8);
    //be equal to
    EXPECT_NE(add(3, 4), 8);
    //greater than
    EXPECT_GT(add(3, 4), 7);
    //less than
    EXPECT_LT(add(3, 4), 8);
    //Greater than or equal to
    EXPECT_GE(add(3, 4), 7);
    //Less than or equal to
    EXPECT_LE(add(3, 4), 7);
}

TEST(test, sub_funcs) {
    EXPECT_EQ(add(3, 4), 7);
    EXPECT_NE(add(3, 4), 8);
    EXPECT_GT(add(3, 4), 6);
    EXPECT_LT(add(3, 4), 8);
    EXPECT_GE(add(3, 4), 7);
    EXPECT_LE(add(3, 4), 7);
}

int main(void)
{
    TEST_ALL_FUNCS();
    return 0;
}