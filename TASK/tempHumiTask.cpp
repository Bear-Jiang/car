//T for temprature;H for humidity;
#include "tempHumiTask.h"

static TempHumidity_t sens;
uint16_t humi,temp;
uint8_t checksum;
uint8_t error=0;
void tempHumiTask(void* arg)
{
    vTaskDelay(50);
    sens.connectionReset();
    vTaskDelay(50);
    for(;;)
    {
        error = sens.mesure((uint8_t*)&humi,&checksum,0);
        if(error)
        {
            sens.connectionReset();
        }
    }
}


TempHumidity_t::TempHumidity_t()
{
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
}


void TempHumidity_t::dataReadEnable()
{
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

void TempHumidity_t::dataWriteEnable()
{
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

uint8_t TempHumidity_t::writeByte(uint8_t value)
{
    uint8_t error = 0;
    dataWriteEnable();
    for(uint8_t i=0x80;i>0;i/=2)
    {
        if(i&value)
        {
            W_DATA(1);
        }
        else
        {
            W_DATA(0);
        }
        __nop();
        CLK_1();
        __nop();__nop();__nop();
        CLK_0();
        __nop();
    }
    W_DATA(1);
    __nop();
    dataReadEnable();
    CLK_1();
    error = R_DATA();
    CLK_0();
    return error;
}

uint8_t TempHumidity_t::readByte(uint8_t ack)
{
    uint8_t val = 0;
    dataWriteEnable();
    W_DATA(1);
    dataReadEnable();
    for(uint8_t i=0x80;i>0;i/=2)
    {
        CLK_1();
        if(R_DATA())
        {
            val = val|i;
        }
        CLK_0();
    }
    
    dataWriteEnable();
    W_DATA(!ack);
    __nop();
    CLK_1();
    __nop();__nop();__nop();
    CLK_0();
    __nop();
    W_DATA(1);
    return val;
    
}

void TempHumidity_t::transStart()
{
    dataWriteEnable();
    W_DATA(1);
    CLK_0();
    __nop();
    CLK_1();
    __nop();
    W_DATA(0);
    __nop();
    CLK_0();
    __nop();__nop();__nop();
    CLK_1();
    __nop();
    W_DATA(1);
    __nop();
    CLK_0();
}

void TempHumidity_t::connectionReset()
{
    dataWriteEnable();
    W_DATA(1);
    CLK_0();
    
    for(uint8_t i=0;i<9;i++)
    {
        CLK_1();
        CLK_0();
    }
    transStart();
}

uint8_t TempHumidity_t::softReset()
{
    uint8_t error = 0;
    connectionReset();
    error = writeByte(SENS_RESET);
    return error;
}

uint8_t TempHumidity_t::readStatusReg(uint8_t* value,uint8_t* checksum)
{
    uint8_t error = 0;
    transStart();
    error = writeByte(STATUS_REG_R);
    *value = readByte(ACK);
    *checksum = readByte(noACK);
    return error;
}

uint8_t TempHumidity_t::writeStatusReg(uint8_t* value)
{
    uint8_t error = 0;
    transStart();
    error += writeByte(STATUS_REG_W);
    error += writeByte(*value);
    return error;
}

uint8_t TempHumidity_t::mesure(uint8_t* value,uint8_t* checksum,uint8_t mode)
{
    uint8_t error = 0;
    transStart();
    if(mode==0)
    {
        error+=writeByte(MEASURE_TEMP);
    }
    else
    {
        error+=writeByte(MEASURE_HUMI);
    }
    
//    for(uint16_t i=0;i<65535;i++)
//    {
//        dataReadEnable();
//        if(R_DATA()==0)
//            break;
//    }
    vTaskDelay(400);
    if(R_DATA()) error+=1;
    *(value+1) = readByte(ACK);
    *value = readByte(ACK);
    *checksum = readByte(noACK);
    return error;
}


