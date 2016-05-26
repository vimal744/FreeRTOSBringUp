#ifndef SENSOR_FUSION_PUBLIC_INTERFACE_H
#define SENSOR_FUSION_PUBLIC_INTERFACE_H

#include "GeneralTypes.h"

#include "GyroTypes.h"
#include "AccelTypes.h"
#include "CompassTypes.h"

void SensorFusionPowerUp
    ( void );

void SensorFusionInit
    ( void );

void SensorFusionPowerDown
    ( void );

boolean SensorFusionAddGyroData
    (
    const GyroDataType* const a_PtrGyroData
    );

boolean SensorFusionAddAccelData
    (
    const AccelDataType* const a_PtrAccelData
    );

boolean SensorFusionAddCompassData
    (
    const CompassDataType* const a_PtrCmpsData
    );

#endif // SENSOR_FUSION_PUBLIC_INTERFACE_H
