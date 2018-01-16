#include "adcTask.h"


static power_t power;

void adcTask(void* argument)
{
    portTickType tick = xTaskGetTickCount();
    for(;;)
    {
        vTaskDelayUntil(&tick,400);

        power.startCov();      
    }
}


void adcConvCpltCallback()
{
//    power.msg.current = power.buf[0] * 100;
//    power.msg.voltage = power.buf[1] * 100;
    power.sendToCommander();
    power.sendToRemote();
}

power_t::power_t()
{
    sendBuf[0] = 0xfe;
    sendBuf[1] = 0x0f;
    sendBuf[2] = 0x00;
//    sendBuf[3] = MSG_POWER_ID;
    sendBuf[14] = 0x0a;
}

void power_t::startCov(void)
{
    HAL_ADC_Start_DMA(&hadc1,(uint32_t*)buf,2);
}


void power_t::sendToCommander(void)
{
//    osMessageQueuePut(power_MsgQueue, &(msg), 0, NULL);
}

void power_t::sendToRemote(void)
{
//    for(uint8_t i=0;i<sizeof(msg);i++)
//    {
////        sendBuf[4+i] = *((uint8_t*)&msg+i);
//    }
//    remoteSend(sendBuf,sendBuf[1]);
}



