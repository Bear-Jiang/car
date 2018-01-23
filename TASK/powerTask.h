#ifndef _ADC_TASK_H__
#define _ADC_TASK_H__

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "adc.h"
/* Exported types ------------------------------------------------------------*/

struct PowerMsg_t
{
    float current;
    float voltage;
};

class Power_t
{
public:
    Power_t();
    float getCurrent(){return message_data.current;}
    float getVoltage(){return message_data.voltage;}
    void startCov(void);
    void sendToCommander(void);
    friend void adcConvCpltCallback(void);
private:
    PowerMsg_t message_data;
    uint16_t adc_buf[2];
};

/* Exported constants --------------------------------------------------------*/
extern QueueHandle_t power_queue_handle;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void powerTask(void* argument);

#endif  /* _ADC_TASK_H__ */

