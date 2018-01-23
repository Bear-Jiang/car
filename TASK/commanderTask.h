#ifndef _COMMANDER_TASK_H__
#define _COMMANDER_TASK_H__

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stm32f4xx_hal.h"
#include "lwip.h"
#include "lwip/api.h"
#include "lwip/sys.h"
#include "lwip/ip_addr.h"
#include "string.h"
/* Exported types ------------------------------------------------------------*/
class Commander_t
{
public:
    Commander_t();

private:

};

class Remote_t
{
public:
    Remote_t();
    int8_t udpInit();
    void send();
    void sendMsg(uint8_t id,uint8_t* data,uint8_t len);
private:
    ip_addr_t dst_ip_addr;
    struct udp_pcb *upcb;
    struct pbuf *p;
    uint8_t send_buf[30];
    uint8_t receive_buf[30];
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void commanderTask(void* arg);



#endif  /* _COMMANDER_TASK_H__ */


