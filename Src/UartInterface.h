/**
  ******************************************************************************
  * File Name          : Uart Interface.h
  * Description        : Header File for the Uart Interface
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

/* Public Includes -----------------------------------------------------------*/

#include "cmsis_os.h"
#include "GeneralTypes.h"

/* Private Includes ----------------------------------------------------------*/


/* Literal Constants ---------------------------------------------------------*/

/* Types ---------------------------------------------------------------------*/

/* Procedures ----------------------------------------------------------------*/

void UartPowerUp
    (
    void
    );

void UartPowerInit
    (
    void
    );

void UartWriteData
    (
    const uint8_t*  a_PtrData,
    uint32_t        a_DataSize,
    uint32_t        a_TimeOut_Ms
    );

#endif // UART_INTERFACE_H
