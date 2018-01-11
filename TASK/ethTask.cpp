#include "ethTask.h"
#include "lwip.h"
#include "lwip/api.h"
#include "lwip/sys.h"
#include "lwip/ip_addr.h"
#include "string.h"
//StackType_t ethTaskStackBuffer[200];
//StaticTask_t ethTaskTCB;

static ip_addr_t DstIPaddr;
u8_t data[100]={'h','e','l','l','o','\0'};
u8_t recieveBuffer[200];
struct udp_pcb *upcb;

void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    u16_t a = p->len;
    memcpy((void*)recieveBuffer,p->payload,p->len);
    udp_sendto(upcb, p,addr,port);
    pbuf_free(p);
    
}


void ethTask(void* arg)
{
    MX_LWIP_Init();
    
    IP4_ADDR(&DstIPaddr,192,168,1,15);
    
    /**********************udp init*********************/
    err_t err;
    struct pbuf *p;
    upcb = udp_new();
    if (upcb!=NULL)
    {
        err = udp_bind(upcb, IP_ADDR_ANY, 7);
        err = udp_connect(upcb, &DstIPaddr, 5000);
        udp_recv(upcb, udp_receive_callback, NULL); 
        
        for(;;)
        {
            
            if(1)//模拟收到消息队列
            {
                int len = 6;
                p = pbuf_alloc(PBUF_TRANSPORT,len,PBUF_POOL);//allocate memory
                pbuf_take(p,(char*)data,len);//copy data to buf
                udp_send(upcb, p);//send udp data
                pbuf_free(p);
                
            }
            vTaskDelay(500);
        }
        
    }
    

}



