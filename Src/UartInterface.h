#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "cmsis_os.h"
#include "GeneralTypes.h"

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
