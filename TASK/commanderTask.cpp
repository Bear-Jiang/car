#include "commanderTask.h"
#include "ledTask.h"
#include "ethTask.h"
#include "controlTask.h"
#include "powerTask.h"
#include "pressureTask.h"
#include "tempHumiTask.h"
#include "compassTask.h"


TaskHandle_t led_task_handle;
TaskHandle_t ctl_task_handle;
TaskHandle_t power_task_handle;
TaskHandle_t pressure_task_handle;
TaskHandle_t temp_humi_task_handle;
TaskHandle_t compass_task_handle;
TaskHandle_t eth_task_handle;

static PowerMsg_t power_data;
static CompassMsg_t compass_data;
static TempHumiMsg_t temp_humi_data;
static PressureMsg_t pressure_data;

static Remote_t remote_control;

static uint8_t receive_buf[30];
//static SemaphoreHandle_t receiveDataSem;

void commanderTask(void* arg)
{
    
    xTaskCreate(ledTask,"ledTask",100,NULL,6,&led_task_handle);
    xTaskCreate(ethTask,"ethTask",200,NULL,4,&eth_task_handle);
    xTaskCreate(controlTask,"ctlTask",50,NULL,7,&ctl_task_handle);
    xTaskCreate(powerTask,"powerTask",50,NULL,6,&power_task_handle);
    xTaskCreate(pressureTask,"pressureTask",100,NULL,3,&pressure_task_handle);
    xTaskCreate(tempHumiTask,"tempHumiTask",100,NULL,3,&temp_humi_task_handle);
    xTaskCreate(compassTask,"compassTask",100,NULL,4,&compass_task_handle);

//    receiveDataSem = xSemaphoreCreateBinary();
    
    vTaskDelay(1000);//Wait for subtask ready
    remote_control.udpInit();
    for(;;)
    {
        if(xQueueReceive(power_queue_handle,(void*)&power_data,0) == pdPASS)
        {
            remote_control.sendMsg(MSG_POWER_ID,(uint8_t*)&power_data,sizeof(power_data));
        }
        if(xQueueReceive(compass_queue_handle,(void*)&compass_data,0) == pdPASS)
        {
            remote_control.sendMsg(MSG_COMPASS_ID,(uint8_t*)&compass_data,sizeof(compass_data));
        }
        if((temp_humi_queue_handle != NULL) && (xQueueReceive(temp_humi_queue_handle,(void*)&temp_humi_data,0) == pdPASS))
        {
            remote_control.sendMsg(MSG_TEMP_HUMI_ID,(uint8_t*)&temp_humi_data,sizeof(temp_humi_data));
        }
        if((pressure_queue_handle != NULL) && (xQueueReceive(pressure_queue_handle,(void*)&pressure_data,0) == pdPASS))
        {
            remote_control.sendMsg(MSG_PRESSURE_ID,(uint8_t*)&pressure_data,sizeof(pressure_data));
        }
        
        
        
        vTaskDelay(10);
    }
}

__weak void unpackLedData(uint8_t* p)
{   
}

__weak void unpackGimbalData(uint8_t* p)
{   
}

__weak void unpackControlData(uint8_t* p)
{
}

void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    int len = p->len;
    memcpy((void*)receive_buf,p->payload,p->len);
//    udp_sendto(upcb, p,addr,port);
    pbuf_free(p);
    
    if((receive_buf[0] == 0xfe) && (receive_buf[1] == len) && (receive_buf[len-1] == 0x0a))
    {
        switch(receive_buf[3])
        {
            case MSG_GIMBAL_ID:
            {
                unpackGimbalData(receive_buf+4);
                break;
            }
            case MSG_LIGHT_ID:
            {
                unpackLedData(receive_buf+4);
                break;
            }
            case MSG_CMD_ID:
            {
                unpackControlData(receive_buf+4);
                break;
            }
        }
    }
}

Remote_t::Remote_t()
{
    send_buf[0] = 0xfe;
}

int8_t Remote_t::udpInit()
{
    IP4_ADDR(&dst_ip_addr,192,168,1,15);
    upcb = udp_new();
    if(upcb != NULL)
    {
        udp_bind(upcb, IP_ADDR_ANY, 7);
        udp_connect(upcb, &dst_ip_addr, 8000);
        udp_recv(upcb, udp_receive_callback, NULL); 
        return 0;
    }
    else
    {
        return -1;
    }
}

void Remote_t::sendMsg(uint8_t id,uint8_t* data,uint8_t len)
{
    static uint8_t count = 0;
    send_buf[1] = 7+len;
    send_buf[2] = count++;
    send_buf[3] = id;
    for(uint8_t i=0;i<len;i++)
    {
        send_buf[4+i] = *(data+i);
    }
    send_buf[len+6] = 0x0a;
    
    p = pbuf_alloc(PBUF_TRANSPORT,send_buf[1],PBUF_POOL);//allocate memory
    pbuf_take(p,(char*)send_buf,send_buf[1]);//copy data to buf
    udp_send(upcb, p);//send udp data
    pbuf_free(p);
            
}

void Remote_t::send()
{
    int len = 6;
    u8_t data[100]={'h','e','l','l','o','\0'};
    p = pbuf_alloc(PBUF_TRANSPORT,len,PBUF_POOL);//allocate memory
    pbuf_take(p,(char*)data,len);//copy data to buf
    udp_send(upcb, p);//send udp data
    pbuf_free(p);
}


