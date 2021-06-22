/*
 * at_frame.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AT_FRAME_H
#define AT_FRAME_H

#include "stdint.h"
#include "at_device.h"

typedef struct {
    uint32_t at_task_mux_id;
    uint32_t at_cmd_args_mux_id;
    uint32_t at_cmd_resp_sem_id;
    uint32_t server_dnmsg_queue_id;
    at_cmd_args_s *pat_cmd_args;
} at_frame_args_s;

#define AT_CMD_TIMEOUT 10*1000
//#define AT_CMD_TIMEOUT -2 
#define AT_OK 0
#define AT_ERROR -1

extern at_frame_args_s at_frame;
uint32_t send_cmd(at_cmd_args_s *args);

void at_usart_debug_msg_handler(char *buf, uint16_t len);

#endif /* !AT_FRAME_H */
