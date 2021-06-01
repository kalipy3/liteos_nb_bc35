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

extern uint32_t at_usart_msg_queue_id;

void *usart_Receive_Handler_Task(void *arg)
{
    at_usart_msg_s msg;
    static char msg_buf[100];
    UINT32 uwRet = 0;
    while (1)
    {
        uwRet = LOS_QueueReadCopy(at_usart_msg_queue_id, &msg, sizeof(at_usart_msg_s), LOS_WAIT_FOREVER);
        if(uwRet != LOS_OK)
        {
            printf("recv message failure,error:%x\n",uwRet);
            //break;
            continue;
        }
        
        at_usart_get_msg_data((char *)msg_buf, msg);//get到的msg_data保存到msg_buf
        printf("从串口接收到一帧数据:%s\n", (char *)msg_buf);
        //usart_receive_msg_handler((char *)msg_buf);
    }
}

void Create_Task(void)
{
    //先启动usart_debug这个进程
    create_at_usart_debug_receiver_task();

    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 9;
    stInitParam1.uwStackSize = 0x400;
    stInitParam1.pcName = "usart_Receive_Handler_Task";
    
    stInitParam1.pfnTaskEntry = usart_Receive_Handler_Task;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("usart_Receive_Handler_Task Create failed\r\n");
    }
}
