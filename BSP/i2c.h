#ifndef _I2C_H__
#define _I2C_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c3;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void I2C3_Init(void);

#ifdef __cplusplus
 }
#endif

#endif  /* _I2C_H__ */

