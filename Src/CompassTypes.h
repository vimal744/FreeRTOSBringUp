#ifndef COMPASS_TYPES_H
#define COMPASS_TYPES_H

#include "cmsis_os.h"
#include "GeneralTypes.h"

#define COMPASS_AXIS_CNT ( 3 )

typedef struct
    {
    float       meas[ COMPASS_AXIS_CNT ];
    } CompassDataType;

#endif // COMPASS_TYPES_H
