/*
 * pkg_typedef.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PKG_TYPEDEF_H
#define PKG_TYPEDEF_H

#include "stdint.h"
#pragma pack (1)

//包首//在不对齐的情况下是3+2+1+4+1+2=13个字节
typedef struct {
    char tag[3];//标识符
    uint16_t len;
    uint8_t type;
    uint32_t id;//终端id
    uint8_t seq;
    uint16_t check_sum;
} pkg_head_s;

typedef struct {
    uint8_t target;
    uint8_t act;
} pkg_act_s;

//服务端对iot pkg_act_s请求的响应包
typedef struct {
    uint8_t target;
    uint8_t resp_code;
} pkg_act_resp_s;

typedef struct {
    uint8_t target;
} pkg_observer_s;

//服务端对iot pkg_observer_s(观察TEMP_HUMI)请求的响应包
typedef struct {
    uint8_t target;
    float temp;
    float humi;
    uint8_t resp_code;
} pkg_observer_resp_s;

//服务端对iot pkg_observer_s(观察ADXL)请求的响应包
typedef struct {
    uint8_t target;
    int16_t x;
    int16_t y;
    int16_t z;
    float xang;
    float yang;
    float zang;
    uint8_t resp_code;
} pkg_observer_adxl_resp_s;

typedef struct {//在不对齐的情况下是9个字节
    uint8_t target;
    float temp;
    float humi;
} pkg_obs_temp_humi_s;

typedef struct {
    char *pkg_buf;
    uint16_t pkg_len;//包首pkg_head_s的长度+包体的长度+"\r\n"的2个字节
} pkg_s;


//typedef struct {
//    uint8_t target;
//} pkg_set_args_s;
//
////方向 版本号 负载 结束标志
//typedef struct {
//    uint8_t direction;
//    uint32_t version;
//    char * payload;
//} pkg_body_s;

#pragma pack()

#define TARGET_TEMP_HUMI 0x01
#define TARGET_LED 0x02
#define TARGET_IOT 0x03
#define TARGET_ADXL 0x04

#define ACT_BIND_TERMID_TO_UID 0x01
#define ACT_LED_ON 0x02
#define ACT_LED_OFF 0x03
#define ACT_ADXL_ALARM 0x04

#define PKG_ACTION 0x01
#define PKG_OBSV 0x02

#endif /* !PKG_TYPEDEF_H */
