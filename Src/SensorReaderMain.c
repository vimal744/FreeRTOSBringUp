#include "SensorReaderInterface.h"
#include "SensorFusionInterface.h"
#include "GyroTypes.h"
#include "PrintUtility.h"

#include "FreeRTOS.h"
#include "task.h"

#define SENSOR_MAIN_STACK_SIZE      ( 256 )

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
    GyroRawDataType rawData =0;

    for(;;)
    {
        rawData += 1;
        Printf("Sensor Reader: Send Gyro Data %d\r\n", rawData );
        SensorFusionAddGyroData( &rawData );
        osDelay(1000);
    }
}
