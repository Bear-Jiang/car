#ifndef _LED_TASK_H__
#define _LED_TASK_H__


/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern StackType_t ledTaskStackBuffer[50];
extern StaticTask_t ledTaskTCB;
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void ledTask(void* arg);

#endif  /* _LED_TASK_H__ */

