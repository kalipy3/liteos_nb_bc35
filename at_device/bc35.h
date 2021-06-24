/*
 * bc35.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BC35_H
#define BC35_H

#include "at_device.h"

//kalipy--------------------------------
#define AT_CFUN      "AT+CFUN?\r"
#define AT_CIMI "AT+CIMI\r"
#define AT_CSQ "AT+CSQ\r"
#define AT_CEREG "AT+CEREG?\r"
#define AT_CGPADDR "AT+CGPADDR\r"
#define AT_NPING "AT+NPING=223.5.5.5\r"
#define AT_NSOCR "AT+NSOCR=DGRAM,17,8888,1\r"
#define AT_NSOST "AT+NSOST=1,123.57.44.108,8888,5,68656C6C6F\r"
#define AT_NSORF "AT+NSORF=1,256\r"

uint32_t nb_cfun(uint8_t *presp);
uint32_t nb_cimi(uint8_t *presp);
uint32_t nb_csq(uint8_t *presp);
uint32_t nb_cereg(uint8_t *presp);
uint32_t nb_cgpaddr(uint8_t *presp);
uint32_t nb_nping(uint8_t *presp);
uint32_t nb_nsocr_udp(uint8_t *presp);
uint32_t nb_nsost(uint8_t *presp, char * req_data);
uint32_t nb_nsorf(uint8_t *presp);
//tcp send data
uint32_t nb_nsosd(uint8_t *presp, char * req_data);
uint32_t nb_nsosd_ex(uint8_t *presp, char * req_data,int data_len);

#endif /* !BC35_H */
