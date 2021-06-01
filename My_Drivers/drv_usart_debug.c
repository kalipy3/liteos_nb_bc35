/*
 * drv_usart_debug.c
 * Copyright (C) 2021 2021-05-27 10:40 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "drv_usart_debug.h"

static char at_usart_debug_rcv_buf[USART_DEBUG_RX_BUFFER_LEN];

UART_HandleTypeDef *at_debug_huart;
uint32_t at_usart_debug_msg_queue_id;

void at_usart_debug_init(void){
    uint32_t uwRet;
    
    at_debug_huart = &USART_DEBUG_HUART;
    
    __HAL_UART_ENABLE_IT(at_debug_huart, UART_IT_IDLE);
    __HAL_UART_ENABLE_IT(at_debug_huart, UART_IT_RXNE);
    __HAL_UART_CLEAR_FLAG(at_debug_huart, UART_FLAG_TC);
    __HAL_UART_ENABLE_IT(at_debug_huart, UART_IT_ERR);
    
    uwRet = LOS_QueueCreate("usart_debug_rececie_irq_idle_msgQueue", 5, &at_usart_debug_msg_queue_id, 0, sizeof(at_usart_msg_s));
    if(uwRet != LOS_OK)
    {
        printf("usart_debug_rececie_irq_idle_msgQueue Create failed, err_code:0x%x\r\n", uwRet);
    }

}

void at_usart_debug_irq_handler(void){
    UINT32 uwRet = 0;
    at_usart_msg_s msg;
    static uint32_t si = 0;
    static uint32_t ei = 0;

    if (__HAL_UART_GET_FLAG(at_debug_huart, UART_FLAG_RXNE)) {
        at_usart_debug_rcv_buf[ei++] = at_debug_huart->Instance->DR;
        
        if (ei >= RX_BUFFER_LEN) {
            ei = 0;
        }

        if (ei == si) {
            printf("the usart_debug buffer overflowed! please consume the msg as soon as possible!");
        }

    }

    else if (__HAL_UART_GET_FLAG(at_debug_huart, UART_FLAG_IDLE)) {
        __HAL_UART_CLEAR_IDLEFLAG(at_debug_huart);
        
        msg.si = si;
        msg.ei = ei;
        
        uwRet = LOS_QueueWriteCopy(at_usart_debug_msg_queue_id, &msg, sizeof(at_usart_msg_s) , 0);//把消息发往上层处理
        si = ei;
        
        if(uwRet != LOS_OK)
        {
            printf("send message failure,error:%x\n",uwRet);
        }
    }
}

//get到的msg_data保存到msg_buf
int at_usart_debug_get_msg_data(char * msg_buf, at_usart_msg_s msg) {

    if (msg.si < msg.ei) {//数据只有1段时
        uint32_t len = msg.ei - msg.si + 1;
        for (int i = 0; i < len; i++)
        {
            msg_buf[i] = at_usart_debug_rcv_buf[msg.si++];
        }

        printf("1:%s\n", (char *)msg_buf);
        return len;
    } else {//数据被分成2段时
        uint32_t len = (USART_DEBUG_RX_BUFFER_LEN - msg.si + 1) + (msg.ei + 1);//总的长度 = 后半部分长度+前半部分长度

        for(int i = 0; i < len; i++)
        {
            msg_buf[i] = at_usart_debug_rcv_buf[msg.si++];
            if (msg.si == USART_DEBUG_RX_BUFFER_LEN)
            {
                msg.si = 0;
            }
        }

        printf("2:%s\n", (char *)msg_buf);
        return len;
    }
}

//方法一
void at_usart_debug_send(char *buf, uint16_t len){
    HAL_UART_Transmit(at_debug_huart, (uint8_t *)buf, len, 0xFFFF);
}

//方法二
static char at_usart_debug_tx_buf[USART_DEBUG_TX_BUFFER_LEN];
void my_usart_debug_printf(char* fmt,...) 
{  
    unsigned int i,length;

    va_list ap;
    va_start(ap,fmt);
    vsprintf(at_usart_debug_tx_buf,fmt,ap);
    va_end(ap);	
    
    length=strlen((const char*)at_usart_debug_tx_buf);		
    while((at_debug_huart->Instance->SR&0X40)==0);
    for(i = 0;i < length;i ++)
    {			
        at_debug_huart->Instance->DR = at_usart_debug_tx_buf[i];
        while((at_debug_huart->Instance->SR&0X40)==0);	
    }	
}

//方法三见usart.c
