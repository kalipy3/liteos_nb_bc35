/*
 * adxl345.c
 * Copyright (C) 2021 2021-06-21 08:57 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include "adxl345.h"
#include <math.h>

/*ADXL345初始化函数：成功返回0，失败返回1*/
uint8_t ADXL345_Init(void){				  
    uint8_t id,val;
    HAL_I2C_Mem_Read(&hi2c2,ADXL_READ,DEVICE_ID,I2C_MEMADD_SIZE_8BIT,&id,1,0xff);	
    printf("id:%x\r\n", id);
    if(id ==0XE5){  	//读器件ID，ADXL345的器件ID为0XE5
        val = 0x2B;		//低电平中断输出，13位全分辨率，输出数据右对齐，16g量程
        HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,DATA_FORMAT,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
        val = 0x0A;		//数据输出速度为100Hz
        HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,BW_RATE,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
        val = 0x28;		//链接使能，测量模式
        HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,POWER_CTL,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
        val = 0x00;		//不使用中断
        HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,INT_ENABLE,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
        HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,OFSX,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
        HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,OFSY,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
        HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,OFSZ,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
        return 0;
    }			
    return 1;	   								  
} 
/*读取ADXL345三个轴的数据*/
void ADXL345_RD_XYZ(short *x,short *y,short *z){
    uint8_t buf[6];						  		   
    HAL_I2C_Mem_Read(&hi2c2,ADXL_READ,DATA_X0,I2C_MEMADD_SIZE_8BIT,&buf[0],1,0xFF);
    HAL_I2C_Mem_Read(&hi2c2,ADXL_READ,DATA_X1,I2C_MEMADD_SIZE_8BIT,&buf[1],1,0xFF);
    HAL_I2C_Mem_Read(&hi2c2,ADXL_READ,DATA_Y0,I2C_MEMADD_SIZE_8BIT,&buf[2],1,0xFF);
    HAL_I2C_Mem_Read(&hi2c2,ADXL_READ,DATA_Y1,I2C_MEMADD_SIZE_8BIT,&buf[3],1,0xFF);
    HAL_I2C_Mem_Read(&hi2c2,ADXL_READ,DATA_Z0,I2C_MEMADD_SIZE_8BIT,&buf[4],1,0xFF);
    HAL_I2C_Mem_Read(&hi2c2,ADXL_READ,DATA_Z1,I2C_MEMADD_SIZE_8BIT,&buf[5],1,0xFF);	
    *x=(short)(((uint16_t)buf[1]<<8)+buf[0]); 	//DATA_X1为高位有效字节    
    *y=(short)(((uint16_t)buf[3]<<8)+buf[2]); 	//DATA_Y1为高位有效字节  	    
    *z=(short)(((uint16_t)buf[5]<<8)+buf[4]); 	//DATA_Z1为高位有效字节  	   
}
/*读取ADXL345的数据并做滤波处理，读times次再取平均值*/
void ADXL345_Read_Average(short *x,short *y,short *z,uint8_t times){
    uint8_t i;
    short tx,ty,tz;
    *x=0; *y=0; *z=0;
    if(times){
        for(i=0;i<times;i++){
            ADXL345_RD_XYZ(&tx,&ty,&tz);
            *x+=tx;	*y+=ty;	*z+=tz;
            LOS_TaskDelay(5);
        }
        *x/=times; *y/=times; *z/=times;
    }
}
/*计算ADXL345角度，x/y/表示各方向上的加速度分量，dir表示要获得的角度*/
short ADXL345_Get_Angle(float x,float y,float z,uint8_t dir){
    float temp;
    float res=0;	//弧度值
    switch(dir){
        case 0:		//0表示与Z轴的角度
            temp=sqrt((x*x+y*y))/z;
            res=atan(temp);
            break;
        case 1:		//1表示与X轴的角度
            temp=x/sqrt((y*y+z*z));
            res=atan(temp);
            break;
        case 2:		//2表示与Y轴的角度
            temp=y/sqrt((x*x+z*z));
            res=atan(temp);
            break;
    }
    return res*180/3.14;	//返回角度值
}

/*ADXL345自动校准函数*/
void ADXL345_AUTO_Adjust(char *xval,char *yval,char *zval){
    short tx,ty,tz;
    uint8_t i, val;
    short offx=0,offy=0,offz=0;
    val = 0x00;		//先进入休眠模式
    HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,POWER_CTL,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
    HAL_Delay(100);
    val = 0x2B;		//低电平中断输出，13位全分辨率，输出数据右对齐，16g量程
    HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,DATA_FORMAT,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);	
    val = 0x0A;		//数据输出速度为100Hz
    HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,BW_RATE,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
    val = 0x28;		//链接使能，测量模式
    HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,POWER_CTL,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
    val = 0x00;		//不使用中断
    HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,INT_ENABLE,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
    HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,OFSX,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
    HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,OFSY,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
    HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,OFSZ,I2C_MEMADD_SIZE_8BIT,&val,1,0xFF);
    HAL_Delay(12);
    for(i=0;i<10;i++){
        ADXL345_Read_Average(&tx,&ty,&tz,10);
        offx+=tx; offy+=ty; offz+=tz;
    }	 		
    offx/=10; offy/=10; offz/=10;
    *xval=-offx/4;
    *yval=-offy/4;
    *zval=-(offz-256)/4;
    HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,OFSX,I2C_MEMADD_SIZE_8BIT,(uint8_t *)xval,1,0xFF);
    HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,OFSY,I2C_MEMADD_SIZE_8BIT,(uint8_t *)yval,1,0xFF);
    HAL_I2C_Mem_Write(&hi2c2,ADXL_WRITE,OFSZ,I2C_MEMADD_SIZE_8BIT,(uint8_t *)zval,1,0xFF);	
}

/*数据处理函数*/
void data_pros(){
    short x,y,z;
    ADXL345_Read_Average(&x,&y,&z,10); 
    printf("x:%d\r\n", x);
    printf("y:%d\r\n", y);
    printf("z:%d\r\n", z);

    short xang,yang,zang;	
    xang=ADXL345_Get_Angle(x,y,z,1);
    yang=ADXL345_Get_Angle(x,y,z,2);
    zang=ADXL345_Get_Angle(x,y,z,0);
    printf("x_angle:%d\r\n", xang);
    printf("y_angle:%d\r\n", yang);
    printf("z_angle:%d\r\n", zang);
}

//获取adxl345的x,y,z坐标值和角度
void adxl345_data_get(Adxl345_data *adxl_data){
    short x,y,z;
    ADXL345_Read_Average(&x,&y,&z,10); 

    short xang,yang,zang;	
    xang=ADXL345_Get_Angle(x,y,z,1);
    yang=ADXL345_Get_Angle(x,y,z,2);
    zang=ADXL345_Get_Angle(x,y,z,0);

    adxl_data->y = y;
    adxl_data->z = z;
    adxl_data->xang = xang;
    adxl_data->yang = yang;
    adxl_data->zang = zang;
}
