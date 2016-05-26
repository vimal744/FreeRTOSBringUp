#ifndef ACCELEROMETER_TYPES_H
#define ACCELEROMETER_TYPES_H

#include "cmsis_os.h"
#include "GeneralTypes.h"

#define ACCEL_AXIS_CNT ( 3 )

typedef struct
    {
    float       meas[ ACCEL_AXIS_CNT ];
    } AccelDataType;

#endif // ACCELEROMETER_TYPES_H
