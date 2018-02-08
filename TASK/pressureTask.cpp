#include "pressureTask.h"

static Pressure_t pressure;
QueueHandle_t pressure_queue_handle;

void pressureTask(void* argument)
{
    pressure_queue_handle = xQueueCreate(1,sizeof(PressureMsg_t));
    portTickType tick = xTaskGetTickCount();
    
    pressure.reset();
    vTaskDelay(1);
    pressure.readProm();
    for(;;)
    {
        vTaskDelayUntil(&tick,100);//10Hz
        
        pressure.calcP();
        pressure.sendToCommander();
    }
}

Pressure_t::Pressure_t(void)
{
}

void Pressure_t::sendToCommander(void)
{
    xQueueSend(pressure_queue_handle,(void*)&message_data,NULL);
}

void Pressure_t::reset(void)
{
    uint8_t cmd = 0x1e;
    HAL_I2C_Master_Transmit(&hi2c3,w_addr,&cmd,1,10);
}

void Pressure_t::readProm(void)
{
    uint8_t cmd = 0xa0;
    uint8_t buf[2];
    for(int i=0;i<7;i++)
    {
        HAL_I2C_Master_Transmit(&hi2c3,w_addr,&cmd,1,10);
        HAL_I2C_Master_Receive(&hi2c3,r_addr,buf,2,10);
        prom[i] = (buf[0]<<8)+buf[1];
        
        cmd += 0x02;
    }
   
}

void Pressure_t::calcP()
{
    uint8_t buf[3] = {0,0,0};
    uint8_t cmd = 0x56;
    HAL_I2C_Master_Transmit(&hi2c3,w_addr,&cmd,1,10);//Convert temprature
    vTaskDelay(10);
    cmd = 0x00;
    HAL_I2C_Master_Transmit(&hi2c3,w_addr,&cmd,1,10);
    HAL_I2C_Master_Receive(&hi2c3,r_addr,buf,3,10);
    tempratureRaw = (buf[0]<<16) + (buf[1]<<8) + buf[2];
    
    cmd = 0x46;
    HAL_I2C_Master_Transmit(&hi2c3,w_addr,&cmd,1,10);//Convert pressure
    vTaskDelay(10);
    cmd = 0x00;
    HAL_I2C_Master_Transmit(&hi2c3,w_addr,&cmd,1,10);
    HAL_I2C_Master_Receive(&hi2c3,r_addr,buf,3,10);
    pressureRaw = (buf[0]<<16) + (buf[1]<<8) + buf[2];
    
    dT = tempratureRaw - (prom[5]<<8);
    TEMP = 2000 + ((dT * prom[6])>>23);
    OFF = (prom[2]<<16) + ((prom[4] * dT)>>7);
    SENS = (prom[1]<<15) + ((prom[3] * dT)>>8);
    P = (((pressureRaw * SENS)>>21) - OFF)>>13;
    
    //º∆À„…Ó∂»
    message_data.depth = P/10.0;
}

int32_t Pressure_t::getP()
{
    return P;
}
