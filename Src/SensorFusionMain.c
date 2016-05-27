/**
  ******************************************************************************
  * File Name          : SensorFusionMain.h
  * Description        : Implementation for the Sensor Fusion Interface
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

/* Public Includes -----------------------------------------------------------*/

#include "SensorFusionInterface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "PrintUtility.h"
#include <queue.h>
#include <string.h>
#include <semphr.h>

/* Private Includes ----------------------------------------------------------*/


/* Literal Constants ---------------------------------------------------------*/

/* Stack size for the sensor fusion thread */
#define SENSOR_FUSION_MAIN_STACK_SIZE      ( 256 )

/* Printf statement for debugging */
#define SensorFusion_Debug_Printf( _args ) //Printf _args

/* Memory Constants ----------------------------------------------------------*/

static const char* c_ThreadName = "SensorFusion_Main";

/* Types ---------------------------------------------------------------------*/

/* Sensor Id Type */
typedef uint8_t SensorIdType; enum
{
    SNSR_ID_GYRO    = 0,
    SNSR_ID_ACCEL   = 1,
    SNSR_ID_CMPS    = 2,

    SNSR_ID_CNT
};


/* Structure to hold the incoming sensor data */
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


/* Global Variables ----------------------------------------------------------*/

static TaskHandle_t                 s_SensorFusion_Main_Handle;
static QueueHandle_t                s_DataQueue;
static SensorQuaternionDataType     s_QuaternionData;
static SemaphoreHandle_t            s_QuaternionData_Mutex;

/* Procedures ----------------------------------------------------------------*/

static boolean AddData
    (
    SensorIdType            a_SensorId,
    const uint8_t* const    a_PtrData,
    uint32_t                a_DataSize
    );

static void MainSensorFusion
    (
    void* a_Ptr
    );

static boolean ProcessDataQueue
    (
    void
    );

static void UpdateQuaternionData
    (
    void
    );


/**
* @brief Power up the sensor fusion thread
*/

void SensorFusionPowerUp
    ( void )
{
    // Create the mutex
    s_QuaternionData_Mutex = xSemaphoreCreateRecursiveMutex();

    // Create the queue to hold the incoming sensor data
    s_DataQueue            = xQueueCreate( 32, sizeof( QueueDataType ) );

    // Create the sensor fusion thread
    xTaskCreate( MainSensorFusion, c_ThreadName, SENSOR_FUSION_MAIN_STACK_SIZE, NULL, tskIDLE_PRIORITY, &s_SensorFusion_Main_Handle );
}

/**
* @brief Init the sensor fusion thread
*/

void SensorFusionInit
    ( void )
{
    // Reset the static variables
    memset( &s_QuaternionData, 0, sizeof( SensorQuaternionDataType ) );
}

/**
* @brief Power down the sensor fusion thread
*/

void SensorFusionPowerDown
    ( void )
{
     if( s_SensorFusion_Main_Handle != NULL )
     {
         vTaskDelete( s_SensorFusion_Main_Handle );
     }
}

/**
* @brief Interface to the quaternion data from the SF thread
*/

void SensorFusionGetQuaternionData
    (
    const SensorQuaternionDataType* a_PtrData
    )
{
    xSemaphoreTake( s_QuaternionData_Mutex, portMAX_DELAY );
    memcpy( (void*)a_PtrData, &s_QuaternionData, sizeof( SensorQuaternionDataType ) );
    xSemaphoreGive( s_QuaternionData_Mutex );
}

/**
* @brief Interface to add Gyro data to the SF thread
*/

boolean SensorFusionAddGyroData
    (
    const GyroDataType* const a_PtrGyroData
    )
{
    return AddData( SNSR_ID_GYRO, (uint8_t*)a_PtrGyroData, sizeof( GyroDataType ) );
}

/**
* @brief Interface to add Accel data to the SF thread
*/

boolean SensorFusionAddAccelData
    (
    const AccelDataType* const a_PtrAccelData
    )
{
    return AddData( SNSR_ID_ACCEL, (uint8_t*)a_PtrAccelData, sizeof( AccelDataType ) );
}


/**
* @brief Interface to add Compass data to the SF thread
*/

boolean SensorFusionAddCompassData
    (
    const CompassDataType* const a_PtrCmpsData
    )
{
    return AddData( SNSR_ID_CMPS, (uint8_t*)a_PtrCmpsData, sizeof( CompassDataType ) );
}

/**
* @brief Interface to add data to the SF thread
*/

static boolean AddData
    (
    SensorIdType            a_SensorId,
    const uint8_t* const    a_PtrData,
    uint32_t                a_DataSize
    )
{
    // Create an instance of the queue item
    QueueDataType queueItem;

    // Populate the queue item
    queueItem.SensorId = a_SensorId;
    queueItem.TimeStamp = xTaskGetTickCount();
    memcpy( &( queueItem.SensorData ), a_PtrData, a_DataSize );

    // Add the item to the queue.
    return ( ( xQueueSend( s_DataQueue, &queueItem, portMAX_DELAY ) != pdTRUE ) ? FALSE : TRUE );
}

/**
* @brief Main for the sensor application thread
*/

static void MainSensorFusion
    (
    void*           a_Ptr
    )
{
    for(;;)
    {
        // Process the data in the queue
        if( ProcessDataQueue() )
        {
            // Update the quaternion data
            UpdateQuaternionData();
        }
    }
}

/**
* @brief Process the sensor data in the queue
*/

static boolean ProcessDataQueue
    (
    void
    )
{
    QueueDataType   queueItem;
    boolean         success;

    success = FALSE;

    // If the data was read properly from the queue
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


/**
* @brief Update the quaternion data
*
* NOTE: Currently simulating the data because I could not get the sensor board to work
*/
static void UpdateQuaternionData
    (
    void
    )
{
    xSemaphoreTake( s_QuaternionData_Mutex, portMAX_DELAY );

    s_QuaternionData.TimeStamp      = xTaskGetTickCount();
    s_QuaternionData.MeasurementX   += 5.5f;
    s_QuaternionData.MeasurementY   += 50.23f;
    s_QuaternionData.MeasurementZ   += 500.123f;
    s_QuaternionData.MeasurementW   += -5000.1312f;

    xSemaphoreGive( s_QuaternionData_Mutex );
}
