/*
 * at_receiver.c
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "at_receiver.h"
#include <hex2str_and_str2hex.h>

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
        printf("get a msg from usart_bc35:%s\r\n", (char *)at_usart_rcv_data_buf);
        at_usart_msg_dispater((char *)at_usart_rcv_data_buf, len);

        //释放
        //uwRet = LOS_SemPost(at_frame.at_cmd_resp_sem_id);
        //if (uwRet != LOS_OK) {
        //    printf("at_receiver 1.post sem fail!, err_code:0x%x\r\n", uwRet);
        //}

    }
}

static void at_usart_msg_dispater(char *buf, int len) {
    at_usart_debug_msg_handler(buf, len);
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
            uint32_t ret = LOS_SemPost(at_frame.at_cmd_resp_sem_id);
            if (ret != LOS_OK) {
                printf("at_receiver 1.post sem fail!, err_code:0x%x\r\n", ret);
            }
        }
    }
}

static void svr_dn_msg_match(char *buf, int len) {
    
    //char a[32],b[32],c[32],d[32],e[32];
    //int match_cnt = sscanf(buf, "%[^,],%[^,],%[^,],%[^,],%s", a, b, c, d, e);
    //if (match_cnt >=5) {
    //    printf("svr_dn_msg_match() buf:%s\r\n", buf);
    //    printf("match msg_data:%s,%s,%s,%s,%s\n", a, b, c, d, e);
    //    printf("msg_body:%s\n", d);
    //    printf("resp_code:%s\n", e);
    //}
    
    if (len > 30) {
        char socket_id[3],server_ip[32],port[32],body_len[32],body[256],resp_code[3];
        int match_cnt = sscanf(buf, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", socket_id, server_ip, port, body_len, body, resp_code);
        if (match_cnt >=6) {
            printf("svr_dn_msg_match() buf:%s\r\n", buf);
            printf("match msg_data:%s,%s,%s,%s,%s,%s\n", socket_id, server_ip, port, body_len, body, resp_code);
            printf("socket_id:%s\n", socket_id);
            printf("server_ip:%s\n", server_ip);
            printf("port:%s\n", port);
            printf("body_len:%s\n", body_len);
            printf("body:%s\n", body);
            printf("resp_code:%s\n", resp_code);

            char str_msg_body[256] = {0};//这里如果不初始化为0的话，解析出的str_msg_body会有一个<0x02>乱码,即msg_body_parsed打印出来会这样:msg_body_parsed:<0x02>hello world
            hex2str(body, str_msg_body);
            printf("msg_body_parsed:%s\n", str_msg_body);
        }
    }
    
    
    //if (len > 30) {
    //    printf("555555555555:%s\r\n", buf);
    //    char a[32],b[32],c[32],d[32];
    //    sscanf(buf, "%[^,],%[^,],%[^,],%s", a, b, c, d);
    //    printf("%s,%s,%s,%s\n", a, b, c, d);
    //}
}

uint32_t create_at_receiver_task(void)
{
    UINT32 uwRet = 0;
    UINT32 uwTask1;
    TSK_INIT_PARAM_S stInitParam1;

    stInitParam1.usTaskPrio = 4;
    stInitParam1.uwStackSize = 0x800;
    stInitParam1.pcName = "at_usart_msg_listen";

    stInitParam1.pfnTaskEntry = at_usart_msg_listen;
    uwRet = LOS_TaskCreate(&uwTask1, &stInitParam1);
    if(uwRet != LOS_OK)
    {
        printf("at_usart_msg_listen Create failed\r\n");
    }
}
