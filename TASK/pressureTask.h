#ifndef _PRESSURE_TASK_H__
#define _PRESSURE_TASK_H__

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "i2c.h"
/* Exported types ------------------------------------------------------------*/

class pressure_t
{
public:
    pressure_t(void);
    void reset(void);
    void readProm(void);
    void calcP();
    int32_t getP();
    void sendToCommander(void);
    void sendToRemote(void);
    friend void unpackPressureData(uint8_t* buf);
private:
    static const uint16_t w_addr = 0xec;
    static const uint16_t r_addr = 0xed;

    float depth;    
    uint16_t prom[7];//存放出厂校准参数
    uint32_t pressureRaw;
    uint32_t tempratureRaw;
    int32_t dT;
    int32_t TEMP;
    int64_t OFF;
    int64_t SENS;
    int32_t P;

    uint8_t sendBuf[11];

};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void pressureTask(void* argument);


#endif  /* _PRESSURE_TASK_H__ */


