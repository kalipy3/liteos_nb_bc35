/*
 * at_device.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */
//#include "usart.h"
//#include "at_usart.h"
#include "main.h"

#ifndef AT_DEVICE_H
#define AT_DEVICE_H

extern UART_HandleTypeDef huart3;

#define USART_HANDLE_FOR_AT_DEVICE    huart3
#define RX_BUFFER_LEN 1024
#define TX_BUFFER_LEN 256 

typedef struct {
    uint32_t si;
    uint32_t ei;
} at_usart_msg_s;

void at_device_init(void);

#endif /* !AT_DEVICE_H */
