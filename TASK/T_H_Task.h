#ifndef _T_H_TASK_H__
#define _T_H_TASK_H__
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"

#define     noACK           0
#define     ACK             1
#define STATUS_REG_W        0x06
#define STATUS_REG_R        0x07
#define MEASURE_TEMP        0x03
#define MEASURE_HUMI        0x05
#define SENS_RESET          0x1e


#define W_DATA(x)    (x?HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET))

#define R_DATA()              HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1)

#define CLK_0()               HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);
#define CLK_1()               HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);     

class temp_humidity_t
{
public:
    temp_humidity_t();
    void dataReadEnable();
    void dataWriteEnable();
    uint8_t writeByte(uint8_t value);
    uint8_t readByte(uint8_t ack);
    void transStart();
    void connectionReset();
    uint8_t softReset();
    uint8_t readStatusReg(uint8_t* value,uint8_t* checksum);
    uint8_t writeStatusReg(uint8_t* value);
    uint8_t mesure(uint8_t* value,uint8_t* checksum,uint8_t mode);

private:
    GPIO_InitTypeDef GPIO_InitStruct;
//    uint8_t humi,temp;

};


void T_H_Task(void* arg);

#endif  /* _T_H_TASK_H__ */

