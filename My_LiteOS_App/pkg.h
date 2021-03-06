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
#include "adxl345.h"

uint16_t get_check_sum(uint16_t len);

void build_head(uint16_t len, uint8_t type, uint8_t seq);

void build_tail(uint16_t len);

pkg_s build_temp_humi_pkg(float temp, float humi);

void parse_temp_humi_pkg(char *raw_pkg, pkg_head_s *h, pkg_obs_temp_humi_s *p);

void parse_pkg_act_pkg(char *raw_pkg, pkg_head_s *h, pkg_act_s *p);

pkg_s build_pkg_act_resp_pkg(pkg_head_s *args_h, pkg_act_s *args_p, uint8_t resp_code);

pkg_s build_bind_termid_to_uid_pkg();
void parse_bind_termid_to_uid_pkg(char *raw_pkg, pkg_head_s *h, pkg_act_s *p);
void parse_bind_termid_to_uid_resp_pkg(char *raw_pkg, pkg_head_s *h, pkg_act_resp_s *p);

//温度湿度获取请求包的解析和响应
void parse_pkg_observer_pkg(char *raw_pkg, pkg_head_s *h, pkg_observer_s *p);
pkg_s build_pkg_observer_resp_pkg(pkg_head_s *args_h, pkg_observer_s *args_p, float temp, float humi, uint8_t resp_code);

//adxl数据获取请求包的解析和响应
void parse_pkg_observer_adxl_pkg(char *raw_pkg, pkg_head_s *h, pkg_observer_s *p);
pkg_s build_pkg_observer_adxl_resp_pkg(pkg_head_s *args_h, pkg_observer_s *args_p, Adxl345_data *adxl_data, uint8_t resp_code);

//adxl检测到老人摔倒后，iot给php发报警请求包，和iot对php响应包的解析
pkg_s build_adxl_alarm_pkg();
void parse_adxl_alarm_resp_pkg(char *raw_pkg, pkg_head_s *h, pkg_act_resp_s *p);

#endif /* !PKG_H */
