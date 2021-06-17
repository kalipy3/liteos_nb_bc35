/*
 * connector.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "liteos.h"
#include "at_usart.h"
#include "usart_debug.h"
#include "bc35.h"

void Create_BC35_Connectiontor_Task(void);

#endif /* !CONNECTOR_H */
