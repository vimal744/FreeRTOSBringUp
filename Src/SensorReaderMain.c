#include "SensorReaderInterface.h"
#include "FreeRTOS.h"
#include "task.h"

#define SENSOR_MAIN_STACK_SIZE      ( 128 )

static const char* c_ThreadName = "SensorReader_Main";


static TaskHandle_t s_SensorReader_Main_Handle;


static void MainSensorReader
    (
    void* a_Ptr
    );

void SensorReaderPowerUp
    ( void )
{

}

void SensorReaderInit
    ( void )
{
    xTaskCreate( MainSensorReader, c_ThreadName, SENSOR_MAIN_STACK_SIZE, NULL, tskIDLE_PRIORITY, &s_SensorReader_Main_Handle );
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
    for(;;)
    {
        osDelay(1000);
    }
}
