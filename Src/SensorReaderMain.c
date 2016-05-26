#include "SensorReaderInterface.h"
#include "SensorFusionInterface.h"

#include "GyroTypes.h"
#include "AccelTypes.h"
#include "CompassTypes.h"


#include "PrintUtility.h"

#include "FreeRTOS.h"
#include "task.h"

#define SENSOR_MAIN_STACK_SIZE      ( 256 )
#define SensorReader_Debug_Printf( _args ) //Printf _args

static const char* c_ThreadName = "SensorReader_Main";

static TaskHandle_t s_SensorReader_Main_Handle;


static void MainSensorReader
    (
    void* a_Ptr
    );

void SensorReaderPowerUp
    ( void )
{
    xTaskCreate( MainSensorReader, c_ThreadName, SENSOR_MAIN_STACK_SIZE, NULL, tskIDLE_PRIORITY, &s_SensorReader_Main_Handle );
}

void SensorReaderInit
    ( void )
{

}

void SensorReaderPowerDown
    ( void )
{
     if( s_SensorReader_Main_Handle != NULL )
     {
         vTaskDelete( s_SensorReader_Main_Handle );
     }
}


static void MainSensorReader
    (
    void* a_Ptr
    )
{
    GyroDataType    gyroData;
    AccelDataType   accelData;
    CompassDataType cmpsData;


    gyroData.meas[0] = 0.0f;
    gyroData.meas[1] = 0.0f;
    gyroData.meas[2] = 0.0f;

    accelData.meas[0] = 0.0f;
    accelData.meas[1] = 0.0f;
    accelData.meas[2] = 0.0f;

    cmpsData.meas[0] = 0.0f;
    cmpsData.meas[1] = 0.0f;
    cmpsData.meas[2] = 0.0f;

    for(;;)
    {
        gyroData.meas[0] += 1.0f;
        gyroData.meas[1] += 10.0f;
        gyroData.meas[2] += -10.0f;
        SensorReader_Debug_Printf(("SR: Tx Gyro x=%f, y=%f, z=%f\r\n", gyroData.meas[0], gyroData.meas[1], gyroData.meas[2] ));
        SensorFusionAddGyroData( &gyroData );
        osDelay(10);

        accelData.meas[0] += 2.0f;
        accelData.meas[1] += 20.0f;
        accelData.meas[2] += -20.0f;
        SensorReader_Debug_Printf(("SR: Tx Accl x=%f, y=%f, z=%f\r\n", accelData.meas[0], accelData.meas[1], accelData.meas[2] ));
        SensorFusionAddAccelData( &accelData );
        osDelay(10);

        cmpsData.meas[0] += 3.0f;
        cmpsData.meas[1] += 30.0f;
        cmpsData.meas[2] += -30.0f;
        SensorReader_Debug_Printf(("SR: Tx Cmps x=%f, y=%f, z=%f\r\n", cmpsData.meas[0], cmpsData.meas[1], cmpsData.meas[2] ));
        SensorFusionAddCompassData( &cmpsData );

        osDelay(1000);
    }
}
