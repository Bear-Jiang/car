#ifndef _ADC_H__
#define _ADC_H__
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ADC1_Init(void);
void adcConvCpltCallback(void);
#ifdef __cplusplus
 }
#endif
#endif /* _ADC_H__ */


