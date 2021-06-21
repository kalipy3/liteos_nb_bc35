/*
 * at_transmitter.c
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "at_transmitter.h"

uint32_t get_err_code(char *buf, uint16_t len) {
    uint32_t err_code = AT_ERROR;
    char *str;
    str = strstr(buf, "CMD ERROR:");
    if (NULL != str)
    {
        sscanf(buf, "CMD ERROR:%d", &err_code);
    }
    return err_code;
}


uint32_t send_cmd(at_cmd_args_s *args) {
    UINT32 ret = AT_OK;
    //任务互斥
    /* 申请互斥锁 */
    ret = LOS_MuxPend(at_frame.at_task_mux_id, LOS_WAIT_FOREVER);
    if (ret != LOS_OK) {
        printf("1.pend mux fail!, err_code:0x%x\r\n", ret);
    }
    ret = LOS_MuxPend(at_frame.at_cmd_args_mux_id, LOS_WAIT_FOREVER);
    if (ret != LOS_OK) {
        printf("2.pend mux fail!, err_code:0x%x\r\n", ret);
    }
    at_frame.pat_cmd_args = args;
    at_frame.pat_cmd_args->match_idx = -1;
    ret = LOS_MuxPost(at_frame.at_cmd_args_mux_id);
    if (ret != LOS_OK) {
        printf("3.post mux fail!, err_code:0x%x\r\n", ret);
    }

    //通过串口发送at cmd
    at_usart_send(args->cmd, args->cmd_len);
    //等待接收器返回信息
    ret = LOS_SemPend(at_frame.at_cmd_resp_sem_id, AT_CMD_TIMEOUT);//10
    if (ret != LOS_OK) {
        printf("4.pend sem fail!, err_code:0x%x\r\n", ret);
    }
    
    ret = LOS_MuxPend(at_frame.at_cmd_args_mux_id, LOS_WAIT_FOREVER);
    if (ret != LOS_OK) {
        printf("5.pend mux fail!, err_code:0x%x\r\n", ret);
    }
    at_frame.pat_cmd_args = NULL;
    ret = LOS_MuxPost(at_frame.at_cmd_args_mux_id);
    
    if (ret != LOS_OK) {
        printf("6.pend sem fail!, err_code:0x%x\r\n", ret);
        //return;
    } else if (ret == LOS_OK) {
        if (1 == at_frame.pat_cmd_args->match_idx) {
            ret = get_err_code(at_frame.pat_cmd_args->resp_buf, at_frame.pat_cmd_args->resp_msg_len);
        }
    }
    
    //释放
    ret = LOS_MuxPost(at_frame.at_task_mux_id);
    if (ret != LOS_OK) {
        printf("7.post mux fail!, err_code:0x%x\r\n", ret);
    }
    return ret;
}

uint32_t send_cmd_ex(at_cmd_args_s *args) {
    UINT32 ret = AT_OK;
    ret = LOS_MuxPend(at_frame.at_cmd_args_mux_id, LOS_WAIT_FOREVER);
    if (ret != LOS_OK) {
        printf("2.pend mux fail!, err_code:0x%x\r\n", ret);
    }
    at_frame.pat_cmd_args = args;
    at_frame.pat_cmd_args->match_idx = -1;
    ret = LOS_MuxPost(at_frame.at_cmd_args_mux_id);
    if (ret != LOS_OK) {
        printf("3.post mux fail!, err_code:0x%x\r\n", ret);
    }

    //通过串口发送at cmd
    at_usart_send(args->cmd, args->cmd_len);
    //等待接收器返回信息
    ret = LOS_SemPend(at_frame.at_cmd_resp_sem_id, AT_CMD_TIMEOUT);//10
    if (ret != LOS_OK) {
        printf("4.pend sem fail!, err_code:0x%x\r\n", ret);
    }
    
    ret = LOS_MuxPend(at_frame.at_cmd_args_mux_id, LOS_WAIT_FOREVER);
    if (ret != LOS_OK) {
        printf("5.pend mux fail!, err_code:0x%x\r\n", ret);
    }
    at_frame.pat_cmd_args = NULL;
    ret = LOS_MuxPost(at_frame.at_cmd_args_mux_id);
    
    if (ret != LOS_OK) {
        printf("6.pend sem fail!, err_code:0x%x\r\n", ret);
        //return;
    } else if (ret == LOS_OK) {
        if (1 == at_frame.pat_cmd_args->match_idx) {
            ret = get_err_code(at_frame.pat_cmd_args->resp_buf, at_frame.pat_cmd_args->resp_msg_len);
        }
    }
    
    return ret;
}

//	uint32_t at_socket_udp_transmit(uint16_t socket, char* ip, uint32_t port, uint32_t length, char* data)
uint32_t send_payload(uint16_t socket, char* ip, uint32_t port, uint32_t length, char* data, int type)
{
    uint32_t ret;
    ret = LOS_MuxPend(at_frame.at_task_mux_id, LOS_WAIT_FOREVER);
    if(UDP == type)
    {
        ret = at_socket_udp_transmit(socket, ip, port, length, data);
    }
    else{
        ret = at_socket_tcp_transmit(socket, length, data);
    }
    LOS_MuxPost(at_frame.at_task_mux_id);
    return ret;
}
