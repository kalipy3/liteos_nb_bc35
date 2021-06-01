/*
 * drv_usart_debug.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef DRV_USART_DEBUG_H
#define DRV_USART_DEBUG_H

#include "usart.h"
#include "liteos.h"
#include "at_device.h"

extern UART_HandleTypeDef huart3;

#define USART_DEBUG_HUART    huart3
#define USART_DEBUG_RX_BUFFER_LEN 1024
#define USART_DEBUG_TX_BUFFER_LEN 256 

void at_usart_debug_init(void);
void at_usart_debug_send(char *buf, uint16_t len);
void at_usart_debug_irq_handler(void);
int at_usart_debug_get_msg_data(char * msg_buf, at_usart_msg_s msg);

#endif /* !DRV_USART_DEBUG_H */
