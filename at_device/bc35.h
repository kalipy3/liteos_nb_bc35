/*
 * bc35.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BC35_H
#define BC35_H

#include "at_device.h"

#define NB_REBOOT                   "AT+NRB\r"

#define AT_SET_FULL_FUNC            "AT+CFUN=1\r"
#define AT_SET_MINI_FUNC            "AT+CFUN=0\r"
#define NB_GET_FUN                  "AT+CFUN?\r"

#define AT_SET_ERROR_INDICATOR      "AT+CMEE=1\r"
#define AT_DISABLE_HUAWEI_PLATFORM  "AT+QREGSWT=2\r"

#define AT_ATTACH_NETWORR           "AT+CGATT=1\r"
#define AT_GET_ATTACH_STATE         "AT+CGATT?\r"

#define AT_CLEAR_PRIOR_FREQ_CHANNEL "AT+NCSEARFCN\r"
#define AT_SET_MESSAGE_INDICATOR    "AT+NSONMI=2\r"
#define AT_GET_SIGNAL_STRENGTH      "AT+CSQ\r"
#define AT_GET_IMEI                 "AT+CGSN=1\r"
#define AT_GET_IP                   "AT+CGPADDR\r"

//#define AT_CREATE_SOCKET_TCP        "AT+NSOCR=STREAM,"
#define AT_CREATE_SOCKET_TCP        "AT+NSOCR=STREAM,6,8888"


uint32_t nb_reboot(void);
uint32_t nb_get_fun(uint8_t *pfun);
uint32_t nb_set_full_fun(uint8_t *pfun);
uint32_t nb_set_mini_fun(uint8_t *pfun);
uint32_t nb_enble_error_report(uint8_t *presp);
uint32_t nb_need_huawei_platform(uint8_t *presp);//disable_registration
uint32_t nb_attach2server(uint8_t *presp);
uint32_t nb_get_attach_state(uint8_t *presp);
uint32_t nb_clear_stored_EARFCN(uint8_t *presp);
uint32_t nb_set_socket_msg_indicator(uint8_t *presp);
uint32_t nb_get_signal_len(uint8_t *presp);
uint32_t nb_get_IMEI(uint8_t *presp);
uint32_t nb_get_IP(uint8_t *presp);
uint32_t nb_create_tcp_socket(uint8_t *presp);

#endif /* !BC35_H */
