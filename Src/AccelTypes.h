/**
  ******************************************************************************
  * File Name          : AccelTypes.h
  * Description        : Header File for the accelerometer types
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

#ifndef ACCELEROMETER_TYPES_H
#define ACCELEROMETER_TYPES_H

/* Public Includes -----------------------------------------------------------*/

#include "cmsis_os.h"
#include "GeneralTypes.h"

/* Private Includes ----------------------------------------------------------*/


/* Literal Constants ---------------------------------------------------------*/

/* Accel Axis count */
#define ACCEL_AXIS_CNT ( 3 )

/* Types ---------------------------------------------------------------------*/

/* Accel Data Type */
typedef struct
    {
    float       meas[ ACCEL_AXIS_CNT ];
    } AccelDataType;

#endif // ACCELEROMETER_TYPES_H
