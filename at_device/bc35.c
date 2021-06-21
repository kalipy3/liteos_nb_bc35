/*
 * bc35.c
 * Copyright (C) 2021 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "bc35.h"
#include "hex2str_and_str2hex.h"

extern uint32_t send_cmd(at_cmd_args_s *args);

//teacher start-------------------------
extern uint32_t send_cmd_ex(at_cmd_args_s *args);

char receive_buf[256];
char *at_device_svr_dn_msg_parse(char *buf, svr_dn_msg_parsed_s *p)
{
    char *str;
    if(NULL != (str = strstr(buf, "+NSONMI:")))//+NSONMI: <socket>,<remote_addr>,<remote_port>,<length>,<data>
    {
        if(5 != sscanf(str, "+NSONMI:%d,%[^,],%hu,%d,%s\r\n", &p->socket, &p->ip, &p->port, &p->len, receive_buf))
        {
            str = NULL;
        }
    }
    return str;
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
    char t_cmd[256] = "AT+NSOST=1,123.57.44.108,8888,";
    //char t_cmd[256] = "AT+NSOST=1,122.112.145.221,9020,";

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

