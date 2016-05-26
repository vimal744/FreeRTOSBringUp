#ifndef PRINT_UTILITY_H
#define PRINT_UTILITY_H

#include "cmsis_os.h"
#include "GeneralTypes.h"

void PrintString
    (
    const char* const   a_PtrString
    );

void Printf
    (
    char *format,
    ...
    );


#endif // PRINT_UTILITY_H
