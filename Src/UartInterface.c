/**
  ******************************************************************************
  * File Name          : UartInterface.c
  * Description        : Implementation for the Uart Interface
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

/* Public Includes -----------------------------------------------------------*/

#include "UartInterface.h"
#include "GeneralTypes.h"
#include "stm32f4xx_hal.h"

/* Private Includes ----------------------------------------------------------*/

/* Literal Constants ---------------------------------------------------------*/

/* Memory Constants ----------------------------------------------------------*/

/* Types ---------------------------------------------------------------------*/

/* Global Variables ----------------------------------------------------------*/

static USART_HandleTypeDef husart2;

/* Procedures ----------------------------------------------------------------*/

/**
* @brief Power up the uart interface
*/

void UartPowerUp
    (
    void
    )
{

}

/**
* @brief Init the UART
*/

void UartPowerInit
    (
    void
    )
{
    husart2.Instance            = USART2;
    husart2.Init.BaudRate       = 9600;
    husart2.Init.WordLength     = USART_WORDLENGTH_8B;
    husart2.Init.StopBits       = USART_STOPBITS_1;
    husart2.Init.Parity         = USART_PARITY_NONE;
    husart2.Init.Mode           = USART_MODE_TX_RX;
    husart2.Init.CLKPolarity    = USART_POLARITY_LOW;
    husart2.Init.CLKPhase       = USART_PHASE_1EDGE;
    husart2.Init.CLKLastBit     = USART_LASTBIT_DISABLE;
    HAL_USART_Init(&husart2);
}

/**
* @brief Write data to the UART
*/

void UartWriteData
    (
    const uint8_t*  a_PtrData,
    uint32_t        a_DataSize,
    uint32_t        a_TimeOut_Ms
    )
{
    if( ( a_PtrData != NULL ) &&
        ( a_DataSize > 0    )
      )
    {
        HAL_USART_Transmit( &husart2, (uint8_t*)a_PtrData, a_DataSize, a_TimeOut_Ms );
    }
}
