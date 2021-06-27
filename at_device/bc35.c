/*
 * bc35.c
 * Copyright (C) 2021 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "bc35.h"
#include "hex2str_and_str2hex.h"
#include "pkg.h"

extern uint32_t send_cmd(at_cmd_args_s *args);

//teacher start-------------------------
extern uint32_t send_cmd_ex(at_cmd_args_s *args);

char receive_buf[256];
void at_device_svr_dn_msg_parse(char *buf, svr_dn_msg_parsed_s *p)
{
    //if (strstr(buf, "9020")) {
    //if (strstr(buf, "9000")) {
    if (strstr(buf, "8282")) {
    //if (strstr(buf, "+NSONMI:")) {
        char body[256];
        int match_cnt = sscanf(buf, "%d,%[^,],%d,%d,%[^,],%d", &(p->socket_id), p->ip, &(p->port), &(p->len), body, &(p->resp_code));
        
        if (match_cnt == 6) {
            printf("svr_dn_msg_match() buf:%s\r\n", buf);
            printf("match msg_data:\n");
            printf("socket_id:%d\n", p->socket_id);
            printf("server_ip:%s\n", p->ip);
            printf("port:%d\n", p->port);
            printf("body_len:%d\n", p->len);
            printf("body:%s\n", body);
            printf("resp_code:%d\n", p->resp_code);

            //char str_msg_body[256] = {0};//这里如果不初始化为0的话，解析出的str_msg_body会有一个<0x02>乱码,即msg_body_parsed打印出来会这样:msg_body_parsed:<0x02>hello world
            //hex2str(body, str_msg_body);
            hex2str_ex(body, p->data, p->len);
            printf("msg_body_parsed:%s\n", p->data);
            //p->data = str_msg_body;

            //解析服务器发来的响应包
            //pkg_head_s h;
            //pkg_obs_temp_humi_s p;
            //parse_temp_humi_pkg(str_msg_body, &h, &p);
        }
    }
}

//teacher ending-------------------------

//kalipy---------------------
uint32_t nb_cfun(uint8_t *presp)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    args.cmd = AT_CFUN;
    args.cmd_len = strlen(AT_CFUN);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
        }
    }

    return ret;

}
uint32_t nb_cimi(uint8_t *presp)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    args.cmd = AT_CIMI;
    args.cmd_len = strlen(AT_CIMI);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
        }
    }

    return ret;

}
uint32_t nb_csq(uint8_t *presp)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    args.cmd = AT_CSQ;
    args.cmd_len = strlen(AT_CSQ);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
        }
    }

    return ret;

}
uint32_t nb_cereg(uint8_t *presp)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    args.cmd = AT_CEREG;
    args.cmd_len = strlen(AT_CEREG);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
        }
    }

    return ret;

}
uint32_t nb_cgpaddr(uint8_t *presp)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    args.cmd = AT_CGPADDR;
    args.cmd_len = strlen(AT_CGPADDR);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
        }
    }

    return ret;

}
uint32_t nb_nping(uint8_t *presp)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    args.cmd = AT_NPING;
    args.cmd_len = strlen(AT_NPING);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
        }
    }

    return ret;

}
uint32_t nb_nsocr_udp(uint8_t *presp)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    args.cmd = AT_NSOCR;
    args.cmd_len = strlen(AT_NSOCR);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
        }
    }

    return ret;

}

//udp send data
uint32_t nb_nsost(uint8_t *presp, char * req_data)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    //args.cmd = AT_NSOST;
    //char t_cmd[256] = "AT+NSOST=1,123.57.44.108,8888,5,";//这个地方一定要写长度，不然liteos会死掉
    //char t_cmd[256] = "AT+NSOST=1,123.57.44.108,8888,";
    char t_cmd[256] = "AT+NSOST=1,122.112.145.221,9020,";

    char req_data_len[4];
    Int2String(strlen(req_data), req_data_len);//数字转字符串
    strcat(t_cmd, req_data_len);
    strcat(t_cmd, ",");
    
    char hex[256] = {0};
    str2hex(req_data, hex);
    strcat(t_cmd, hex);//数据载荷
    strcat(t_cmd, "\r");
    args.cmd = t_cmd;
    //args.cmd = AT_NSOST;
    printf("args.cmd:%s\r\n", args.cmd);
    
    //args.cmd_len = strlen(AT_NSOST);
    args.cmd_len = strlen(args.cmd);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
        }
    }

    return ret;

}

//tcp send data
uint32_t nb_nsosd(uint8_t *presp, char * req_data)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    //char t_cmd[256] = "AT+NSOSD=1,";//这个地方一定要写长度，不然liteos会死掉
    char t_cmd[256] = "AT+NSOSD=1,";

    char req_data_len[4];
    Int2String(strlen(req_data), req_data_len);//数字转字符串
    strcat(t_cmd, req_data_len);
    strcat(t_cmd, ",");
    
    char hex[256] = {0};
    str2hex(req_data, hex);
    strcat(t_cmd, hex);//数据载荷
    strcat(t_cmd, "\r");
    args.cmd = t_cmd;
    printf("args.cmd:%s\r\n", args.cmd);
    
    args.cmd_len = strlen(args.cmd);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
        }
    }

    return ret;

}

//tcp send data
uint32_t nb_nsosd_ex(uint8_t *presp, char * req_data,int data_len)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    //char t_cmd[256] = "AT+NSOSD=1,";//这个地方一定要写长度，不然liteos会死掉
    char t_cmd[256] = "AT+NSOSD=1,";

    char req_data_len[4];
    Int2String(data_len, req_data_len);//数字转字符串
    strcat(t_cmd, req_data_len);
    strcat(t_cmd, ",");
    
    char hex[256] = {0};
    str2hex_ex(req_data, hex, data_len);
    strcat(t_cmd, hex);//数据载荷
    strcat(t_cmd, "\r");
    args.cmd = t_cmd;
    printf("args.cmd:%s\r\n", args.cmd);
    
    args.cmd_len = strlen(args.cmd);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
        }
    }

    return ret;

}

uint32_t nb_nsorf(uint8_t *presp)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    args.cmd = AT_NSORF;
    args.cmd_len = strlen(AT_NSORF);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
        }
    }

    return ret;

}


//方法二
//uint32_t nb_cmd_resp_parse(void *pdata, uint8_t cmd_type)
//{
//
//}

