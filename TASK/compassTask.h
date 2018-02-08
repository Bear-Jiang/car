#ifndef _COMPASS_TASK_H__
#define _COMPASS_TASK_H__


/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "gpio.h"
#include "usart.h"
/* Exported types ------------------------------------------------------------*/
struct CompassMsg_t
{
    float heading;
    float roll;
    float pitch;
};

class Compass_t
{
public:
    Compass_t();
    void readAngle();
    void startCali();
    bool isCali(){return caliFlag;};
    bool isCaliStart(){return caliStart;};
    void sendToCommander(void);
    friend void unpackUART5_Data(uint8_t* p);
private:
    uint8_t send_buf[20]; 
    bool caliFlag;
    bool caliStart;
    CompassMsg_t angle;
};

/* Exported constants --------------------------------------------------------*/
extern QueueHandle_t compass_queue_handle;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void compassTask(void* arg);

#endif  /* _COMPASS_TASK_H__ */

