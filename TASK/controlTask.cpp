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




#ifdef __cplusplus
extern "C" {
#endif
void EXTI15_10_IRQHandler(void);
#ifdef __cplusplus
}
#endif
uint32_t aaaaaaaaaa=0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_10)
    {
        
    }
    else if(GPIO_Pin == GPIO_PIN_11)
    {
        
    }
}

/**
* @brief This function handles EXTI line[15:10] interrupts.
*/
void EXTI15_10_IRQHandler(void)
{
    /* USER CODE BEGIN EXTI15_10_IRQn 0 */

    /* USER CODE END EXTI15_10_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
    aaaaaaaaaa++;
    /* USER CODE BEGIN EXTI15_10_IRQn 1 */

    /* USER CODE END EXTI15_10_IRQn 1 */
}



