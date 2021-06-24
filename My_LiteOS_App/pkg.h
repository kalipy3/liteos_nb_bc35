/*
 * pkg.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PKG_H
#define PKG_H

#include "pkg_typedef.h"
#include "stdint.h"
#include "string.h"

#define TARGET_TEMP_HUMI 0x01
#define PKG_OBSV 0x02

uint16_t get_check_sum(uint16_t len);

void build_head(uint16_t len, uint8_t type);

pkg_s build_temp_humi_pkg(float temp, float humi);

void parse_temp_humi_pkg(char *raw_pkg, pkg_head_s *h, pkg_obs_temp_humi_s *p);

#endif /* !PKG_H */
