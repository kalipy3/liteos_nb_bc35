/*
 * adxl345_test_task.c
 * Copyright (C) 2021 2021-06-23 09:35 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "adxl345_test_task.h"

static void adxl345_reciver(void) {

    printf("adxl345 init start..\r\n");
    while(ADXL345_Init()){
        printf("ADXL345 Error!\r\n");
        LOS_TaskDelay(200);
    }
    printf("ADXL345 OK!\r\n");

    static char *buf[512];
    while (1)
    {
        LOS_TaskDelay(3000);
        Adxl345_data adxl_data;
        adxl345_data_get(&adxl_data);

        //printf("adxl345 data:\r\n");
        //printf("x:%d\r\n", adxl_data.x);
        //printf("y:%d\r\n", adxl_data.y);
        //printf("z:%d\r\n", adxl_data.z);
        //printf("x_angle:%d\r\n", adxl_data.xang);
        //printf("y_angle:%d\r\n", adxl_data.yang);
        //printf("z_angle:%d\r\n", adxl_data.zang);

        sprintf(buf, "adxl345_data:{x:%d,y:%d,z:%d,xang:%d,yang:%d,zang:%d}", adxl_data.x, adxl_data.x, adxl_data.x, adxl_data.xang, adxl_data.yang, adxl_data.zang);
        printf("%s", buf);
    }
}

uint32_t create_adxl345_receiver_task(void)
{
    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 9;
    stInitParam1.uwStackSize = 0x400;
    stInitParam1.pcName = "adxl345_reciver";

    stInitParam1.pfnTaskEntry = adxl345_reciver;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("create_adxl345_receiver_task Create failed\r\n");
    }

    printf("create_adxl345_receiver_task Create ok\r\n");
}
