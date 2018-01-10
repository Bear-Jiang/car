#include "ledTask.h"
#include "ethTask.h"


TaskHandle_t ledTaskHandle;
TaskHandle_t ethTaskHandle;

int main()
{ 
    HAL_Init();

//    ledTaskHandle = xTaskCreateStatic(ledTask,"ledTask",50,(void *)NULL,5,ledTaskStackBuffer,&ledTaskTCB);
//    ethTaskHandle = xTaskCreateStatic(ethTask,"ethTask",50,(void *)NULL,6,ethTaskStackBuffer,&ethTaskTCB);
    
    xTaskCreate(ledTask,"ledTask",100,NULL,6,NULL);
    xTaskCreate(ethTask,"ethTask",200,NULL,4,NULL);
    
    vTaskStartScheduler();
    for(;;)
    {}
}
#ifdef __cplusplus
extern "C" {
#endif
void xPortSysTickHandler( void );
void SysTick_Handler(void);
void ETH_IRQHandler(void);
#ifdef __cplusplus
}
#endif
    
void SysTick_Handler(void)
{
    HAL_IncTick();
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        xPortSysTickHandler();
    }
}
extern ETH_HandleTypeDef heth;
void ETH_IRQHandler(void)
{
  HAL_ETH_IRQHandler(&heth);
}

/******************以下屏蔽部分在使能动态分配任务时需要取消注释****************/

//#ifdef __cplusplus
//extern "C" {
//#endif
//void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );
//void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );    
//#ifdef __cplusplus
//}
//#endif

//StackType_t IdleTaskStackBuffer[50];
//StaticTask_t IdleTaskTCBBuffer;

//StackType_t TimerTaskStackBuffer[50];
//StaticTask_t TimerTaskTCBBuffer;

//void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
//{
//    *ppxTimerTaskTCBBuffer = &TimerTaskTCBBuffer;
//    *ppxTimerTaskStackBuffer = TimerTaskStackBuffer;
//    *pulTimerTaskStackSize = 50;
//}


//void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
//{
//    *ppxIdleTaskStackBuffer = IdleTaskStackBuffer;
//    *ppxIdleTaskTCBBuffer = &IdleTaskTCBBuffer;
//    *pulIdleTaskStackSize = 50;
//}
