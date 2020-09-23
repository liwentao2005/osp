#ifndef TESTFRAME_H
#define TESTFRAME_H

extern int func_cnt;
extern int now_flag;

#define COLOR(msg, code) "\033["#code"m" msg "\033[0m"
#define GREEN(msg)  COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg)   COLOR(msg, 34)
#define RED(msg)    COLOR(msg, 31)

#define EXPECT(a, comp, b) \
    if (!((a) comp (b))) { \
        printf(RED("%s:%d:Failure\n" "\tExpected: ("#a") " #comp " ("#b")" "\n"),__FILE__, __LINE__); \
        now_flag = 1;\
    }; \

#define EXPECT_EQ(a, b) EXPECT(a, ==, b)
#define EXPECT_NE(a, b) EXPECT(a, !=, b)
#define EXPECT_GT(a, b) EXPECT(a, >, b)
#define EXPECT_LT(a, b) EXPECT(a, <, b)
#define EXPECT_GE(a, b) EXPECT(a, >=, b)
#define EXPECT_LE(a, b) EXPECT(a, >=, b)

#define TEST(a, b) \
void a##_##b(); \
__attribute__((constructor)) \
void reg_##a##_##b () { \
    add_test_func(a##_##b, #a "." #b); \
} \
void a##_##b()

struct func_struct {
    void (*func)();
    const char *func_name;
};

void add_test_func (void (*func)(), const char* str);

int TEST_ALL_FUNCS();

#endif
