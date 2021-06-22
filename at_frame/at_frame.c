/*
 * at_frame.c
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "at_frame.h"

at_frame_args_s at_frame;

__weak void at_usart_debug_msg_handler(char *buf, uint16_t len)
{
    printf("get a usart msg: %s\r\n", buf);
}

void at_frame_init(void)
{
    //创建信号量
    LOS_SemCreate(0, &at_frame.at_cmd_resp_sem_id);
    //创建互斥锁
    LOS_MuxCreate(&at_frame.at_task_mux_id);
    LOS_MuxCreate(&at_frame.at_cmd_args_mux_id);

    //服务器下行数据接收队列
    int32_t uwRet = LOS_QueueCreate("server_dn_msg_rececie_msgQueue", 5, &at_frame.server_dnmsg_queue_id, 0, 512);
    if(uwRet != LOS_OK)
    {
        printf("server_dn_msg_rececie_msgQueue Create failed, err_code:0x%x\r\n", uwRet);
    }

    //先启动usart_debug这个进程
    create_at_usart_debug_receiver_task();
    create_at_receiver_task();

    create_server_dn_msg_receiver_task();
}
