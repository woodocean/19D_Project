/*
 * my_math_lib.c
 *
 *  Created on: 2024年7月19日
 *      Author: Lenovo
 */

#include "my_math_lib.h"


//
// encoding_wave()
// 这个函数可以将一个数值上的正弦波
// 转换成便于 OLED 屏幕显示的数组
// 其中，数组 p 的长度应该是 Width
// 数组 temp_BMP 的长度应该是 Width * Height
//
void encoding_wave(unsigned char*p,unsigned int width,unsigned char*temp_BMP,unsigned int BMP_width, unsigned int BMP_height)
{
    unsigned char i,j;
    unsigned char s;

    float a,b;

    unsigned char y[BMP_width];
    for(i=0;i<BMP_width;i++)
    {
        a = (float)(i*width)/BMP_width - (int)(i*width/BMP_width);
        b = (1-a)*p[i*width/BMP_width] + (a)*p[i*width/BMP_width+1];
        y[i] = (int)b;
    }

    for(i=0;i<BMP_width;i++)
    {
        for(j=0;j<BMP_height;j++)
        {
            if(j == y[i]/8)
            {
                s = y[i] - (y[i]/8)*8;
                temp_BMP[BMP_width*j + i] = 1<<s;
            }
        }
    }
}


//
// strfloat()
// 这个函数可以将一个 9999999.99 - 0.01 之间的小数
// 转换成为一个字符串
// 唯一需要注意的是这个字符串的长度应该要注意
// 其长度应该设置为10
//
void strfloat(float m, unsigned char *a)
{
    // 这个函数仅仅输出正数
    if(m<0)
        m = -m;
    int m_1000000,m_100000,m_10000,m_1000,m_100,m_10,m_1,m0_1,m0_01;
    m_1000000 = ((int)(m/1000000))%10;
    m_100000  = ((int)(m/100000 ))%10;
    m_10000   = ((int)(m/10000  ))%10;
    m_1000    = ((int)(m/1000   ))%10;
    m_100     = ((int)(m/100    ))%10;
    m_10      = ((int)(m/10     ))%10;
    m_1       = ((int)(m/1      ))%10;
    m0_1      = ((int)(m/0.1    ))%10;
    m0_01     = ((int)(m/0.01   ))%10;

    if(m>1000000)
    {
        a[0] = '0' + m_1000000;
        a[1] = '0' + m_100000 ;
        a[2] = '0' + m_10000  ;
        a[3] = '0' + m_1000   ;
        a[4] = '0' + m_100    ;
        a[5] = '0' + m_10     ;
        a[6] = '0' + m_1      ;
        a[7] = '.'            ;
        a[8] = '0' + m0_1     ;
        a[9] = '0' + m0_01    ;
    }
    else if(m>100000)
    {
        a[0] = '0' + m_100000 ;
        a[1] = '0' + m_10000  ;
        a[2] = '0' + m_1000   ;
        a[3] = '0' + m_100    ;
        a[4] = '0' + m_10     ;
        a[5] = '0' + m_1      ;
        a[6] = '.'            ;
        a[7] = '0' + m0_1     ;
        a[8] = '0' + m0_01    ;
        a[9] = '\0'           ;
    }
    else if(m>10000)
    {
        a[0] = '0' + m_10000  ;
        a[1] = '0' + m_1000   ;
        a[2] = '0' + m_100    ;
        a[3] = '0' + m_10     ;
        a[4] = '0' + m_1      ;
        a[5] = '.'            ;
        a[6] = '0' + m0_1     ;
        a[7] = '0' + m0_01    ;
        a[8] = '\0'           ;
        a[9] = '\0'           ;
    }
    else if(m>1000)
    {
        a[0] = '0' + m_1000   ;
        a[1] = '0' + m_100    ;
        a[2] = '0' + m_10     ;
        a[3] = '0' + m_1      ;
        a[4] = '.'            ;
        a[5] = '0' + m0_1     ;
        a[6] = '0' + m0_01    ;
        a[7] = '\0'           ;
        a[8] = '\0'           ;
        a[9] = '\0'           ;
    }
    else if(m>100)
    {
        a[0] = '0' + m_100    ;
        a[1] = '0' + m_10     ;
        a[2] = '0' + m_1      ;
        a[3] = '.'            ;
        a[4] = '0' + m0_1     ;
        a[5] = '0' + m0_01    ;
        a[6] = '\0'           ;
        a[7] = '\0'           ;
        a[8] = '\0'           ;
        a[9] = '\0'           ;
    }
    else if(m>10)
    {
        a[0] = '0' + m_10     ;
        a[1] = '0' + m_1      ;
        a[2] = '.'            ;
        a[3] = '0' + m0_1     ;
        a[4] = '0' + m0_01    ;
        a[5] = '\0'           ;
        a[6] = '\0'           ;
        a[7] = '\0'           ;
        a[8] = '\0'           ;
        a[9] = '\0'           ;
    }
    else if(m>1)
    {
        a[0] = '0' + m_1      ;
        a[1] = '.'            ;
        a[2] = '0' + m0_1     ;
        a[3] = '0' + m0_01    ;
        a[4] = '\0'           ;
        a[5] = '\0'           ;
        a[6] = '\0'           ;
        a[7] = '\0'           ;
        a[8] = '\0'           ;
        a[9] = '\0'           ;
    }
    else
    {
        a[0] = '0'            ;
        a[1] = '.'            ;
        a[2] = '0' + m0_1     ;
        a[3] = '0' + m0_01    ;
        a[4] = '\0'           ;
        a[5] = '\0'           ;
        a[6] = '\0'           ;
        a[7] = '\0'           ;
        a[8] = '\0'           ;
        a[9] = '\0'           ;
    }
}

