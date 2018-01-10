#include "ethTask.h"
#include "lwip.h"
StackType_t ethTaskStackBuffer[200];
StaticTask_t ethTaskTCB;

void ethTask(void* arg)
{
    MX_LWIP_Init();
    for(;;)
    {
        int a = 0;
        a++;
        vTaskDelay(500);
    }
}

