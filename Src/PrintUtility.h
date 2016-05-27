/**
  ******************************************************************************
  * File Name          : PrintUtility.h
  * Description        : Header File for the Print Utility Interface
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

#ifndef PRINT_UTILITY_H
#define PRINT_UTILITY_H

/* Public Includes -----------------------------------------------------------*/

#include "GeneralTypes.h"
#include "cmsis_os.h"

/* Private Includes ----------------------------------------------------------*/


/* Literal Constants ---------------------------------------------------------*/

/* Types ---------------------------------------------------------------------*/

/* Procedures ----------------------------------------------------------------*/

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
