/*
 * bc35.c
 * Copyright (C) 2021 2021-05-21 10:42 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "bc35.h"

extern uint32_t send_cmd(at_cmd_args_s *args);

uint32_t nb_reboot(void)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    args.cmd = NB_REBOOT;
    args.cmd_len = strlen(NB_REBOOT);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    return ret;
}

uint32_t nb_get_fun(uint8_t *pfun)
{
    uint32_t ret;
    at_cmd_args_s args;
    const char *resp[] = {"OK", "ERROR"};

    args.cmd = NB_GET_FUN;
    args.cmd_len = strlen(NB_GET_FUN);
    args.resp_strs_expected = resp;
    args.resp_strs_expected_num = 2;
    ret = send_cmd(&args);

    if (LOS_OK == ret)
    {
        if (0 == args.match_idx)
        {
            sscanf(args.resp_buf, "CFUN:%d", pfun);
        }
    }

    return ret;
}

//方法二
//uint32_t nb_cmd_resp_parse(void *pdata, uint8_t cmd_type)
//{
//
//}
