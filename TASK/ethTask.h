#ifndef _ETH_TASK_H__
#define _ETH_TASK_H__
/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern StackType_t ethTaskStackBuffer[200];
extern StaticTask_t ethTaskTCB;
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void ethTask(void* arg);



#endif



