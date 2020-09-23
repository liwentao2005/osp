#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "testFrame.h"

using namespace std;

struct func_struct func_arr[1000];

int func_cnt = 0;
int now_flag = 0;

int TEST_ALL_FUNCS() {
    printf(GREEN("[==========] ") "Running %d tests\n", func_cnt);
    int failed = 0;
    for (int i=0;i<func_cnt;i++) {
        printf(GREEN("[  RUN     ] ") "%s\n", func_arr[i].func_name);
        now_flag = 0;
        func_arr[i].func();
        failed += now_flag;
        if(now_flag)
            printf(RED("[  FAILED  ] \n"));
        else
            printf(GREEN("[  PASSED  ] \n"));
    }
    printf("\n");
    printf(GREEN("[  PASSED  ] ") "%d/%d\n", func_cnt - failed, func_cnt);
    printf(RED("[  FAILED  ] ") "%d/%d\n", failed, func_cnt);
    return 0;
}

void add_test_func (void (*func)(), const char* str) {
    func_arr[func_cnt].func = func;
    func_arr[func_cnt].func_name = str;
    func_cnt ++;
    return;
}
