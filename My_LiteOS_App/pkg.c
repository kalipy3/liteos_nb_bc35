/*
 * pkg.c
 * Copyright (C) 2021 2021-06-23 16:10 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "pkg.h"

char pkg_buf[1024] = {'I', 'O', 'T'};
int32_t term_id = 1000;

uint16_t get_check_sum(uint16_t len)
{
    uint16_t sum = 0;
    uint16_t *p;
    p = (uint16_t *)pkg_buf;
    for (int i = 0; i < len; i++)
    {
        sum += *(p+i);
    }
    if (len%2 != 0)//奇数个字节
    {
        sum += pkg_buf[len];
    }
    return sum;
}

void build_head(uint16_t len, uint8_t type)
{
    pkg_head_s *p;
    p = (pkg_head_s *)pkg_buf;
    p->tag[0] = 'I';
    p->tag[1] = 'O';
    p->tag[2] = 'T';
    p->len = len;
    p->type = type;
    p->id = term_id;
    p->check_sum = 0;
}

void build_tail(uint16_t len)
{
    snprintf(pkg_buf+len-2, 10, "%s", "\r\n");
}

pkg_s build_temp_humi_pkg(float temp, float humi)
{
    uint16_t len;
    pkg_obs_temp_humi_s *p;
    pkg_head_s *h;

    p = (pkg_obs_temp_humi_s *)(pkg_buf + sizeof(pkg_head_s));
    p->humi = humi;
    p->temp = temp;
    p->target = TARGET_TEMP_HUMI;
    len = sizeof(pkg_head_s) + sizeof(pkg_obs_temp_humi_s) + 2;
    build_head(len, PKG_OBSV);
    build_tail(len);
    h = (pkg_head_s *)pkg_buf;
    h->check_sum = get_check_sum(len);

    pkg_s pkg;
    pkg.pkg_buf = pkg_buf;
    pkg.pkg_len = len;

    return pkg;
}

void parse_temp_humi_pkg(char *raw_pkg, pkg_head_s *h, pkg_obs_temp_humi_s *p)
{
    memcpy((void *)h, (void *)raw_pkg, sizeof(pkg_head_s));
    printf("--pkg_head_s--\r\n");
    printf("h.id:%d\r\n",h->id);
    printf("h.check_sum:%d\r\n",h->check_sum);
    printf("h.tag:%s\r\n",h->tag);
    printf("h.len:%d\r\n",h->len);
    printf("h.type:%d\r\n\r\n",h->type);

    memcpy((void *)p, (void *)(raw_pkg+sizeof(pkg_head_s)), sizeof(pkg_obs_temp_humi_s));
    printf("--pkg_obs_temp_humi_s--\r\n");
    printf("p.humi:%f\r\n",p->humi);
    printf("p.temp:%f\r\n",p->temp);
    printf("p.target:%d\r\n\r\n",p->target);
}

//typedef struct {
//    uint8_t target;
//    uint8_t act;
//} pkg_act_s;
//绑定iot的termid到php服务端的uid
pkg_s build_bind_termid_to_uid_pkg()
{
    uint16_t len;
    pkg_act_s *p;
    pkg_head_s *h;

    p = (pkg_act_s *)(pkg_buf + sizeof(pkg_head_s));
    p->target = TARGET_IOT;
    p->act = ACT_BIND_TERMID_TO_UID;
    len = sizeof(pkg_head_s) + sizeof(pkg_act_s) + 2;
    build_head(len, PKG_ACTION);
    build_tail(len);
    h = (pkg_head_s *)pkg_buf;
    h->check_sum = get_check_sum(len);

    pkg_s pkg;
    pkg.pkg_buf = pkg_buf;
    pkg.pkg_len = len;

    return pkg;
}

void parse_bind_termid_to_uid_pkg(char *raw_pkg, pkg_head_s *h, pkg_act_s *p)
{
    memcpy((void *)h, (void *)raw_pkg, sizeof(pkg_head_s));
    printf("--pkg_head_s--\r\n");
    printf("h.id:%d\r\n",h->id);
    printf("h.check_sum:%d\r\n",h->check_sum);
    printf("h.tag:%s\r\n",h->tag);
    printf("h.len:%d\r\n",h->len);
    printf("h.type:%d\r\n\r\n",h->type);

    memcpy((void *)p, (void *)(raw_pkg+sizeof(pkg_head_s)), sizeof(pkg_act_s));
    printf("--pkg_act_s--\r\n");
    printf("p.act:%d\r\n",p->act);
    printf("p.target:%d\r\n\r\n",p->target);
}
