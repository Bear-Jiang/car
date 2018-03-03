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
            if(compass.cali.save)
            {
                compass.saveCali();
            }
        }
        vTaskDelay(500);
    }
    
}

void unpackCompassData(uint8_t* p)
{
    if(p[0] == 0x01)
    {
        compass.cali.flag = false;
    }
    else
    {
        compass.cali.save = true;
    }
}

Compass_t::Compass_t()
{
    cali.flag = true;
    cali.start = false;
    cali.save = false;
}

void Compass_t::readAngle()
{
    send_buf[0] = 0x68;
    send_buf[1] = 0x04;
    send_buf[2] = 0x00;
    send_buf[3] = 0x04;
    send_buf[4] = 0x08;
    HAL_UART_Transmit_IT(&huart5,send_buf,5);
    return;
}

void Compass_t::startCali()
{
    send_buf[0] = 0x68;
    send_buf[1] = 0x04;
    send_buf[2] = 0x00;
    send_buf[3] = 0x08;
    send_buf[4] = 0x0c;
    HAL_UART_Transmit_IT(&huart5,send_buf,5);
    return;
}

void Compass_t::saveCali()
{
    send_buf[0] = 0x68;
    send_buf[1] = 0x04;
    send_buf[2] = 0x00;
    send_buf[3] = 0x0a;
    send_buf[4] = 0x0e;
    HAL_UART_Transmit_IT(&huart5,send_buf,5);
}

void Compass_t::sendToCommander(void)
{
    xQueueSendFromISR(compass_queue_handle,(void*)&message_data,NULL);
}

int test;

void unpackUART5_Data(uint8_t* p)
{
    if(p[0] == 0x68)
    {
        if(p[3] == 0x84)
        {
            compass.message_data.roll = (p[4]&0x0f) * 100.0 
                            + (p[5]>>4) * 10.0 + 
                            (p[5]&0x0f) + 
                            0.1 * (p[6]>>4) + 
                            0.001 * (p[6]&0x0f);
            compass.message_data.roll *= (p[4]>>4)==1?-1:1;
            
            compass.message_data.pitch = (p[7]&0x0f) * 100.0 
                            + (p[8]>>4) * 10.0 + 
                            (p[8]&0x0f) + 
                            0.1 * (p[9]>>4) + 
                            0.001 * (p[9]&0x0f);
            compass.message_data.pitch *= (p[7]>>4)==1?-1:1;
            
            compass.message_data.heading = (p[10]&0x0f) * 100.0 
                            + (p[11]>>4) * 10.0 + 
                            (p[11]&0x0f) + 
                            0.1 * (p[12]>>4) + 
                            0.001 * (p[12]&0x0f);
            compass.message_data.heading *= (p[10]>>4)==1?-1:1;
            compass.sendToCommander();
        }
        else if(p[3] == 0x88)
        {
            compass.cali.start = true;
        }
        else if(p[3] == 0x8a)
        {
            compass.cali.start = false;
            compass.cali.save = false;
            compass.cali.flag = true;
        }
    }
}


