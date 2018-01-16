#include "pressureTask.h"

static pressure_t pressure;

void pressureTask(void* argument)
{
    portTickType tick = xTaskGetTickCount();
    
    pressure.reset();   
    vTaskDelay(1);
    pressure.readProm();
    for(;;)
    {
        vTaskDelayUntil(&tick,40);//25Hz
        
        pressure.calcP();
        /*******发送压力数据至commander任务*****/
        pressure.sendToCommander();
        
        /**********发送压力数据至上位机*********/
        static uint8_t time_count = 0;
        time_count++;
        if(time_count==10)
        {
            time_count = 0;
            pressure.sendToRemote();
        }
    }
}

void unpackPressureData(uint8_t* buf)
{
    
}

pressure_t::pressure_t(void)
{
    sendBuf[0] = 0xfe;
    sendBuf[1] = 0x0b;
    sendBuf[2] = 0x00;
//    sendBuf[3] = MSG_PRESSURE_ID;
    sendBuf[10] = 0x0a;
}

void pressure_t::sendToRemote(void)
{
    for(uint8_t i=0;i<sizeof(depth);i++)
    {
        sendBuf[4+i] = *((uint8_t*)&depth+i);
    }
//    remoteSend(sendBuf,sendBuf[1]);
}

void pressure_t::sendToCommander(void)
{
//    osMessageQueuePut (pressure_MsgQueue, &(depth), 0, NULL);
}

void pressure_t::reset(void)
{
    uint8_t cmd = 0x1e;
    HAL_I2C_Master_Transmit(&hi2c3,w_addr,&cmd,1,10);
}

void pressure_t::readProm(void)
{
    uint8_t cmd = 0xa0;
    
    for(int i=0;i<7;i++)
    {
        HAL_I2C_Master_Transmit(&hi2c3,w_addr,&cmd,1,10);
        HAL_I2C_Master_Receive(&hi2c3,r_addr,(uint8_t*)(prom+i),2,10);
        cmd += 0x02;
    }
   
}

void pressure_t::calcP()
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
    depth = P;
}

int32_t pressure_t::getP()
{
    return P;
}
