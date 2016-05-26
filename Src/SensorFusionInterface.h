#ifndef SENSOR_FUSION_PUBLIC_INTERFACE_H
#define SENSOR_FUSION_PUBLIC_INTERFACE_H

#include "GeneralTypes.h"
#include "GyroTypes.h"
#include "cmsis_os.h"

void SensorFusionPowerUp
    ( void );

void SensorFusionInit
    ( void );

void SensorFusionPowerDown
    ( void );

boolean SensorFusionAddGyroData
    (
    const GyroRawDataType* const a_PtrGyroData
    );

#endif // SENSOR_FUSION_PUBLIC_INTERFACE_H
