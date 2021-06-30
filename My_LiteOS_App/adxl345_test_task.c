/*
 * adxl345_test_task.c
 * Copyright (C) 2021 2021-06-23 09:35 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "adxl345_test_task.h"
#include "pkg.h"

static void adxl345_reciver(void) {

    //printf("adxl345 init start..\r\n");
    //while(ADXL345_Init()){
    //    printf("ADXL345 Error!\r\n");
    //    LOS_TaskDelay(200);
    //}
    //printf("ADXL345 OK!\r\n");

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

        sprintf(buf, "adxl345_data:{x:%d,y:%d,z:%d,xang:%f,yang:%f,zang:%f}", adxl_data.x, adxl_data.y, adxl_data.z, adxl_data.xang, adxl_data.yang, adxl_data.zang);
        printf("%s\r\n", buf);

        //测试方便，如果adxl的x>200，说明老人摔倒，iot给php_server发送adxl_alarm包
        if (adxl_data.x > 200)
        {
            printf("your family fall down , adxl_alarm to server..\r\n");

            //打包
            pkg_s pkg = build_adxl_alarm_pkg();
            printf("pkg_len:%d\r\n\r\n", pkg.pkg_len);
            printf("pkg.pkg_buf:---\r\n");
            for (int i = 0; i < pkg.pkg_len; i++)
            {
                printf("pkg.pkg_buf[%d]:%x ", i, pkg.pkg_buf[i]);
            }
            printf("---\r\n");
            static char presp[1];
            nb_nsosd_ex(presp, pkg.pkg_buf, pkg.pkg_len);
        }
    }
}

uint32_t create_adxl345_receiver_task(void)
{
    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 9;
    stInitParam1.uwStackSize = 0x800;
    stInitParam1.pcName = "adxl345_reciver";

    stInitParam1.pfnTaskEntry = adxl345_reciver;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("create_adxl345_receiver_task Create failed\r\n");
    }

    printf("create_adxl345_receiver_task Create ok\r\n");
}
