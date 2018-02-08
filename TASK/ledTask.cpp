#include "ledTask.h"

void ledTask(void* arg)
{
    for(;;)
    {
        vTaskDelay(500);
        LEN_BLUE_TOGGLE();
    }
}


