#ifndef _ETH_H__
#define _ETH_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern ETH_HandleTypeDef heth;
/* Exported macro ------------------------------------------------------------*/
     
/* Exported functions ------------------------------------------------------- */
void ETH_Init(void);     

#ifdef __cplusplus
}
#endif


#endif


