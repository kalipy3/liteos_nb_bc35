/*
 * led.c
 * Copyright (C) 2020 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "led.h"

void drv_led_init(void)
{
    //使能gpioe
    RCC->AHB1ENR |= 1<<4;
    //使能gpiog
    RCC->AHB1ENR |= 1<<6;

    //GPIOE.3 led0
    GPIOE->MODER &= ~(3<<(3*2));//清零
    GPIOE->MODER |= 1<<(3*2);//通用输出模式
    GPIOE->OTYPER &= ~(1<<3);//清零
    GPIOE->OTYPER |= (0<<3);//推挽输出
    GPIOE->ODR |= 1<<3;//默认设置led0灭
    //GPIOE.4 led1
    GPIOE->MODER &= ~(3<<(4*2));//清零
    GPIOE->MODER |= 1<<(4*2);//通用输出模式
    GPIOE->OTYPER &= ~(1<<4);//清零
    GPIOE->OTYPER |= (0<<4);//推挽输出
    GPIOE->ODR |= 1<<4;//默认设置led1灭
    //GPIOG.9 led2
    GPIOG->MODER &= ~(3<<(9*2));//清零
    GPIOG->MODER |= 1<<(9*2);//通用输出模式
    GPIOG->OTYPER &= ~(1<<9);//清零
    GPIOG->OTYPER |= (0<<9);//推挽输出
    GPIOG->ODR |= 1<<9;//默认设置led2灭
}


void drv_led_on(int led_no)
{
    switch(led_no)
    {				 
        case led0:	//led0亮(PE3)
            GPIOE->ODR &= ~(1<<3);
            break;
        case led1:	//led1亮(PE4)
            GPIOE->ODR &= ~(1<<4);
            break;
        case led2:	//led2亮(PG9)
            GPIOG->ODR &= ~(1<<9);
            break;
    }
}

void drv_led_off(int led_no)
{
    switch(led_no)
    {				 
        case led0:	//led0灭(PE3)
            GPIOE->ODR |= 1<<3;
            break;
        case led1:	//led1灭(PE4)
            GPIOE->ODR |= 1<<4;
            break;
        case led2:	//led2灭(PG9)
            GPIOG->ODR |= 1<<9;
            break;
    }
}

void drv_led_toggle(int ledx_pin)
{
    GPIOE->ODR &= (0x0000ffff);//清除高16位
    GPIOG->ODR &= (0x0000ffff);//清除高16位
    switch(ledx_pin)
    {				 
        case led0_pin:
            if ((GPIOE->ODR & (1<<ledx_pin)) == 0) {
                drv_led_off(led0);
            } else {
                drv_led_on(led0);
            }
            break;
        case led1_pin:
            if ((GPIOE->ODR & (1<<ledx_pin)) == 0) {
                drv_led_off(led1);
            } else {
                drv_led_on(led1);
            }
            break;
        case led2_pin:
            if ((GPIOG->ODR & (1<<ledx_pin)) == 0) {
                drv_led_off(led2);
            } else {
                drv_led_on(led2);
            }
            break;
    }
}

void liteos_led_flash(int led_no, unsigned int period)//peroid:闪烁周期，单位为ms
{
    drv_led_on(led_no);
    LOS_TaskDelay(period);
    //delay_ms(period);

    drv_led_off(led_no);
    LOS_TaskDelay(period);
    //delay_ms(period);
}
