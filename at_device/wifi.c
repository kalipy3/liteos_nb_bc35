#include "stm32f4xx.h"  
#include "wifi.h"	    
#include "usart3.h"	    
#include "my_http.h"  
#include "liteos.h"

char wifi_mode = 0;         //联网模式 0：SSID和密码写在程序里
char Connect_flag = 0;      //同服务器连接状态  0：还没有连接服务器  1：连接上服务器了
	
void WiFi_ResetIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode =GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
}

char WiFi_SendCmd(char *cmd, int timeout)
{
	WiFi_RxCounter=0;                                                   
	memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);      
	WiFi_printf("%s\r\n",cmd);                
	while(timeout--){                        
		//Delay_Ms(100);
        LOS_TaskDelay(100);
		if(strstr(WiFi_RX_BUF,"OK"))
			break;
		u3_printf("%d ",timeout);
	}
	u3_printf("\r\n");                          
	if(timeout<=0)return 1;                     //如果timeout<=0，说明超时时间到了，也没能收到OK，返回1
	else return 0;		         				//反之，表示正确，说明收到OK，通过break主动跳出while
}

char WiFi_Reset(int timeout)
{
	RESET_IO(0);                                    
    //Delay_Ms(500);                                  
    LOS_TaskDelay(500);
    RESET_IO(1);                                    	
    while(timeout--){                               
        //Delay_Ms(100);                              
        LOS_TaskDelay(100);
        if(strstr(WiFi_RX_BUF,"ready"))             //如果接收到ready表示复位成功
            break;       						    
        u3_printf("%d ",timeout);                   
    }
    u3_printf("\r\n");                              
    if(timeout<=0)return 1;                         
    else return 0;		         				    
}

char WiFi_JoinAP(int timeout)
{		
    WiFi_RxCounter=0;                               //WiFi接收数据量变量清零                        
    memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);         //清空WiFi接收缓冲区 
    WiFi_printf("AT+CWJAP=\"%s\",\"%s\"\r\n",SSID,PASS); //发送指令	
    while(timeout--){                               
        //Delay_Ms(1000);                             
        LOS_TaskDelay(1000);
        u3_printf("gg:%s\n", WiFi_RX_BUF);
        if(strstr(WiFi_RX_BUF,"WIFI GOT IP\r\n\r\nOK")) 
        //if(strstr(WiFi_RX_BUF,"OK")) 
            break;       						    
        u3_printf("%d ",timeout);                   
    }
    u3_printf("\r\n");                              
    if(timeout<=0)return 1;                         
    return 0;                                       
}

char WiFi_WaitAP(int timeout)
{		
    while(timeout--){                               
        LOS_TaskDelay(1000);
        if(strstr(WiFi_RX_BUF,"WIFI GOT IP"))       //如果接收到WIFI GOT IP表示成功
            break;       						    
        u3_printf("%d ",timeout);                   
    }
    u3_printf("\r\n");                              
    if(timeout<=0)return 1;                         
    return 0;                                       
}

char WiFi_GetIP(int timeout)
{
    char *presult1,*presult2;
    char ip[50];

    WiFi_RxCounter=0;                               
    memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);         
    WiFi_printf("AT+CIFSR\r\n");                    
    while(timeout--){                               
        //Delay_Ms(100);                            
        LOS_TaskDelay(100);
        if(strstr(WiFi_RX_BUF,"OK"))                
            break;       						    
        u3_printf("%d ",timeout);                   
    }
    u3_printf("\r\n");                              
    if(timeout<=0)return 1;                         
    else{
        presult1 = strstr(WiFi_RX_BUF,"\"");
        if( presult1 != NULL ){
            presult2 = strstr(presult1+1,"\"");
            if( presult2 != NULL ){
                memcpy(ip,presult1+1,presult2-presult1-1);
                u3_printf("ESP8266的IP地址：%s\r\n",ip);     //串口显示IP地址
                return 0;    //正确返回0
            }else return 2;  //未收到预期数据
        }else return 3;      //未收到预期数据	
    }
}

char WiFi_Get_LinkSta(void)
{
    char id_temp[10]={0};    //缓冲区，存放ID
    char sta_temp[10]={0};   //缓冲区，存放状态

    if(strstr(WiFi_RX_BUF,"CONNECT")){                 //如果接受到CONNECT表示有客户端连接	
        sscanf(WiFi_RX_BUF,"%[^,],%[^,]",id_temp,sta_temp);
        u3_printf("有客户端接入，ID=%s\r\n",id_temp);  
        WiFi_RxCounter=0;                                                      
        memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);         
        return 1;                                      //有客户端接入
    }else if(strstr(WiFi_RX_BUF,"CLOSED")){            //如果接受到CLOSED表示有链接断开	
        sscanf(WiFi_RX_BUF,"%[^,],%[^,]",id_temp,sta_temp);
        u3_printf("有客户端断开，ID=%s\r\n",id_temp);        
        WiFi_RxCounter=0;                                                           
        memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);              
        return 2;                                            //有客户端断开
    }else return 0;                                          //无状态改变	
}

char WiFi_Get_Data(char *data, char *len, char *id)
{
    char temp[10]={0};      //缓冲区
    char *presult;

    if(strstr(WiFi_RX_BUF,"+IPD")){      
        LOS_TaskDelay(10);
        sscanf(WiFi_RX_BUF,"%[^,],%[^,],%[^:]",temp,id,len);//截取各段数据，主要是id和数据长度	
        presult = strstr(WiFi_RX_BUF,":");                  //查找冒号。冒号后的是数据
        if( presult != NULL )                               //找到冒号
            sprintf((char *)data,"%s",(presult+1));         //冒号后的数据，复制到data
        WiFi_RxCounter=0;                                                            
        memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);              
        return 1;                                           //有数据到来
    } else return 0;                                        //无数据到来
}

char WiFi_SendData(char id, char *databuff, int data_len, int timeout)
{    
    int i;

    WiFi_RxCounter=0;                                                         
    memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);           
    WiFi_printf("AT+CIPSEND=%d,%d\r\n",id,data_len);  
    while(timeout--){                                 
        //Delay_Ms(10);                               
        LOS_TaskDelay(10);
        if(strstr(WiFi_RX_BUF,">"))                   
            break;       						      
        u3_printf("%d ",timeout);                     
    }
    if(timeout<=0)return 1;                                   
    else{                                                        	
        WiFi_RxCounter=0;                                     
        memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);                	
        for(i=0;i<data_len;i++)WiFi_printf("%c",databuff[i]); 
        while(timeout--){                                     
            LOS_TaskDelay(10);
            if(strstr(WiFi_RX_BUF,"SEND OK")){                //如果接受SEND OK，表示发送成功			 
                WiFi_RxCounter=0;                                                         
                memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);           		
                break;                                        
            } 
            if(strstr(WiFi_RX_BUF,"link is not valid")){      //如果接受link is not valid，表示连接断开			
                WiFi_RxCounter=0;                                                     
                memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);        			
                return 2;                                     
            }
        }
        if(timeout<=0)return 3;      
        else return 0;	            
    }	
}

char WiFi_Connect_Server(int timeout)
{	
	WiFi_RxCounter=0;                               //WiFi接收数据量变量清零                        
	memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);         //清空WiFi接收缓冲区   
	WiFi_printf("AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",tcp_server_ip,tcp_server_port);
	while(timeout--){                               
		//Delay_Ms(100);                              	
        LOS_TaskDelay(100);
        if(strstr(WiFi_RX_BUF ,"CONNECT"))          //接受到CONNECT表示连接成功
            break;                                  
        if(strstr(WiFi_RX_BUF ,"CLOSED"))           //接受到CLOSED表示服务器未开启
            return 1;                               
        if(strstr(WiFi_RX_BUF ,"ALREADY CONNECTED"))//如果接受到ALREADY CONNECTED已经建立连接
            return 2;                               
        u3_printf("%d ",timeout);                     
    }
    u3_printf("\r\n");                        
    if(timeout<=0)return 3;                   
    else                                      //连接成功，准备进入透传
    {
        u3_printf("ready into to toucuan mode\r\n");                  
        WiFi_RxCounter=0;                                                       
        memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);              
        WiFi_printf("AT+CIPSEND\r\n");                  //进入透传
        while(timeout--){                               
            //Delay_Ms(100);                              	
            LOS_TaskDelay(100);
            if(strstr(WiFi_RX_BUF,"\r\nOK\r\n\r\n>"))   
                break;                          
            u3_printf("%d ",timeout);             
        }
        if(timeout<=0)return 4;                 	
    }
    return 0;	                                	
}

char esp8266_connect_server(char * server_ip, int server_port, int timeout)
{	
	WiFi_RxCounter=0;                                                       
	memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);            
	WiFi_printf("AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",server_ip,server_port);
	while(timeout--){                               
        LOS_TaskDelay(100);
        if(strstr(WiFi_RX_BUF ,"CONNECT"))
            break;                                  
        if(strstr(WiFi_RX_BUF ,"CLOSED"))
            return 1;                               
        if(strstr(WiFi_RX_BUF ,"ALREADY CONNECTED"))
            return 2;                               
        u3_printf("%d ",timeout);                    
    }
    u3_printf("\r\n");                        
    if(timeout<=0)return 3;                   
    else                                      //连接成功，准备进入透传
    {
        u3_printf("ready into to toucuan mode\r\n");                  
        WiFi_RxCounter=0;                                                       
        memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);              
        WiFi_printf("AT+CIPSEND\r\n");                  
        while(timeout--){                               
            //Delay_Ms(100);                              	
            LOS_TaskDelay(100);
            if(strstr(WiFi_RX_BUF,"\r\nOK\r\n\r\n>"))   
                break;                          
            u3_printf("%d ",timeout);           
        }
        if(timeout<=0)return 4;                 	
    }
    return 0;	                                	
}

char WiFi_Close(int timeout)
{		
    LOS_TaskDelay(200);
    WiFi_printf("+++");                             //退出透传
    LOS_TaskDelay(1500);
    Connect_flag = 0;                               
    WiFi_RxCounter=0;                                                       
    memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);          
    WiFi_printf("AT+CIPCLOSE\r\n");                 	
    while(timeout--){                               
        LOS_TaskDelay(100);
        if(strstr(WiFi_RX_BUF,"OK"))                
            break;       						    
        u3_printf("%d ",timeout);                   
    }
    u3_printf("\r\n");                              
    if(timeout<=0)return 1;                         
    return 0;                                      
}

char WiFi_Init(void)
{		
    u3_printf("ready reset esp8266\r\n");                     
    if(WiFi_Reset(50)){                                
        u3_printf("reset failed,ready reboot esp8266\r\n");           
        return 1;                                      
    }else u3_printf("reset success\r\n");                   

    u3_printf("ready set STA mode\r\n");                  
    if(WiFi_SendCmd("AT+CWMODE=1",50)){                //设置STA模式
        u3_printf("set STA mode failed,ready reboot wifi\r\n");    
        return 2;                                      
    }else u3_printf("set STA mode success\r\n");            

    if(wifi_mode==0){                                      //如果联网模式=0：SSID和密码写在程序里 
        u3_printf("ready cexiao zidon link\r\n");                 
        if(WiFi_SendCmd("AT+CWAUTOCONN=0",50)){            //取消自动连接
            u3_printf("cexiao failed，ready reboot wifi\r\n");   
            return 3;                                      
        }else u3_printf("quxiao zidon link success\r\n");           

        u3_printf("ready link router\r\n");                   	
        if(WiFi_JoinAP(30)){                               
            u3_printf("link router fail, ready reboot wifi\r\n");     
            return 4;                                      	
        }else u3_printf("link router ok\r\n");             			
    }else{                                                
    }

    u3_printf("ready get ip addr\r\n");                   
    if(WiFi_GetIP(50)){                                
        u3_printf("get IP addr fail，ready reboot wifi\r\n");     
        return 10;                                     
    }else u3_printf("get IP addr ok\r\n");             

    u3_printf("ready start toucuan\r\n");                     
    if(WiFi_SendCmd("AT+CIPMODE=1",50)){               //开启透传
        u3_printf("start toucuan fail,ready reboot\r\n");       
        return 11;                                     
    }else u3_printf("turn off toucuan ok\r\n");               

    u3_printf("ready turn off duolu link\r\n");                 
    if(WiFi_SendCmd("AT+CIPMUX=0",50)){                //关闭多路连接
        u3_printf("turn off duolu link fail,ready reboot\r\n");   
        return 12;                                     
    }else u3_printf("turn off ok\r\n");           

    return 0;                                          
}
