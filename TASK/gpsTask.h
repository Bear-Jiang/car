#ifndef _GPS_TASK_H__
#define _GPS_TASK_H__


/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern StackType_t gpsTaskStackBuffer[50];
extern StaticTask_t gpsTaskTCB;
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void gpsTask(void* arg);

#endif  /* _GPS_TASK_H__ */

