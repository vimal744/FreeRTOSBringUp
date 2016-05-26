#include "SensorFusionInterface.h"

#include "FreeRTOS.h"
#include "task.h"
#include "PrintUtility.h"
#include <queue.h>
#include <string.h>

#define SENSOR_FUSION_MAIN_STACK_SIZE      ( 256 )

static const char* c_ThreadName = "SensorFusion_Main";


typedef uint8_t SensorIdType; enum
{
    SNSR_ID_GYRO    = 0,
    SNSR_ID_ACCEL   = 1,
    SNSR_ID_CMPS    = 2,

    SNSR_ID_CNT
};

typedef struct
{
    SensorIdType  SensorId;

    union
    {
        GyroDataType    GyroData;
        AccelDataType   AccelData;
        CompassDataType CmpsData;
    } SensorData;

} QueueDataType;


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
    s_DataQueue = xQueueCreate( 32, sizeof( QueueDataType ) );
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
    const GyroDataType* const a_PtrGyroData
    )
{
    QueueDataType queueItem;

    queueItem.SensorId = SNSR_ID_GYRO;
    memcpy( &( queueItem.SensorData ), a_PtrGyroData, sizeof( GyroDataType ) );

    return ( ( xQueueSend( s_DataQueue, &queueItem, portMAX_DELAY ) != pdTRUE ) ? FALSE : TRUE );
}

boolean SensorFusionAddAccelData
    (
    const AccelDataType* const a_PtrAccelData
    )
{
    QueueDataType queueItem;

    queueItem.SensorId = SNSR_ID_ACCEL;
    memcpy( &( queueItem.SensorData ), a_PtrAccelData, sizeof( AccelDataType ) );

    return ( ( xQueueSend( s_DataQueue, &queueItem, portMAX_DELAY ) != pdTRUE ) ? FALSE : TRUE );
}


boolean SensorFusionAddCompassData
    (
    const CompassDataType* const a_PtrCmpsData
    )
{
    QueueDataType queueItem;

    queueItem.SensorId = SNSR_ID_CMPS;
    memcpy( &( queueItem.SensorData ), a_PtrCmpsData, sizeof( CompassDataType ) );

    return ( ( xQueueSend( s_DataQueue, &queueItem, portMAX_DELAY ) != pdTRUE ) ? FALSE : TRUE );
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
    QueueDataType   queueItem;
    boolean         success;

    if( pdTRUE == xQueueReceive( s_DataQueue, &queueItem, portMAX_DELAY ) )
    {
        if( SNSR_ID_GYRO == queueItem.SensorId )
            {
            Printf
                (
                "SF: Rx Gyro x=%f, y=%f, z=%f\r\n",
                queueItem.SensorData.GyroData.meas[0],
                queueItem.SensorData.GyroData.meas[1],
                queueItem.SensorData.GyroData.meas[2]
                );
            }
        else if( SNSR_ID_ACCEL == queueItem.SensorId )
            {
            Printf
                (
                "SF: Rx Accl x=%f, y=%f, z=%f\r\n",
                queueItem.SensorData.AccelData.meas[0],
                queueItem.SensorData.AccelData.meas[1],
                queueItem.SensorData.AccelData.meas[2]
                );
            }
        else if( SNSR_ID_CMPS == queueItem.SensorId )
            {
            Printf
                (
                "SF: Rx Cmps x=%f, y=%f, z=%f\r\n",
                queueItem.SensorData.CmpsData.meas[0],
                queueItem.SensorData.CmpsData.meas[1],
                queueItem.SensorData.CmpsData.meas[2]
                );
            }

        success = TRUE;
    }
    else
    {
        success = FALSE;
    }
}
