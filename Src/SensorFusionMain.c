#include "SensorFusionInterface.h"

#include "FreeRTOS.h"
#include "task.h"
#include "PrintUtility.h"
#include <queue.h>
#include <string.h>
#include <semphr.h>

#define SENSOR_FUSION_MAIN_STACK_SIZE      ( 256 )

#define SensorFusion_Debug_Printf( _args ) //Printf _args

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
    SensorIdType    SensorId;
    uint32_t        TimeStamp;
    union
    {
        GyroDataType    GyroData;
        AccelDataType   AccelData;
        CompassDataType CmpsData;

    } SensorData;

} QueueDataType;


static TaskHandle_t                 s_SensorFusion_Main_Handle;
static QueueHandle_t                s_DataQueue;
static SensorQuaternionDataType     s_QuaternionData;
static SemaphoreHandle_t            s_QuaternionData_Mutex;

static void MainSensorFusion
    (
    void* a_Ptr
    );

static boolean AddData
    (
    SensorIdType            a_SensorId,
    const uint8_t* const    a_PtrData,
    uint32_t                a_DataSize
    );

static boolean ProcessDataQueue
    (
    void
    );

static void UpdateQuaternionData
    (
    void
    );

void SensorFusionPowerUp
    ( void )
{
    s_QuaternionData_Mutex = xSemaphoreCreateRecursiveMutex();    
    s_DataQueue            = xQueueCreate( 32, sizeof( QueueDataType ) );
    xTaskCreate( MainSensorFusion, c_ThreadName, SENSOR_FUSION_MAIN_STACK_SIZE, NULL, tskIDLE_PRIORITY, &s_SensorFusion_Main_Handle );
    memset( &s_QuaternionData, 0, sizeof( SensorQuaternionDataType ) );
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

void SensorFusionGetQuaternionData
    (
    const SensorQuaternionDataType* a_PtrData
    )
{
    xSemaphoreTake( s_QuaternionData_Mutex, portMAX_DELAY );
    memcpy( (void*)a_PtrData, &s_QuaternionData, sizeof( SensorQuaternionDataType ) );
    xSemaphoreGive( s_QuaternionData_Mutex );
}

boolean SensorFusionAddGyroData
    (
    const GyroDataType* const a_PtrGyroData
    )
{
    return AddData( SNSR_ID_GYRO, (uint8_t*)a_PtrGyroData, sizeof( GyroDataType ) );
}

boolean SensorFusionAddAccelData
    (
    const AccelDataType* const a_PtrAccelData
    )
{
    return AddData( SNSR_ID_ACCEL, (uint8_t*)a_PtrAccelData, sizeof( AccelDataType ) );
}


boolean SensorFusionAddCompassData
    (
    const CompassDataType* const a_PtrCmpsData
    )
{
    return AddData( SNSR_ID_CMPS, (uint8_t*)a_PtrCmpsData, sizeof( CompassDataType ) );
}

static boolean AddData
    (
    SensorIdType            a_SensorId,
    const uint8_t* const    a_PtrData,
    uint32_t                a_DataSize
    )
{
    QueueDataType queueItem;

    queueItem.SensorId = a_SensorId;
    queueItem.TimeStamp = xTaskGetTickCount();
    memcpy( &( queueItem.SensorData ), a_PtrData, a_DataSize );

    return ( ( xQueueSend( s_DataQueue, &queueItem, portMAX_DELAY ) != pdTRUE ) ? FALSE : TRUE );
}

static void MainSensorFusion
    (
    void*           a_Ptr
    )
{
    for(;;)
    {
        if( ProcessDataQueue() )
        {
            UpdateQuaternionData();
        }
    }
}

static boolean ProcessDataQueue
    (
    void
    )
{
    QueueDataType   queueItem;
    boolean         success;

    success = FALSE;

    if( pdTRUE == xQueueReceive( s_DataQueue, &queueItem, portMAX_DELAY ) )
    {
        if( SNSR_ID_GYRO == queueItem.SensorId )
            {
            SensorFusion_Debug_Printf
                ((
                "SF: Rx Gyro ts=%d, x=%f, y=%f, z=%f\r\n",
                queueItem.TimeStamp,
                queueItem.SensorData.GyroData.meas[0],
                queueItem.SensorData.GyroData.meas[1],
                queueItem.SensorData.GyroData.meas[2]
                ));
            success = TRUE;
            }
        else if( SNSR_ID_ACCEL == queueItem.SensorId )
            {
            SensorFusion_Debug_Printf
                ((
                "SF: Rx Accl ts=%d, x=%f, y=%f, z=%f\r\n",
                queueItem.TimeStamp,
                queueItem.SensorData.AccelData.meas[0],
                queueItem.SensorData.AccelData.meas[1],
                queueItem.SensorData.AccelData.meas[2]
                ));
            success = TRUE;
            }
        else if( SNSR_ID_CMPS == queueItem.SensorId )
            {
            SensorFusion_Debug_Printf
                ((
                "SF: Rx Cmps ts=%d, x=%f, y=%f, z=%f\r\n",
                queueItem.TimeStamp,
                queueItem.SensorData.CmpsData.meas[0],
                queueItem.SensorData.CmpsData.meas[1],
                queueItem.SensorData.CmpsData.meas[2]
                ));
            success = TRUE;
            }
    }

    return success;

}


static void UpdateQuaternionData
    (
    void
    )
{
    xSemaphoreTake( s_QuaternionData_Mutex, portMAX_DELAY );

    s_QuaternionData.TimeStamp      = xTaskGetTickCount();
    s_QuaternionData.MeasurementX   += 5.0f;
    s_QuaternionData.MeasurementY   += 50.0f;
    s_QuaternionData.MeasurementZ   += 500.0f;
    s_QuaternionData.MeasurementW   += 5000.0f;

    xSemaphoreGive( s_QuaternionData_Mutex );
}