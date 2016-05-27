/**
  ******************************************************************************
  * File Name          : CompassTypes.h
  * Description        : Header File for the compass types
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

#ifndef COMPASS_TYPES_H
#define COMPASS_TYPES_H

/* Public Includes -----------------------------------------------------------*/

#include "cmsis_os.h"
#include "GeneralTypes.h"

/* Private Includes ----------------------------------------------------------*/


/* Literal Constants ---------------------------------------------------------*/

/* Compass Axis count */
#define COMPASS_AXIS_CNT ( 3 )

/* Types ---------------------------------------------------------------------*/

/* Compass Data Type */
typedef struct
    {
    float       meas[ COMPASS_AXIS_CNT ];
    } CompassDataType;

#endif // COMPASS_TYPES_H
