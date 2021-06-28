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
#include "adxl345.h"
#include "pkg.h"

void Create_Task(void)
{
    at_frame_init();
}

void bc35_UDP_Test_Task(void)
{
    static int flag = 0;
    static char presp[1];
    while(1) {
        LOS_TaskDelay(10000);
        //if (flag == 0) {
        //    printf("---init---\r\n");
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
            at_usart_bc35_send("AT+CFUN=1\r", strlen("AT+CFUN=1\r"));
            LOS_TaskDelay(3000);
            nb_cfun(presp);
            LOS_TaskDelay(1000);
            at_usart_bc35_send("AT+CGATT=1\r", strlen("AT+CGATT=1\r"));
            LOS_TaskDelay(3000);
            nb_cimi(presp);
            LOS_TaskDelay(1000);
            nb_csq(presp);
            LOS_TaskDelay(1000);
            nb_cereg(presp);
            LOS_TaskDelay(2000);
            nb_cgpaddr(presp);
            LOS_TaskDelay(3000);
            nb_nping(presp);
            LOS_TaskDelay(3000);
            nb_nsocr_udp(presp);
            flag = 1;
            printf("---init ok---\r\n");
        }

        printf("---start---\r\n");
        //static char str[] = "hello udp_server, I'am liuyong!!";
        
        static char buf[512];
        Adxl345_data adxl_data;
        adxl345_data_get(&adxl_data);
        sprintf(buf, "hello udp_server, I'am liuyong, this is my adxl345_data:{x:%d,y:%d,z:%d,xang:%d,yang:%d,zang:%d}", adxl_data.x, adxl_data.x, adxl_data.x, adxl_data.xang, adxl_data.yang, adxl_data.zang);
        
        nb_nsost(presp, buf);
        LOS_TaskDelay(3000);
        nb_nsorf(presp);
        printf("---end---\r\n");

    }
}

void Create_bc35_UDP_Test_Task(void)
{
    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 9;
    stInitParam1.uwStackSize = 0x800;
    stInitParam1.pcName = "test";

    stInitParam1.pfnTaskEntry = bc35_UDP_Test_Task;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("bc35_UDP_Test_Task Create failed\r\n");
    }
}

void bc35_TCP_Test_Task(void)
{
    static int flag = 0;
    static char presp[1];
    while(1) {
        LOS_TaskDelay(10000);
        if (flag == 0) {
            printf("---init---\r\n");
            at_usart_bc35_send("AT+CFUN=1\r", strlen("AT+CFUN=1\r"));
            LOS_TaskDelay(3000);
            at_usart_bc35_send("AT+CFUN?\r", strlen("AT+CFUN?\r"));
            LOS_TaskDelay(1000);
            at_usart_bc35_send("AT+CGATT=1\r", strlen("AT+CGATT=1\r"));
            LOS_TaskDelay(3000);
            at_usart_bc35_send("AT+CIMI\r", strlen("AT+CIMI\r"));
            LOS_TaskDelay(1000);
            at_usart_bc35_send("AT+CSQ\r", strlen("AT+CSQ\r"));
            LOS_TaskDelay(1000);
            at_usart_bc35_send("AT+NSOCR=STREAM,6,8282,1\r", strlen("AT+NSOCR=STREAM,6,8282,1\r"));//create a tcp socket
            LOS_TaskDelay(3000);
            at_usart_bc35_send("AT+NSOCO=1,150.158.178.83,8282\r", strlen("AT+NSOCO=1,150.158.178.83,8282\r"));//tcp connect to server
            //at_usart_bc35_send("AT+NSOCO=1,123.57.44.108,9999\r", strlen("AT+NSOCO=1,123.57.44.108,9999\r"));//tcp connect to server
            //at_usart_bc35_send("AT+NSOCO=1,122.112.145.221,9000\r", strlen("AT+NSOCO=1,122.112.145.221,9000\r"));//tcp connect to server
            LOS_TaskDelay(3000);
            flag = 1;
            printf("---init ok---\r\n");

        //printf("---start---\r\n");
        //at_usart_bc35_send("AT+NSOSD=1,2,ABCD\r", strlen("AT+NSOSD=1,2,ABCD\r"));//tcp send data
        //LOS_TaskDelay(3000);
        //at_usart_bc35_send("AT+NSORF=1,256\r", strlen("AT+NSORF=1,256\r"));//tcp or udp recive data
        //printf("---end---\r\n");
        
        printf("---start---\r\n");
        //static char str[] = "hello tcp_server, I'am liuyong!!";

        static char buf[512];
        Adxl345_data adxl_data;
        adxl345_data_get(&adxl_data);
        //sprintf(buf, "hello tcp_server, I'am liuyong, this is my adxl345_data:{x:%d,y:%d,z:%d,xang:%d,yang:%d,zang:%d}", adxl_data.x, adxl_data.x, adxl_data.x, adxl_data.xang, adxl_data.yang, adxl_data.zang);
        //nb_nsosd(presp, buf);
        
        //打包
        //float temp = 12.0;
        //float humi = 27.0;
        //pkg_s pkg = build_temp_humi_pkg(temp, humi);
        //printf("pkg_len:%d\r\n\r\n", pkg.pkg_len);
        //printf("pkg.pkg_buf:---\r\n");
        //for (int i = 0; i < pkg.pkg_len; i++)
        //{
        //    printf("pkg.pkg_buf[%d]:%x ", i, pkg.pkg_buf[i]);
        //}
        //printf("---\r\n");
        //nb_nsosd_ex(presp, pkg.pkg_buf, pkg.pkg_len);

        //LOS_TaskDelay(4000);
        //at_usart_bc35_send("AT+NSORF=1,256\r", strlen("AT+NSORF=1,256\r"));//tcp or udp recive data
        //printf("---end---\r\n");
        
        //打包
        pkg_s pkg = build_bind_termid_to_uid_pkg();
        printf("pkg_len:%d\r\n\r\n", pkg.pkg_len);
        printf("pkg.pkg_buf:---\r\n");
        for (int i = 0; i < pkg.pkg_len; i++)
        {
            printf("pkg.pkg_buf[%d]:%x ", i, pkg.pkg_buf[i]);
        }
        printf("---\r\n");
        nb_nsosd_ex(presp, pkg.pkg_buf, pkg.pkg_len);
        }

        LOS_TaskDelay(3000);
        at_usart_bc35_send("AT+NSORF=1,256\r", strlen("AT+NSORF=1,256\r"));//tcp or udp recive data
        printf("---end---\r\n");
    }
}

void Create_bc35_TCP_Test_Task(void)
{
    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 9;
    stInitParam1.uwStackSize = 0x800;
    stInitParam1.pcName = "test";

    stInitParam1.pfnTaskEntry = bc35_TCP_Test_Task;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("bc35_TCP_Test_Task Create failed\r\n");
    }
}
