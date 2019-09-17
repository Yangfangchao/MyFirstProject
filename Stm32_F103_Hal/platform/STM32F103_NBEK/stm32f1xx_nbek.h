/**
  ******************************************************************************
  * @file    stm32l4xx_nucleo.h
  * @author  MCD Application Team
  * @brief   This file contains definitions for:
  *          - LEDs and push-button available on STM32L4XX-Nucleo Kit
  *            from STMicroelectronics
  *          - LCD, joystick and microSD available on Adafruit 1.8" TFT LCD
  *            shield (reference ID 802), external SMPS
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L4XX_NBEK_H
#define __STM32L4XX_NBEK_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32L4XX_NBEK
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

//*****************************************************************************
// 中断函数指针类型
typedef void (*IrqFuncPtr)(void);

typedef enum
{
  LED0,
  LED1
} Led_TypeDef;

#define LED_PIN                           GPIO_PIN_13
#define LED_GPIO_PORT                     GPIOC


/*##################### USART ##################################*/

/**
  * @brief  USART1 Interface pins
  *         used to print log infomation
  */

#define LOGx                          USART1
#define LOGx_CLK_ENABLE()             __HAL_RCC_USART1_CLK_ENABLE()
#define LOGx_CLK_DISABLE()            __HAL_RCC_USART1_CLK_DISABLE()

#define LOGx_TXRX_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()  // __HAL_RCC_GPIOA_CLK_ENABLE()


#define LOGx_FORCE_RESET()            __HAL_RCC_USART1_FORCE_RESET()
#define LOGx_RELEASE_RESET()          __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define LOGx_TX_PIN                   GPIO_PIN_9     // GPIO_PIN_9
#define LOGx_TX_GPIO_PORT             GPIOA          // GPIOA

#define LOGx_RX_PIN                   GPIO_PIN_10    // GPIO_PIN_10
#define LOGx_RX_GPIO_PORT             GPIOA          // GPIOA
#define LOGx_GPIO_PORT                GPIOA 


/**
  * @brief  LPUART1 Interface pins
  *         used to communicate with nb device
  */

#define NBUart                          LPUART1
#define NBUart_CLK_ENABLE()             __HAL_RCC_LPUART1_CLK_ENABLE()
#define NBUart_CLK_DISABLE()            __HAL_RCC_LPUART1_CLK_DISABLE()

#define NBUart_TXRX_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()  // __HAL_RCC_GPIOA_CLK_ENABLE()

#define NBUart_FORCE_RESET()            __HAL_RCC_LPUART1_FORCE_RESET()
#define NBUart_RELEASE_RESET()          __HAL_RCC_LPUART1_RELEASE_RESET()

/* Definition for LPUSARTx Pins */
#define NBUart_TX_PIN                   	GPIO_PIN_11     	// GPIO_PIN_11
#define NBUart_TX_GPIO_PORT   		GPIOB           		// GPIOB

#define NBUart_RX_PIN                   	GPIO_PIN_10     	// GPIO_PIN_10
#define NBUart_RX_GPIO_PORT      		GPIOB           		// GPIOB
#define NBUart_GPIO_PORT                	GPIOB 
#define NBUart_AF                       		GPIO_AF8_LPUART1

/* NB power enPin*/
#define NB_PWR_PIN                      		GPIO_PIN_0
#define NB_PWR_PORT                     	GPIOA


/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup STM32L4XX_NUCLEO_Exported_Functions
  * @{
  */
uint32_t         BSP_GetVersion(void);


/**
  * @}
  */



#ifdef __cplusplus
}
#endif

#endif /* __STM32L4XX_NBEK_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

