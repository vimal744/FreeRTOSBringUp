#include "SensorFusionInterface.h"
#include "GyroTypes.h"
#include "FreeRTOS.h"
#include "task.h"
#include "PrintUtility.h"
#include <queue.h>

#define SENSOR_FUSION_MAIN_STACK_SIZE      ( 256 )

static const char* c_ThreadName = "SensorFusion_Main";

static TaskHandle_t     s_SensorFusion_Main_Handle;
static QueueHandle_t    s_DataQueue;

static void MainSensorFusion
    (
    void* a_Ptr
    );

static void ProcessDataQueue
    (
    void
    );

void SensorFusionPowerUp
    ( void )
{
    s_DataQueue = xQueueCreate( 32, sizeof( GyroRawDataType ) );
    xTaskCreate( MainSensorFusion, c_ThreadName, SENSOR_FUSION_MAIN_STACK_SIZE, NULL, tskIDLE_PRIORITY, &s_SensorFusion_Main_Handle );
}

void SensorFusionInit
    ( void )
{

}

void SensorFusionPowerDown
    ( void )
{
     if( s_SensorFusion_Main_Handle != NULL )
     {
         vTaskDelete( s_SensorFusion_Main_Handle );
     }
}

boolean SensorFusionAddGyroData
    (
    const GyroRawDataType* const a_PtrGyroData
    )
{

    boolean success;

    if( xQueueSend( s_DataQueue, a_PtrGyroData, portMAX_DELAY ) != pdTRUE )
    {
        success = FALSE;
    }
    else
    {
        success = TRUE;
    }

    return success;
}


static void MainSensorFusion
    (
    void* a_Ptr
    )
{
    for(;;)
    {
        ProcessDataQueue();
    }
}

static void ProcessDataQueue
    (
    void
    )
{
    GyroRawDataType rcvdGyroData;
    boolean         success;

    if( pdTRUE == xQueueReceive( s_DataQueue, &rcvdGyroData, portMAX_DELAY ) )
    {
        Printf("Sensor Fusion: Received Gyro Data %d\r\n", rcvdGyroData);
        success = TRUE;
    }
    else
    {
        success = FALSE;
    }
}
