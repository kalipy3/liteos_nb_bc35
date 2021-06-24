/*
 * hex2str_and_str2hex.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef HEX2STR_AND_STR2HEX_H
#define HEX2STR_AND_STR2HEX_H

//字符串数据转16进制字符串数据
//str="hello" --> hex="68656c6c6f"
//str="^&%$:.," --> hex="5e2625243a2e2c"
void str2hex(char * str, char * hex);

void str2hex_ex(char * str, char * hex,int str_len);

void hex2str(char * hex, char * str);

void hex2str_ex(char * hex, char * str, int hex_len);

void Int2String(int num,char *str);

#endif /* !HEX2STR_AND_STR2HEX_H */
