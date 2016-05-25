#ifndef SENSOR_READER_PUBLIC_INTERFACE_H
#define SENSOR_READER_PUBLIC_INTERFACE_H

#include "cmsis_os.h"

void SensorReaderPowerUp
    ( void );

void SensorReaderInit
    ( void );

void SensorReaderPowerDown
    ( void );

#endif // SENSOR_READER_PUBLIC_INTERFACE_H
