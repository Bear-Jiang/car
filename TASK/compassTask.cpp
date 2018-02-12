#include "compassTask.h"

static Compass_t compass;
QueueHandle_t compass_queue_handle;

void compassTask(void* arg)
{
    compass_queue_handle = xQueueCreate(1,sizeof(CompassMsg_t));
    for(;;)
    {
        if(compass.cali.flag)
        {
            compass.readAngle();
        }
        else
        {
            if(!compass.cali.start)
            {
                compass.startCali();
            }
            if(compass.cali.finish)
            {
                compass.stopCali();
            }
            if(compass.cali.save)
            {
                compass.saveCali();
            }
        }
        if(compass.cali.factory)
        {
            compass.factory();
            compass.cali.factory = false;
        }
        vTaskDelay(500);
    }
    
}

Compass_t::Compass_t()
{
    cali.flag = true;
    cali.start = false;
    cali.finish = false;
    cali.factory = false;
    cali.save = false;
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

void Compass_t::startCali()
{
    send_buf[0] = 0x77;
    send_buf[1] = 0x04;
    send_buf[2] = 0x00;
    send_buf[3] = 0x60;
    send_buf[4] = 0x64;
    HAL_UART_Transmit_IT(&huart5,send_buf,5);
    return;
}

void Compass_t::stopCali()
{
    send_buf[0] = 0x77;
    send_buf[1] = 0x04;
    send_buf[2] = 0x00;
    send_buf[3] = 0x12;
    send_buf[4] = 0x16;
    HAL_UART_Transmit_IT(&huart5,send_buf,5);
    return;
}

void Compass_t::saveCali()
{
    send_buf[0] = 0x77;
    send_buf[1] = 0x04;
    send_buf[2] = 0x00;
    send_buf[3] = 0x09;
    send_buf[4] = 0x0d;
    HAL_UART_Transmit_IT(&huart5,send_buf,5);
}

void Compass_t::factory()
{
    send_buf[0] = 0x77;
    send_buf[1] = 0x04;
    send_buf[2] = 0x00;
    send_buf[3] = 0x0e;
    send_buf[4] = 0x12;
    HAL_UART_Transmit_IT(&huart5,send_buf,5);
}

void Compass_t::sendToCommander(void)
{
    xQueueSendFromISR(compass_queue_handle,(void*)&angle,NULL);
}

int test;

void unpackUART5_Data(uint8_t* p)
{
    int8_t flag = 0;
    if(p[0] == 0x77)
    {
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
            compass.sendToCommander();
        }
        else if(p[3] == 0x89)
        {
            compass.cali.flag = true;
            compass.cali.start = false;
            compass.cali.finish = false;
            compass.cali.save = false;
        }
        else if(p[3] == 0x26)
        {
//            compass.cali.finish = true;
            test++;
        }
        else if(p[3] == 0x8e)
        {
            compass.cali.factory = false;
        }
        else if(p[3] == 0x60)
        {
            compass.cali.start = true;;
        }
        else if(p[3] == 0x72)//finish cali
        {
            compass.cali.finish = false;
            compass.cali.save = true;
        }
    }
    
}


