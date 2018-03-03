#ifndef _USART_H__
#define _USART_H__

#ifdef __cplusplus
 extern "C" {
#endif
     
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern UART_HandleTypeDef huart5;//For compass
extern UART_HandleTypeDef huart6;     
     
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void unpackUART5_Data(uint8_t* p);
void unpackUART6_Data(uint8_t* p);
void UART_Init(void);     
#ifdef __cplusplus
 }
#endif
#endif /* _USART_H__ */

