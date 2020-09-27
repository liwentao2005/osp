//#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "ss_client_base_api.h"

static unsigned int CAN_IF_Client_ID = 0;

static void Received_Message_Callback(SC_Message_T const * const message)
{

}

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
    
    /*1.Get SS_Client_Info_T*/
    CAN_IF_Client_ID = Init_SocketServer_Client_Defult(CAN_IF_CLIENT_NAME, (void*)&Received_Message_Callback);
    /**/
    Launch_SocketServer_Client(CAN_IF_Client_ID);
    /*inital CAN HVAC value*/
    SocketServer_Client_Send(CAN_IF_Client_ID, "NAME", 100 /*CAN_IF_HVAC_INIT_UPDATE*/, CAN_IF_Client_ID , NULL , 0);
    
    return 0;
}
