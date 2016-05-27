/**
  ******************************************************************************
  * File Name          : SensorReaderInterface.h
  * Description        : Header File for the Sensor Reader Interface
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

#ifndef SENSOR_READER_PUBLIC_INTERFACE_H
#define SENSOR_READER_PUBLIC_INTERFACE_H

/* Public Includes -----------------------------------------------------------*/

#include "GeneralTypes.h"

/* Private Includes ----------------------------------------------------------*/


/* Literal Constants ---------------------------------------------------------*/

/* Types ---------------------------------------------------------------------*/

/* Procedures ----------------------------------------------------------------*/

void SensorReaderPowerUp
    ( void );

void SensorReaderInit
    ( void );

void SensorReaderPowerDown
    ( void );

#endif // SENSOR_READER_PUBLIC_INTERFACE_H
