//#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "ss_client_base_api.h"

int main(void)
{
    int ret = 0;
    char  CAN_IF_CLIENT_NAME[20];

    ret = SSClient_Name_Generator((char*) "CN", CAN_IF_CLIENT_NAME, sizeof(CAN_IF_CLIENT_NAME));
    if (0 != ret)
    {
        printf("SSClient_Name_Generator error.\n");
    } else {
        printf("SSClient_Name_Generator: %s OK.\n", CAN_IF_CLIENT_NAME);
    }
    ret = SSClient_Name_Generator((char*) "CN", CAN_IF_CLIENT_NAME, sizeof(CAN_IF_CLIENT_NAME));
    if (0 != ret)
    {
        printf("SSClient_Name_Generator error.\n");
    } else {
        printf("SSClient_Name_Generator: %s OK.\n", CAN_IF_CLIENT_NAME);
    }
    return 0;
}
