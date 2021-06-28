/*
 * led.h
 * Copyright (C) 2020 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LED_H
#define LED_H

#include "main.h"
#include "liteos.h"

#define led0    0
#define led1    1
#define led2    2

#define led0_pin 3
#define led1_pin 4 
#define led2_pin 9

void drv_led_init(void);
void drv_led_on(int led_no);
void drv_led_off(int led_no);
void drv_led_toggle(int ledx_pin);
void led_flash(int led_no, unsigned int period);//peroid:闪烁周期，单位为liteos的ticks

#endif /* !LED_H */
