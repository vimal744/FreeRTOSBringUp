/**
  ******************************************************************************
  * File Name          : GyroTypes.h
  * Description        : Header File for the gyroscope types
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

#ifndef GYRO_TYPES_H
#define GYRO_TYPES_H

/* Public Includes -----------------------------------------------------------*/

#include "cmsis_os.h"
#include "GeneralTypes.h"

/* Private Includes ----------------------------------------------------------*/


/* Literal Constants ---------------------------------------------------------*/

/* Gyro Axis count */
#define GYRO_AXIS_CNT ( 3 )

/* Types ---------------------------------------------------------------------*/

/* Gyro Data Type */
typedef struct
    {
    float       meas[ GYRO_AXIS_CNT ];
    } GyroDataType;

#endif // GYRO_TYPES_H
