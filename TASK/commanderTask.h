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
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/****************remote message id*****************/
#define MSG_TEMP_HUMI_ID    0x00
#define MSG_PRESSURE_ID     0x01
#define MSG_COMPASS_ID      0x02
#define MSG_POWER_ID        0x03
#define MSG_CMD_ID          0x04
#define MSG_GIMBAL_ID       0x05
#define MSG_LIGHT_ID        0x06
#define MSG_PID_ID          0x07
#define MSG_STATE_ID        0x08

/* Exported functions ------------------------------------------------------- */
void commanderTask(void* arg);



#endif  /* _COMMANDER_TASK_H__ */


