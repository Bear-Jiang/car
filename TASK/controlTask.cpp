#include "controlTask.h"

uint16_t value = 500;

void controlTask(void* arg)
{
    
    for(;;)
    {
        
        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,value);//R_PWM
        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,value);//L_PWM
        
        vTaskDelay(500);
        
    }
}




