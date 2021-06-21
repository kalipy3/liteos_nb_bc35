/*
 * connector.c
 * Copyright (C) 2021 2021-06-03 10:43 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "connector.h"

void connector(void)
{
    uint32_t ret;
    uint32_t is_connectted = 0;

    while(1)
    {

        LOS_TaskDelay(10*1000);
        if(is_connectted)
        {
            continue;
        }

        is_connectted = 1;

        printf("--send_payload start..\n");
        printf("--send_payload ending..\n");

    }
}

void Create_BC35_Connectiontor_Task(void)
{
    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 9;
    stInitParam1.uwStackSize = 0x800;
    stInitParam1.pcName = "test";

    stInitParam1.pfnTaskEntry = connector;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("Create_BC35_Connectiontor_Task Create failed\r\n");
    }
}

