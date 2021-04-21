/*
 * at_usart.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */
#include "at_device.h"

#ifndef AT_USART_H
#define AT_USART_H

void at_usart_init(void);
void at_usart_send(char *buf, uint16_t len);
void at_usart_irq_handle(void);
void at_usart_get_msg_data(char * msg_buf, at_usart_msg_s msg);

#endif /* !AT_USART_H */
