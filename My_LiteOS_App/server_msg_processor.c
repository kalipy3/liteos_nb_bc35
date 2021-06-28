/*
 * server_msg_processor.c
 * Copyright (C) 2021 2021-06-22 09:56 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "server_msg_processor.h"
#include "led.h"
#include "bc35.h"

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
            //target = ((pkg_observer_s *)p)->target;
            //if (TARGET_TEMP_HUMI == target)
            //{
            //    pkg = build_temp_humi_pkg(12.0, 27.0);
            //    //send_payload(at_frame.socket, pkg.pkg_buf, pkg.pkg_len, "127.0.0.1", 9999, UDP);
            //} else if (TARGET_LED == target) {
            //    
            //}
            //break;
        case PKG_ACTION:

            ////服务端对iot pkg_act_s请求的响应包
            //typedef struct {
            //    uint8_t resp_code;
            //} pkg_act_resp_s;
            target = ((pkg_act_resp_s *)p)->target;
            if (TARGET_IOT == target)
            {
                //解析服务器发来的响应包
                pkg_act_resp_s tp;
                pkg_head_s th;
                parse_bind_termid_to_uid_resp_pkg(parsed->data, &th, &tp);

            } else if (TARGET_LED == target) {
                printf("get a req pkg from server..\r\n");
                //解析服务器发来的请求包
                pkg_act_s tp;
                pkg_head_s th;
                parse_pkg_act_pkg(parsed->data, &th, &tp);

                if (tp.act == ACT_LED_ON)
                {
                    drv_led_on(led0);
                } else if (tp.act == ACT_LED_OFF) {
                    drv_led_off(led0);
                }

                //构造该请求的响应包
                uint8_t resp_code = 0;//success
                pkg_s pkg = build_pkg_act_resp_pkg(&th, &tp, resp_code);
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

        at_device_svr_dn_msg_parse(server_dnmsg_buf, &parsed_msg);

        server_pkg_process(&parsed_msg);
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
