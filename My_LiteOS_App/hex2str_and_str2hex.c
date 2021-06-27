#include <hex2str_and_str2hex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//字符串数据转16进制字符串数据
//str="hello" --> hex="68656c6c6f"
//str="^&%$:.," --> hex="5e2625243a2e2c"
void str2hex(char * str, char * hex)
{
    printf("str_len:%d\r\n",strlen(str));

    char ahex[3];//1. 因为一个字符占用一个字节空间，表示为16进制数就是0x68(这里以字符'h'为例讲解),用字符数组存储就要三个字节空间，因为sprintf()会在ahex后自动加个'\0',所以0x68存储为字符串就是"68\0" //2. 其实一个16进制数占用的空间就等于一个8位char占用的空间，但是这里为什么不直接用8位的char来存储16进制数，因为sprintf( char *buffer, const char *format, [ argument] … ),即sprintf只允许传入一个char *buffer

    for (int i = 0; i < strlen(str); i++)
    {
        sprintf(ahex, "%02X", str[i]);//%2X中的02意思是，比如str[i]中的某个字符转换为ahex后，ahex是"1\0"时，左边补0,变为"01\0",只有这样我们的hex2str(char * hex, char * str)在解析参数hex时才不会出错(因为hex2str()里的for循环中的i是固定i+=2进行解析传入的hex字符串)
        printf("ahex:%s\n", ahex); 
        strcat(hex, ahex);//hex += ahex;
    }
    printf("hex_with_str:%s\n", hex); 
}

//结构体二进制专用
void str2hex_ex(char * str, char * hex,int str_len)
{
//printf("str_len:%d\r\n",str_len);

    char ahex[3];//1. 因为一个字符占用一个字节空间，表示为16进制数就是0x68(这里以字符'h'为例讲解),用字符数组存储就要三个字节空间，因为sprintf()会在ahex后自动加个'\0',所以0x68存储为字符串就是"68\0" //2. 其实一个16进制数占用的空间就等于一个8位char占用的空间，但是这里为什么不直接用8位的char来存储16进制数，因为sprintf( char *buffer, const char *format, [ argument] … ),即sprintf只允许传入一个char *buffer

    for (int i = 0; i < str_len; i++)
    {
        sprintf(ahex, "%02X", str[i]);//%2X中的02意思是，比如str[i]中的某个字符转换为ahex后，ahex是"1\0"时，左边补0,变为"01\0",只有这样我们的hex2str(char * hex, char * str)在解析参数hex时才不会出错(因为hex2str()里的for循环中的i是固定i+=2进行解析传入的hex字符串)
//printf("ahex:%s\n", ahex); 
        strcat(hex, ahex);//hex += ahex;
    }
//printf("hex_with_str:%s\n", hex); 
}

void hex2str(char * hex, char * str)
{
    printf("hex_len:%d\r\n",strlen(hex));
    char achar[10];
    for (int i = 0; i < strlen(hex); i += 2)
    {
        //sscanf("68", "%2x", achar);
        sscanf(hex+i, "%2X", achar);//%2x,取指定长度(这里是2个字节)的字符串,即每次只取hex中的2个字节数据
        printf("%s\n", achar);
        strcat(str, achar);//str += achar;
    }
    printf("str:%s\n", str); 

}

//结构体二进制专用
void hex2str_ex(char * hex, char * str, int hex_len)
{
//printf("hex_len:%d\r\n", hex_len);
    int j = 0;
    for (int i = 0; i < hex_len*2; i += 2, j++)
    {
        sscanf(hex+i, "%2X", &str[j]);//%2x,取指定长度(这里是2个字节)的字符串,即每次只取hex中的2个字节数据
//printf("%x \n", str[j]);
    }
}

void Int2String(int num,char *str)//10进制 
{
    int i = 0;//指示填充str 
    if(num<0)//如果num为负数，将num变正 
    {
        num = -num;
        str[i++] = '-';
    } 
    //转换 
    do
    {
        str[i++] = num%10+48;//取num最低位 字符0~9的ASCII码是48~57；简单来说数字0+48=48，ASCII码对应字符'0' 
        num /= 10;//去掉最低位    
    }while(num);//num不为0继续循环

    str[i] = '\0';

    //确定开始调整的位置 
    int j = 0;
    if(str[0]=='-')//如果有负号，负号不用调整 
    {
        j = 1;//从第二位开始调整 
        ++i;//由于有负号，所以交换的对称轴也要后移1位 
    }
    //对称交换 
    for(;j<i/2;j++)
    {
        //对称交换两端的值 其实就是省下中间变量交换a+b的值：a=a+b;b=a-b;a=a-b; 
        str[j] = str[j] + str[i-1-j];
        str[i-1-j] = str[j] - str[i-1-j];
        str[j] = str[j] - str[i-1-j];
    } 

}
//int main()
//{
//    char hex[100];
//    char str[100] = "^&%$:.,";
//    str2hex(str, hex);
//
//    char hex2[100] = "68656c6c6f";
//    char str2[100] = {0};
//    hex2str(hex2, str2);
//
//    return 0; 
//}
