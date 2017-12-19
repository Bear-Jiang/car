#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"

void StartDefaultTask(void* arg);

int main()
{
    HAL_Init();

    xTaskCreate(StartDefaultTask,"led_task",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY | portPRIVILEGE_BIT,NULL);
    vTaskStartScheduler();
    for(;;)
    {}
}


void StartDefaultTask(void* arg)
{
    for(;;)
    {
        vTaskDelay(100);
        LEN_BLUE_TOGGLE();
    }
}

