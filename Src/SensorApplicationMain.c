#include "SensorApplicationInterface.h"
#include "SensorFusionInterface.h"
        
#include "FreeRTOS.h"
#include "task.h"
#include "PrintUtility.h"
#include <queue.h>
#include <string.h>

#define SENSOR_APP_MAIN_STACK_SIZE      ( 256 )

static const char* c_ThreadName = "SensorApp_Main";

static TaskHandle_t     s_SensorApp_Main_Handle;

static void MainSensorApp
    (
    void* a_Ptr
    );


void SensorApplicationPowerUp
    ( void )
{
    xTaskCreate( MainSensorApp, c_ThreadName, SENSOR_APP_MAIN_STACK_SIZE, NULL, tskIDLE_PRIORITY, &s_SensorApp_Main_Handle );
}

void SensorApplicationInit
    ( void )
{

}

void SensorApplicationPowerDown
    ( void )
{
     if( s_SensorApp_Main_Handle != NULL )
     {
         vTaskDelete( s_SensorApp_Main_Handle );
     }
}


static void MainSensorApp
    (
    void*           a_Ptr
    )
{
    SensorQuaternionDataType quaternionSensorData;

    for(;;)
    {
        SensorFusionGetQuaternionData(&quaternionSensorData);

        Printf
            (
            "Sensor App: ts=%d, x=%.3f, y=%.3f, z=%.3f, w=%.3f\r\n",
            quaternionSensorData.TimeStamp,
            quaternionSensorData.MeasurementX,
            quaternionSensorData.MeasurementY,
            quaternionSensorData.MeasurementZ,
            quaternionSensorData.MeasurementW
            );

        osDelay(1000);
    }
}

