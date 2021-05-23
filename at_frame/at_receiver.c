/*
 * at_receiver.c
 * Copyright (C) 2021 2021-04-28 21:44 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "at_receiver.h"

extern at_cmd_args_s at_cmd_args;
extern uint32_t at_usart_msg_queue_id;
char at_usart_rcv_data_buf[RX_BUFFER_LEN];

static void at_usart_msg_listen(void) {
    
    at_usart_msg_s msg;
    UINT32 uwRet = 0;
    while (1)
    {
        //读消息
        //如果出错，输出错误信息
        //如果有消息，则提取消息数据
        //dispatch消息
        uwRet = LOS_QueueReadCopy(at_usart_msg_queue_id, &msg, sizeof(at_usart_msg_s), LOS_WAIT_FOREVER);
        if(uwRet != LOS_OK)
        {
            printf("recv message failure,error:%x\n",uwRet);
            continue;
        }

        int len = at_usart_get_msg_data((char *)at_usart_rcv_data_buf, msg);//get到的msg_data保存到at_usart_rcv_data_buf
        printf("从串口接收到一帧数据:%s\n", (char *)at_usart_rcv_data_buf);
        at_usart_msg_dispater((char *)at_usart_rcv_data_buf, len);

        //释放
        LOS_SemPost(at_frame.at_cmd_resp_sem_id);

    }
}

static void at_usart_msg_dispater(char *buf, int len) {
    at_cmd_resp_match(buf, len);
    svr_dn_msg_match(buf, len);
}

static void at_cmd_resp_match(char *buf, int len) {
    char *str;
    if (NULL == at_frame.pat_cmd_args) return;
    for (int i = 0; i < at_frame.pat_cmd_args->resp_strs_expected_num; i++)
    {
        str = strstr(at_usart_rcv_data_buf, at_frame.pat_cmd_args->resp_strs_expected[i]);
        if (NULL != str)
        {
            at_frame.pat_cmd_args->match_idx = i;
            at_frame.pat_cmd_args->resp_buf = str;
            at_frame.pat_cmd_args->resp_msg_len = len;
            LOS_SemPost(at_frame.at_cmd_resp_sem_id);
        }
    }
}

static void svr_dn_msg_match(char *buf, int len) {
}

uint32_t create_at_receiver_task(void)
{
    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 9;
    stInitParam1.uwStackSize = 0x400;
    stInitParam1.pcName = "at_usart_msg_listen";

    stInitParam1.pfnTaskEntry = at_usart_msg_listen;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("at_usart_msg_listen Create failed\r\n");
    }
}
