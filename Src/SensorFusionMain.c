#include "SensorFusionInterface.h"
#include "FreeRTOS.h"
#include "task.h"

#define SENSOR_FUSION_MAIN_STACK_SIZE      ( 128 )

static const char* c_ThreadName = "SensorFusion_Main";

static TaskHandle_t s_SensorFusion_Main_Handle;


static void MainSensorFusion
    (
    void* a_Ptr
    );

void SensorFusionPowerUp
    ( void )
{

}

void SensorFusionInit
    ( void )
{
    xTaskCreate( MainSensorFusion, c_ThreadName, SENSOR_FUSION_MAIN_STACK_SIZE, NULL, tskIDLE_PRIORITY, &s_SensorFusion_Main_Handle );
}

void SensorFusionPowerDown
    ( void )
{
     if( s_SensorFusion_Main_Handle != NULL )
     {
         vTaskDelete( s_SensorFusion_Main_Handle );
     }
}

static void MainSensorFusion
    (
    void* a_Ptr
    )
{
    for(;;)
    {
        osDelay(1000);
    }
}
