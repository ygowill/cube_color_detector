#ifndef CUBE_SOLVER_PCA9685_WIRINGPI_H
#define CUBE_SOLVER_PCA9685_WIRINGPI_H

#include <wiringPi.h>

/*******************************************************************************************
    该函数用于初始化pca9685的各个寄存器等状态
    addr是7位的i2c从机地址，返回的是linux标准的设备描述符，调用它的地方视作pca9685的设备描述符
    因为可以多个pca9685级联，通过设备描述符区别它们
    此驱动仅作为驱动舵机使用，周期固定死位20ms，不允许外部设置
********************************************************************************************/
int pca9685_init(unsigned char addr);

/*******************************************************************************************
    该函数用于设置指定通道的脉宽。
    fd是在pca9685_init时获得的设备描述符
    num是通道号（从0开始
    mk是脉宽单位是us
    周期固定为20ms
********************************************************************************************/
void pca9685_setmk(int fd, int num, int mk);


#endif //CUBE_SOLVER_PCA9685_WIRINGPI_H