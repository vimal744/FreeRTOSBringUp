#include "GeneralTypes.h"
#include "PrintUtility.h"
#include "UartInterface.h"

#include "stm32f4xx_hal.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>


void PrintString
    (
    const char* const   a_PtrString
    )
{
    if( a_PtrString != NULL )
    {
        UartWriteData( (uint8_t*)a_PtrString, strlen( a_PtrString ), 1000 );
    }
}

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

    va_start( args, format );

    len = vsnprintf( buffer, BUFFER_SIZE, format, args );

    if( len != -1 )
    {
        UartWriteData( (uint8_t*)buffer, len, 1000 );
    }

    va_end(args);
}




