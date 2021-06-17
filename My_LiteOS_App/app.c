/*
 * App.c
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "app.h"
#include "at_device.h"
#include "liteos.h"
#include "at_usart.h"
#include "usart_debug.h"
#include "at_frame.h"
#include "bc35.h"

void Create_Task(void)
{
    at_frame_init();
}

void bc35Test_Task(void)
{
    static int flag = 0;
    static char presp[1];
    while(1) {
        LOS_TaskDelay(10000);
        //if (flag == 0) {
        //    printf("---init---\r\n");
        //    at_usart_bc35_send("AT+CFUN?\r", strlen("AT+CFUN?\r"));
        //    LOS_TaskDelay(1000);
        //    at_usart_bc35_send("AT+CIMI\r", strlen("AT+CIMI\r"));
        //    LOS_TaskDelay(1000);
        //    at_usart_bc35_send("AT+CSQ\r", strlen("AT+CSQ\r"));
        //    LOS_TaskDelay(1000);
        //    at_usart_bc35_send("AT+CEREG?\r", strlen("AT+CEREG?\r"));
        //    LOS_TaskDelay(1000);
        //    at_usart_bc35_send("AT+CGPADDR\r", strlen("AT+CGPADDR\r"));
        //    LOS_TaskDelay(1000);
        //    at_usart_bc35_send("AT+NPING=223.5.5.5\r", strlen("AT+NPING=223.5.5.5\r"));
        //    LOS_TaskDelay(1000);
        //    at_usart_bc35_send("AT+NSOCR=DGRAM,17,8888,1\r", strlen("AT+NSOCR=DGRAM,17,8888,1\r"));
        //    LOS_TaskDelay(1000);
        //    flag = 1;
        //    printf("---init ok---\r\n");
        //}

        //printf("---start---\r\n");
        //at_usart_bc35_send("AT+NSOST=1,123.57.44.108,8888,2,ABCD\r", strlen("AT+NSOST=1,123.57.44.108,8888,2,ABCD\r"));
        //LOS_TaskDelay(3000);
        //at_usart_bc35_send("AT+NSORF=1,256\r", strlen("AT+NSORF=1,256\r"));
        //LOS_TaskDelay(1000);
        //printf("---end---\r\n");
        //LOS_TaskDelay(2000);
        
        if (flag == 0) {
            printf("---init---\r\n");
            nb_cfun(presp);
            LOS_TaskDelay(1000);
            nb_cimi(presp);
            LOS_TaskDelay(1000);
            nb_csq(presp);
            LOS_TaskDelay(1000);
            nb_cereg(presp);
            LOS_TaskDelay(1000);
            nb_cgpaddr(presp);
            LOS_TaskDelay(1000);
            nb_nping(presp);
            LOS_TaskDelay(1000);
            nb_nsocr_udp(presp);
            flag = 1;
            printf("---init ok---\r\n");
        }

        printf("---start---\r\n");
            LOS_TaskDelay(1000);
            static char str[] = "hello world";
        nb_nsost(presp, str);
            LOS_TaskDelay(3000);
        nb_nsorf(presp);
        printf("---end---\r\n");

    }
}

void Create_bc35Test_Task(void)
{
    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 9;
    stInitParam1.uwStackSize = 0x800;
    stInitParam1.pcName = "test";

    stInitParam1.pfnTaskEntry = bc35Test_Task;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("bc35Test_Task Create failed\r\n");
    }
}
