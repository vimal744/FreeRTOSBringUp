/**
  ******************************************************************************
  * File Name          : PrintUtility.h
  * Description        : Implementation for the print utility interface
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

/* Public Includes -----------------------------------------------------------*/

#include "GeneralTypes.h"
#include "PrintUtility.h"
#include "UartInterface.h"
#include "stm32f4xx_hal.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/* Private Includes ----------------------------------------------------------*/


/* Literal Constants ---------------------------------------------------------*/

/* Types ---------------------------------------------------------------------*/

/* Procedures ----------------------------------------------------------------*/

/**
* @brief This function prints a string to the UART
*/
void PrintString
    (
    const char* const   a_PtrString
    )
{
    // If the string is valid
    if( a_PtrString != NULL )
    {
        // Write the string data to UART
        UartWriteData( (uint8_t*)a_PtrString, strlen( a_PtrString ), 1000 );
    }
}

/**
* @brief This function is to format and print a string
*/

void Printf
    (
    char *format,
    ...
    )

{
    #define BUFFER_SIZE (128)

    char buffer[BUFFER_SIZE];
    va_list args;
    int     len;

    // Format the input argments and generate a string
    va_start( args, format );

    len = vsnprintf( buffer, BUFFER_SIZE, format, args );

    if( len != -1 )
    {
        // Write the string to UART
        UartWriteData( (uint8_t*)buffer, len, 1000 );
    }

    va_end(args);
}




