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

#endif /* !BC35_H */
