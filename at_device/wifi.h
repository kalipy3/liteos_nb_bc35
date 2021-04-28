#ifndef __WIFI_H
#define __WIFI_H

extern char Connect_flag;  //外部变量声明，同服务器连接状态  0：还没有连接服务器  1：连接上服务器了

#define RESET_IO(x) HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, x);
#define WiFi_printf       u4_printf           //串口4控制 WiFi
#define WiFi_RxCounter    Usart4_RxCounter    //串口4控制 WiFi
#define WiFi_RX_BUF       Usart4_RxBuff       //串口4控制 WiFi
#define WiFi_RXBUFF_SIZE  USART4_RXBUFF_SIZE  //串口4控制 WiFi

#define SSID   "aabbcc"                     //路由器SSID名称
#define PASS   "Abcd1234"                 //路由器密码

void WiFi_ResetIO_Init(void);
char WiFi_SendCmd(char *cmd, int timeout);
char WiFi_Reset(int timeout);
char WiFi_JoinAP(int timeout);
char WiFi_Connect_Server(int timeout);
char WiFi_Smartconfig(int timeout);
char WiFi_WaitAP(int timeout);
char WiFi_GetIP(int timeout);
char WiFi_Get_LinkSta(void);
char WiFi_Get_Data(char *data, char *len, char *id);
char WiFi_SendData(char id, char *databuff, int data_len, int timeout);
char WiFi_Connect_Server(int timeout);
char WiFi_Close(int timeout);
char WiFi_Init(void);

char esp8266_connect_server(char * server_ip, int server_port, int timeout);
#endif


