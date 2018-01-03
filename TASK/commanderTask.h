#ifndef _COMMANDER_TASK_H__
#define _COMMANDER_TASK_H__

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern StackType_t commanderTaskStackBuffer[50];
extern StaticTask_t commanderTaskTCB;
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void commanderTask(void* arg);



#endif  /* _COMMANDER_TASK_H__ */


