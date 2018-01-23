#include "compassTask.h"

static Compass_t compass;
QueueHandle_t compass_queue_handle;

void compassTask(void* arg)
{
    compass_queue_handle = xQueueCreate(1,sizeof(CompassMsg_t));
    for(;;)
    {
        compass.readAngle();
        vTaskDelay(500);
    }
    
}

Compass_t::Compass_t()
{
}

void Compass_t::readAngle()
{
    send_buf[0] = 0x77;
    send_buf[1] = 0x04;
    send_buf[2] = 0x00;
    send_buf[3] = 0x04;
    send_buf[4] = 0x08;
    HAL_UART_Transmit_IT(&huart5,send_buf,5);
    return;
}

void Compass_t::sendToCommander(void)
{
    xQueueSendFromISR(compass_queue_handle,(void*)&angle,NULL);
}

void unpackUART5_Data(uint8_t* p)
{
    int8_t flag = 0;
    if(p[3]==0x84)
    {
        flag = (p[4]&0x10)?-1:1;
        compass.angle.pitch = flag* ((p[4]&0x0f) * 100.0 \
                                + (p[5]&0x0f)+((p[5]>>4)&0x0f) * 10.0 \
                                + (p[6]&0x0f) * 0.1+((p[6]>>4)&0x0f) * 0.01);
        flag = (p[7]&0x10)?-1:1;
        compass.angle.roll = flag* ((p[7]&0x0f) * 100.0 \
                                + (p[8]&0x0f)+((p[8]>>4)&0x0f) * 10.0 \
                                + (p[9]&0x0f) * 0.1+((p[9]>>4)&0x0f) * 0.01);
        flag = (p[10]&0x10)?-1:1;
        compass.angle.heading = flag* ((p[10]&0x0f) * 100.0 \
                                + (p[11]&0x0f)+((p[11]>>4)&0x0f) * 10.0 \
                                + (p[12]&0x0f) * 0.1+((p[12]>>4)&0x0f) * 0.01);
        
    }
    compass.sendToCommander();
    
}


