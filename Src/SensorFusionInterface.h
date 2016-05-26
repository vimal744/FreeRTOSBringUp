#ifndef SENSOR_FUSION_PUBLIC_INTERFACE_H
#define SENSOR_FUSION_PUBLIC_INTERFACE_H

#include "GeneralTypes.h"

#include "GyroTypes.h"
#include "AccelTypes.h"
#include "CompassTypes.h"

typedef struct
    {
    uint32_t TimeStamp;
    float    MeasurementX;
    float    MeasurementY;
    float    MeasurementZ;
    float    MeasurementW;
    } SensorQuaternionDataType;

void SensorFusionPowerUp
    ( void );

void SensorFusionInit
    ( void );

void SensorFusionPowerDown
    ( void );

void SensorFusionGetQuaternionData
    (
    const SensorQuaternionDataType* a_PtrData
    );

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
