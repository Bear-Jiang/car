#ifndef _CONTROL_TASK_H__
#define _CONTROL_TASK_H__


/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "pwm.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void controlTask(void* arg);

#endif  /* _CONTROL_TASK_H__ */


