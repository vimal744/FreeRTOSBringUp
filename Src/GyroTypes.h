#ifndef GYRO_TYPES_H
#define GYRO_TYPES_H

#include "cmsis_os.h"
#include "GeneralTypes.h"

#define GYRO_AXIS_CNT ( 3 )

typedef struct
    {
    float       meas[ GYRO_AXIS_CNT ];
    } GyroDataType;

#endif // GYRO_TYPES_H
