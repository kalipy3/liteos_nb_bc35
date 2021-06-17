/*
 * bc35.c
 * Copyright (C) 2021 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "bc35.h"
#include <hex2str_and_str2hex.h>

extern uint32_t send_cmd(at_cmd_args_s *args);

//uint32_t nb_reboot(void)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = NB_REBOOT;
//    args.cmd_len = strlen(NB_REBOOT);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    return ret;
//}
//
//uint32_t nb_get_fun(uint8_t *pfun)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//    
//    args.cmd = NB_GET_FUN;
//    args.cmd_len = strlen(NB_GET_FUN);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "+CFUN:%d", pfun);
//        }
//    }
//
//    return ret;
//}
//
//uint32_t nb_set_full_fun(uint8_t *pfun)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_SET_FULL_FUNC;
//    args.cmd_len = strlen(AT_SET_FULL_FUNC);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "%s", pfun);
//        }
//    }
//
//    return ret;
//}
//
//uint32_t nb_set_mini_fun(uint8_t *pfun)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_SET_MINI_FUNC;
//    args.cmd_len = strlen(AT_SET_MINI_FUNC);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "%s", pfun);
//        }
//    }
//
//    return ret;
//}
//uint32_t nb_enble_error_report(uint8_t *presp)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_SET_ERROR_INDICATOR;
//    args.cmd_len = strlen(AT_SET_ERROR_INDICATOR);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "%s", presp);
//        }
//    }
//
//    return ret;
//}
//
////#define AT_DISABLE_HUAWEI_PLATFORM  "AT+QREGSWT=2\r"
//uint32_t nb_need_huawei_platform(uint8_t *presp)//disable_registration
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_DISABLE_HUAWEI_PLATFORM;
//    args.cmd_len = strlen(AT_DISABLE_HUAWEI_PLATFORM);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "%s", presp);
//        }
//    }
//
//    return ret;
//}
//
////#define AT_ATTACH_NETWORR           "AT+CGATT=1\r"
//uint32_t nb_attach2server(uint8_t *presp)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_ATTACH_NETWORR;
//    args.cmd_len = strlen(AT_ATTACH_NETWORR);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "%s", presp);
//        }
//    }
//
//    return ret;
//}
//
////#define AT_GET_ATTACH_STATE         "AT+CGATT?\r"
//uint32_t nb_get_attach_state(uint8_t *presp)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_GET_ATTACH_STATE;
//    args.cmd_len = strlen(AT_GET_ATTACH_STATE);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "+CGATT:%d", presp);
//        }
//    }
//
//    return ret;
//}
//
////#define AT_CLEAR_PRIOR_FREQ_CHANNEL "AT+NCSEARFCN\r"
//uint32_t nb_clear_stored_EARFCN(uint8_t *presp)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_CLEAR_PRIOR_FREQ_CHANNEL;
//    args.cmd_len = strlen(AT_CLEAR_PRIOR_FREQ_CHANNEL);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "%s", presp);
//        }
//    }
//
//    return ret;
//}
////#define AT_SET_MESSAGE_INDICATOR    "AT+NSONMI=2\r"
//uint32_t nb_set_socket_msg_indicator(uint8_t *presp)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_SET_MESSAGE_INDICATOR;
//    args.cmd_len = strlen(AT_SET_MESSAGE_INDICATOR);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "%s", presp);
//        }
//    }
//
//    return ret;
//}
////#define AT_GET_SIGNAL_STRENGTH      "AT+CSQ\r"
//uint32_t nb_get_signal_len(uint8_t *presp)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_GET_SIGNAL_STRENGTH;
//    args.cmd_len = strlen(AT_GET_SIGNAL_STRENGTH);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "+CSQ:%d", presp);
//        }
//    }
//
//    return ret;
//}
////#define AT_GET_IMEI                 "AT+CGSN=1\r"
//uint32_t nb_get_IMEI(uint8_t *presp)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_GET_IMEI;
//    args.cmd_len = strlen(AT_GET_IMEI);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "+CGSN:%s", presp);
//        }
//    }
//
//    return ret;
//}
////#define AT_GET_IP                   "AT+CGPADDR\r"
//uint32_t nb_get_IP(uint8_t *presp)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_GET_IMEI;
//    args.cmd_len = strlen(AT_GET_IMEI);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "+CGPADDR:%s", presp);
//        }
//    }
//
//    return ret;
//}
//
////#define AT_CREATE_SOCKET_TCP        "AT+NSOCR=STREAM,6,8888"
//uint32_t nb_create_tcp_socket(uint8_t *presp)
//{
//    uint32_t ret;
//    at_cmd_args_s args;
//    const char *resp[] = {"OK", "ERROR"};
//
//    args.cmd = AT_CREATE_SOCKET_TCP;
//    args.cmd_len = strlen(AT_CREATE_SOCKET_TCP);
//    args.resp_strs_expected = resp;
//    args.resp_strs_expected_num = 2;
//    ret = send_cmd(&args);
//
//    if (LOS_OK == ret)
//    {
//        if (0 == args.match_idx)
//        {
//            sscanf(args.resp_buf, "%s", presp);
//        }
//    }
//
//    return ret;
//}

//---------------------
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
uint32_t nb_nsost(uint8_t *presp, char * req_data)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    //args.cmd = AT_NSOST;
    //char t_cmd[256] = "AT+NSOST=1,123.57.44.108,8888,5,";//这个地方一定要写长度，不然liteos会死掉
    char t_cmd[256] = "AT+NSOST=1,123.57.44.108,8888,";

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

