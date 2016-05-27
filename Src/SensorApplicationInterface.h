/**
  ******************************************************************************
  * File Name          : SensorApplicationInterface.h
  * Description        : Header File for the Sensor Application Interface
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

#ifndef SENSOR_APPLICATION_PUBLIC_INTERFACE_H
#define SENSOR_APPLICATION_PUBLIC_INTERFACE_H

/* Public Includes -----------------------------------------------------------*/

#include "GeneralTypes.h"

/* Private Includes ----------------------------------------------------------*/


/* Literal Constants ---------------------------------------------------------*/

/* Types ---------------------------------------------------------------------*/

/* Procedures ----------------------------------------------------------------*/

void SensorApplicationPowerUp
    ( void );

void SensorApplicationInit
    ( void );

void SensorApplicationPowerDown
    ( void );

#endif // SENSOR_APPLICATION_PUBLIC_INTERFACE_H
