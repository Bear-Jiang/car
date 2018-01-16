#ifndef _ADC_TASK_H__
#define _ADC_TASK_H__


/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "adc.h"
/* Exported types ------------------------------------------------------------*/

class power_t
{
public:
    power_t();
//    float getCurrent(){return msg.current;}
//    float getVoltage(){return msg.voltage;}
    void startCov(void);
    void sendToCommander(void);
    void sendToRemote(void);
    friend void adcConvCpltCallback(void);
private:
//    power_msg msg;
    uint16_t buf[2];
    uint8_t sendBuf[15];
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void adcTask(void* argument);




#endif  /* _ADC_TASK_H__ */

