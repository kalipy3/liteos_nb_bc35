/*
 * server_msg_processor.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SERVER_MSG_PROCESSOR_H
#define SERVER_MSG_PROCESSOR_H

#include "at_device.h"
#include "liteos.h"
#include "at_frame.h"

uint32_t create_server_dn_msg_receiver_task(void);

#endif /* !SERVER_MSG_PROCESSOR_H */
