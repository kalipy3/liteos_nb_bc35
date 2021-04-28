/*
 * at_receiver.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AT_RECEIVER_H
#define AT_RECEIVER_H

void at_usart_msg_listen(void);
void at_usart_msg_dispater(char *buf, int len);
void at_cmd_resp_match(char *buf, int len);
void svr_dn_msg_match(char *buf, int len);
uint32_t create_at_receiver_task(void);

#endif /* !AT_RECEIVER_H */
