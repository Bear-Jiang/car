#include "ethTask.h"
#include "lwip.h"
#include "lwip/api.h"
#include "lwip/sys.h"
#include "lwip/ip_addr.h"
#include "string.h"

void ethTask(void* arg)
{
    MX_LWIP_Init();
    
    vTaskDelete( NULL );
}



