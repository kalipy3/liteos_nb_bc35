/*
 * usart_debug.c
 * Copyright (C) 2021 2021-05-27 11:10 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "usart_debug.h"

extern uint32_t at_usart_debug_msg_queue_id;

static char at_usart_debug_rcv_data_buf[USART_DEBUG_RX_BUFFER_LEN];

void at_usart_debug_msg_handler(char *buf, uint16_t len)
{
    printf("at_usart_debug_msg_handler()被调用..");
}

static void at_usart_debug_msg_listen(void) {

    at_usart_msg_s msg;
    UINT32 uwRet = 0;
    while (1)
    {
        //读消息
        //如果出错，输出错误信息
        //如果有消息，则提取消息数据
        //dispatch消息
        uwRet = LOS_QueueReadCopy(at_usart_debug_msg_queue_id, &msg, sizeof(at_usart_msg_s), LOS_WAIT_FOREVER);
        if(uwRet != LOS_OK)
        {
            printf("recv message failure,error:%x\n",uwRet);
            continue;
        }

        int len = at_usart_debug_get_msg_data((char *)at_usart_debug_rcv_data_buf, msg);//get到的msg_data保存到at_usart_rcv_data_buf
        printf("从串口接收到一帧数据usart_debug:%s\n", (char *)at_usart_debug_rcv_data_buf);

        at_usart_debug_msg_handler(at_usart_debug_rcv_data_buf, len);

    }
}

uint32_t create_at_usart_debug_receiver_task(void)
{
    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 4;
    stInitParam1.uwStackSize = 0x400;
    stInitParam1.pcName = "at_usart_debug_msg_listen";

    stInitParam1.pfnTaskEntry = at_usart_debug_msg_listen;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("at_usart_debug_msg_listen Create failed\r\n");
    }
}
