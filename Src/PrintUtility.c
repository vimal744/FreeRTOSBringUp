#include "GeneralTypes.h"
#include "PrintUtility.h"
#include "UartInterface.h"

#include "stm32f4xx_hal.h"
#include <string.h>

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


