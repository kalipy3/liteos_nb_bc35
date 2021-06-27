/*
 * server_msg_processor.c
 * Copyright (C) 2021 2021-06-22 09:56 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "server_msg_processor.h"

char server_dnmsg_buf[512];

int is_valid_pkg(char *pkg)
{
    return 1;
}

void server_pkg_process(svr_dn_msg_parsed_s *parsed)
{
    pkg_head_s *h;
    char *p;
    pkg_s pkg;
    uint8_t target;

    if (!is_valid_pkg(parsed->data))
    {
        printf("the pkg from server is bad!\r\n");
        return;
    }
    h = (pkg_head_s *)(parsed->data);
    p = parsed->data + sizeof(pkg_head_s);

    switch (h->type)
    {
        case PKG_OBSV:
            target = ((pkg_observer_s *)p)->target;
            if (TARGET_TEMP_HUMI == target)
            {
                pkg = build_temp_humi_pkg(12.0, 27.0);
                //send_payload(at_frame.socket, pkg.pkg_buf, pkg.pkg_len, "127.0.0.1", 9999, UDP);
            } else if (TARGET_LED == target) {
                
            }
            break;
        case PKG_ACTION:
            break;
        default:
            printf("the pkg from server not support!\r\n");
    }
}

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

        //server_pkg_process(&parsed_msg);
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
