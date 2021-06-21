/*
 *
 * at_transmitter.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AT_TRANSMITTER_H
#define AT_TRANSMITTER_H

#include "usart.h"
#include "liteos.h"
#include "at_frame.h"
#include "stdint.h"
#include "bc35.h"

uint32_t send_cmd(at_cmd_args_s *args);

extern at_frame_args_s at_frame;

uint32_t send_payload(uint16_t socket, char* ip, uint32_t port, uint32_t length, char* data, int type);

#endif /* !AT_TRANSMITTER_H */
