/*
 * adxl345.h
 * Copyright (C) 2021 kalipy <kalipy@debian>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ADXL345_H
#define ADXL345_H

#include <stdint.h>
#include "i2c.h"

#define    DEVICE_ID        0x00    //器件ID,0xE5
#define    THRESH_TAP       0x1D    //敲击阈值
#define    OFSX             0x1E    //X轴偏移
#define    OFSY             0x1F    //Y轴偏移
#define    OFSZ             0x20    //Z轴偏移
#define    DUR              0x21    //敲击持续时间
#define    Latent           0x22    //敲击延时
#define    Window           0x23    //敲击窗口
#define    THRESH_ACT       0x24    //活动阈值
#define    THRESH_INACT     0x25    //静止阈值
#define    TIME_INACT       0x26    //静止时间
#define    ACT_INACT_CTL    0x27    //轴使能控制活动和静止检测
#define    THRESH_FF        0x28    //自由落体阈值
#define    TIME_FF          0x29    //自由落体时间
#define    TAP_AXES         0x2A    //单击/双击轴控制
#define    ACT_TAP_STATUS   0x2B    //单击/双击源
#define    BW_RATE          0x2C    //数据速率及功率模式控制
#define    POWER_CTL        0x2D    //省电特性控制
#define    INT_ENABLE       0x2E    //中断使能控制
#define    INT_MAP          0x2F    //中断映射控制
#define    INT_SOURCE       0x30    //中断源
#define    DATA_FORMAT      0x31    //数据格式控制
#define    DATA_X0           0x32    //X轴数据0
#define    DATA_X1           0x33    //X轴数据1
#define    DATA_Y0           0x34    //Y轴数据0
#define    DATA_Y1           0x35    //Y轴数据1
#define    DATA_Z0           0x36    //Z轴数据0
#define    DATA_Z1           0x37    //Z轴数据1
#define    FIFO_CTL         0x38    //FIFO控制
#define    FIFO_STATUS      0x39    //FIFO状态
//如果ALT ADDRESS脚(12脚)接地，ADXL 7位地址为0x53，第8位为R/W,0xA7为读，0xA6为写
//如果ALT ADDRESS脚(12脚)接3.3V，ADXL 7位地址为0x1D，第8位为R/W,0x3B为读，0x3A为写
#define     ADXL_READ       0xA7
#define     ADXL_WRITE      0xA6

typedef struct Adxl345_data
{
    int16_t x;
    int16_t y;
    int16_t z;
    float xang;
    float yang;
    float zang;
} Adxl345_data;

/*ADXL345初始化函数：成功返回0，失败返回1*/
uint8_t ADXL345_Init(void);	  
/*读取ADXL345三个轴的数据*/
void ADXL345_RD_XYZ(short *x,short *y,short *z);
/*读取ADXL345的数据并做滤波处理，读times次再取平均值*/
void ADXL345_Read_Average(short *x,short *y,short *z,uint8_t times);

/*计算ADXL345角度，x/y/表示各方向上的加速度分量，dir表示要获得的角度*/
float ADXL345_Get_Angle(short x,short y,short z,uint8_t dir);

/*ADXL345自动校准函数*/
void ADXL345_AUTO_Adjust(char *xval,char *yval,char *zval);

/*数据处理函数*/
void data_pros();

void adxl345_data_get(Adxl345_data *adxl_data);

#endif /* !ADXL345_H */
