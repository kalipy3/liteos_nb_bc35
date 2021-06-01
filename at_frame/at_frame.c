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
    create_at_usart_debug_receiver_task();
}
