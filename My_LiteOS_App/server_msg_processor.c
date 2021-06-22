/*
 * server_msg_processor.c
 * Copyright (C) 2021 2021-06-22 09:56 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "server_msg_processor.h"

char server_dnmsg_buf[512];

static void server_dnmsg_listen(void) {

    UINT32 uwRet = 0;
    svr_dn_msg_parsed_s parsed_msg;
    uint32_t msg_len;

    while (1)
    {
        msg_len = sizeof(server_dnmsg_buf);
        uwRet = LOS_QueueReadCopy(at_frame.server_dnmsg_queue_id, server_dnmsg_buf, &msg_len, LOS_WAIT_FOREVER);
        if(uwRet != LOS_OK)
        {
            printf("server dnmsg recv message failure,error:%x\n",uwRet);
            continue;
        }

        printf("get a dn_msg from server:%s\r\n", (char *)server_dnmsg_buf);

        parsed_msg.data = server_dnmsg_buf;
        at_device_svr_dn_msg_parse(server_dnmsg_buf, &parsed_msg);
    }
}

uint32_t create_server_dn_msg_receiver_task(void)
{
    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 4;
    stInitParam1.uwStackSize = 0x800;
    stInitParam1.pcName = "server_dnmsg_listen";

    stInitParam1.pfnTaskEntry = server_dnmsg_listen;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("create_server_dn_msg_receiver_task Create failed\r\n");
    }
    
    printf("create_server_dn_msg_receiver_task Create ok\r\n");
}
