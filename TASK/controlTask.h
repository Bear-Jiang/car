#ifndef _CONTROL_TASK_H__
#define _CONTROL_TASK_H__

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "pwm.h"

/* Exported types ------------------------------------------------------------*/
class Motor_t
{
public:
    Motor_t();
    void init();
    void setSpeed(float left,float right);
    void getSpeedCount();
    friend void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
private:
    float r_speed, l_speed;
    volatile float r_count, l_count;
};

class Gimbal_t
{
public:
    Gimbal_t(uint16_t yaw, uint16_t pitch);
    void init();
    void setYaw(uint8_t v);
    void setPitch(uint8_t v);
private:
    const uint16_t yaw_mid;
    const uint16_t pitch_zero;
};

class Led_t
{
public:
    Led_t();
    void init();
    void setIntensity(uint8_t id, uint16_t value);
private:
    
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define CONSTRAIN(x,max,min) (x>max?max:(x<min?min:x))
#define MAX(a,b)             (a>b?a:b)
#define MIN(a,b)             (a<b?a:b)
/* Exported functions ------------------------------------------------------- */
void controlTask(void* arg);

#endif  /* _CONTROL_TASK_H__ */


