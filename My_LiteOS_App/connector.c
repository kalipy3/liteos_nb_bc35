/*
 * connector.c
 * Copyright (C) 2021 2021-06-03 10:43 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "connector.h"

void connector(void)
{
    static int connected = 0;
    static char presp[256];
    while(1) {
        LOS_TaskDelay(10*1000);
        if (connected == 0) {
            printf("---init---\r\n");
            nb_cfun(presp);
            nb_cimi(presp);
            nb_csq(presp);
            nb_cereg(presp);
            nb_cgpaddr(presp);
            nb_nping(presp);
            nb_nsocr_udp(presp);
            connected = 1;
            printf("---init ok---\r\n");
        }

        //msg send test
        printf("---start---\r\n");
        nb_nsost(presp);
        nb_nsorf(presp);
        printf("---end---\r\n");

    }
}

void Create_BC35_Connectiontor_Task(void)
{
    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 9;
    stInitParam1.uwStackSize = 0x400;
    stInitParam1.pcName = "test";

    stInitParam1.pfnTaskEntry = connector;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("Create_BC35_Connectiontor_Task Create failed\r\n");
    }
}

