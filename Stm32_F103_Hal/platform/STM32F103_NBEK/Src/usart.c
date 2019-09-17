//******************************************************************************
//                                www.ghostyu.com
//
//                 Copyright (c) 2017-2018, WUXI Ghostyu Co.,Ltd.
//                                All rights reserved.
//
//  FileName : usart.c
//  Date     : 2018-11-02 14:04
//  Version  : V0001
// 历史记录  : 第一次创建
//******************************************************************************

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
//#include "los_bsp_uart.h"
#include "los_hwi.h"

#ifdef LOS_STM32F103
#include "stm32f1xx_hal.h"
#include "stm32f1xx_nbek.h"
#include "stm32f1xx_it.h"
#endif

extern const UART_Config logUartCfg;
extern const UART_Config nbUartCfg;
extern const UART_Config gpsUartCfg;
//*****************************************************************************
// fn : Board_UART_Init
//
// brief : Init the uart
//
// param : none
//
// return : none
void Board_UART_Init(const UART_Config *uartCfg )
{
  if (HAL_UART_Init(uartCfg->pUart) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
//*****************************************************************************
// fn : Board_UART_DeInit
//
// brief : Deinit the uart
//
// param : uartCfg -> pointer of UART_Config
//
// return : none
extern void Board_UART_DeInit(const UART_Config *uartCfg)
{
  if (uartCfg->pUart == NULL )
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  HAL_UART_DeInit(uartCfg->pUart);
}

//*****************************************************************************
// fn : Board_UART_Send
//
// brief : Send the data by uart
//
// param : uartCfg -> pointer of UART_Config
//
// return : none
extern void Board_UART_Send(const UART_Config *uartCfg,uint8_t *buf, uint16_t len)
{
  if (uartCfg->pUart == NULL )
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  
}
//*****************************************************************************
// fn : Board_UART_Rece
//
// brief : Rece the data by uart
//
// param : uartCfg -> pointer of UART_Config
//
// return : none
extern void Board_UART_Rece(const UART_Config *uartCfg,uint8_t *buf, uint16_t len)
{
  if (uartCfg->pUart == NULL )
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  
 
}
//*****************************************************************************
// fn : HAL_UART_MspInit
//
// brief : cfg the gpio in uart
//
// param : uartHandle -> the handle of uart module
//
// return : none
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
  if(uartHandle->Instance == LOGx)
  {
    /* USART1 clock enable */
    LOGx_CLK_ENABLE();
    //LOGx_TXRX_GPIO_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10    ------> USART1_RX 
    */
	
    Board_GPIO_OneInit(logUartCfg.hwAttrs->txPin);
    Board_GPIO_OneInit(logUartCfg.hwAttrs->rxPin);
  }

}
//*****************************************************************************
// fn : HAL_UART_MspDeInit
//
// brief : DeInit the uart
//
// param : uartHandle -> the handle of uart module
//
// return : none
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  if(uartHandle->Instance == LOGx)
  {

    /* Peripheral clock disable */
    LOGx_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    Board_GPIO_DeInit(logUartCfg.hwAttrs->rxPin->Port, logUartCfg.hwAttrs->rxPin->pin);
    Board_GPIO_DeInit(logUartCfg.hwAttrs->txPin->Port, logUartCfg.hwAttrs->txPin->pin);
  }

}

//***********************************************************************
// fn : HAL_UART_ErrorCallback
//
// brief : 串口接收回调函数，由系统自行调用
//
// param : huart -> 串口实例引用
//
// return : none
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

  
}
//**************************************************************************************
// fn : HAL_UART_TxCpltCallback
//
// brief : 串口中断回调函数
//
// param : huart -> the reference of uart 
//
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

    
}
//**************************************************************************************
// fn : HAL_UART_RxCpltCallback
//
// brief : 串口中断回调函数
//
// param : huart -> the reference of uart 
//
// return : none
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}
