#ifndef _COMPASS_TASK_H__
#define _COMPASS_TASK_H__


/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern StackType_t compassTaskStackBuffer[50];
extern StaticTask_t compassTaskTCB;
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void compassTask(void* arg);

#endif  /* _COMPASS_TASK_H__ */

