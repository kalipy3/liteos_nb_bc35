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
    LOS_MuxPend(at_frame.at_task_mux_id, LOS_WAIT_FOREVER);
    
    LOS_MuxPend(at_frame.at_cmd_args_mux_id, LOS_WAIT_FOREVER);
    at_frame.pat_cmd_args = args;
    at_frame.pat_cmd_args->match_idx = -1;
    LOS_MuxPost(at_frame.at_cmd_args_mux_id);

    //通过串口发送at cmd
    at_usart_send(args->cmd, args->cmd_len);
    //等待接收器返回信息
    ret = LOS_SemPend(at_frame.at_cmd_resp_sem_id, AT_CMD_TIMEOUT);//10
    
    LOS_MuxPend(at_frame.at_cmd_args_mux_id, LOS_WAIT_FOREVER);
    at_frame.pat_cmd_args = NULL;
    LOS_MuxPost(at_frame.at_cmd_args_mux_id);
    
    if (ret != LOS_OK) {
        printf("pend sem fail!\r\n");
        return;
    } else if (ret == LOS_OK) {
        if (1 == at_frame.pat_cmd_args->match_idx) {
            ret = get_err_code(at_frame.pat_cmd_args->resp_buf, at_frame.pat_cmd_args->resp_msg_len);
        }
    }
    
    //释放
    LOS_MuxPost(at_frame.at_task_mux_id);
    return ret;
}
