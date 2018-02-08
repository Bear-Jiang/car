#include "powerTask.h"

static Power_t power;
QueueHandle_t power_queue_handle;

void powerTask(void* argument)
{
    power_queue_handle = xQueueCreate(1,sizeof(PowerMsg_t));
    portTickType tick = xTaskGetTickCount();
    for(;;)
    {
        vTaskDelayUntil(&tick,500);

        power.startCov();      
    }
}

void adcConvCpltCallback()
{
    power.message_data.current = power.adc_buf[0] * 24.0/255.0;
    power.message_data.voltage = power.adc_buf[1] * 20.0/255.0;
    power.sendToCommander();
}

Power_t::Power_t()
{
}

void Power_t::startCov(void)
{
    HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adc_buf,2);
}

void Power_t::sendToCommander(void)
{
    xQueueSendFromISR(power_queue_handle,(void*)&message_data,NULL);
}



