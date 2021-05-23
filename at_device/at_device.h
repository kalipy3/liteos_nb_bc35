/*
 * at_device.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */
//#include "usart.h"
//#include "at_usart.h"
#include "main.h"
#include "stdint.h"
#include "liteos.h"
//#include "at_usart.h"

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

typedef struct {
    char * cmd;//构造好的at命令指针
    uint16_t cmd_len;//at命令长度
    const char **resp_strs_expected;//期望响应的特征字符串
    uint8_t resp_strs_expected_num;
    int match_idx;//匹配到的特征字符串索引
    char *resp_buf;
    uint16_t resp_msg_len;
    uint8_t cmd_type;
} at_cmd_args_s;

void at_device_init(void);

#endif /* !AT_DEVICE_H */
