#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"

void StartDefaultTask(void* arg);

StackType_t TaskStackBuffer1[50];
StaticTask_t TaskTCBBuffer1;

int main()
{
    HAL_Init();

    xTaskCreateStatic(StartDefaultTask,"led_task",50,(void *)NULL,1,TaskStackBuffer1,&TaskTCBBuffer1);

    vTaskStartScheduler();
    for(;;)
    {}
}


void StartDefaultTask(void* arg)
{
    for(;;)
    {
        vTaskDelay(500);
        LEN_BLUE_TOGGLE();
    }
}

#ifdef __cplusplus
extern "C" {
#endif
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );    
#ifdef __cplusplus
}
#endif

StackType_t IdleTaskStackBuffer[50];
StaticTask_t IdleTaskTCBBuffer;

StackType_t TimerTaskStackBuffer[50];
StaticTask_t TimerTaskTCBBuffer;

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
    *ppxTimerTaskTCBBuffer = &TimerTaskTCBBuffer;
    *ppxTimerTaskStackBuffer = TimerTaskStackBuffer;
    *pulTimerTaskStackSize = 50;
}


void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
    *ppxIdleTaskStackBuffer = IdleTaskStackBuffer;
    *ppxIdleTaskTCBBuffer = &IdleTaskTCBBuffer;
    *pulIdleTaskStackSize = 50;
}
