#ifndef _GPIO_H__
#define _GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define LEN_BLUE_OFF() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET)
#define LEN_BLUE_ON() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET)
#define LEN_BLUE_TOGGLE() HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2)
     
/* Exported functions ------------------------------------------------------- */
void GPIO_Init(void);
     

#ifdef __cplusplus
}
#endif

#endif  /* _GPIO_H__ */

