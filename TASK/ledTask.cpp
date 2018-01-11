#include "ledTask.h"

//StackType_t ledTaskStackBuffer[50];
//StaticTask_t ledTaskTCB;

void ledTask(void* arg)
{
    for(;;)
    {
        vTaskDelay(500);
        LEN_BLUE_TOGGLE();
    }
}


