/*
 * at_device.c
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "at_device.h"
#include "bc35.h"

void at_device_init(void){
    drv_led_init();
    at_usart_debug_init();
    at_usart_init();
}

__weak void at_device_svr_dn_msg_parse(char *buf, svr_dn_msg_parsed_s *p)
{

}
