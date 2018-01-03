#include "ledTask.h"

TaskHandle_t ledTaskHandle;

int main()
{
    HAL_Init();

    ledTaskHandle = xTaskCreateStatic(ledTask,"ledTask",50,(void *)NULL,1,ledTaskStackBuffer,&ledTaskTCB);

    vTaskStartScheduler();
    for(;;)
    {}
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
