/*
 * at_device.c
 * Copyright (C) 2021 2021-04-21 14:07 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "at_device.h"
#include "at_usart.h"

void at_device_init(void){
    at_usart_init();
}

