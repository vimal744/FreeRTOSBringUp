/**
  ******************************************************************************
  * File Name          : SensorReaderInterface.h
  * Description        : Implementation for the Sensor Reader Interface
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

/* Public Includes -----------------------------------------------------------*/

#include "SensorReaderInterface.h"
#include "SensorFusionInterface.h"

#include "GyroTypes.h"
#include "AccelTypes.h"
#include "CompassTypes.h"
#include "PrintUtility.h"

#include "FreeRTOS.h"
#include "task.h"

/* Private Includes ----------------------------------------------------------*/


/* Literal Constants ---------------------------------------------------------*/

/* Stack size for the sensor reader thread */
#define SENSOR_MAIN_STACK_SIZE      ( 256 )

/* Printf statement for debugging */
#define SensorReader_Debug_Printf( _args ) //Printf _args

/* Memory Constants ----------------------------------------------------------*/

static const char* c_ThreadName = "SensorReader_Main";

/* Global Variables ----------------------------------------------------------*/

static TaskHandle_t s_SensorReader_Main_Handle;

/* Procedures ----------------------------------------------------------------*/

static void MainSensorReader
    (
    void* a_Ptr
    );

/**
* @brief Power up the sensor Reader thread
*/

void SensorReaderPowerUp
    ( void )
{
    xTaskCreate( MainSensorReader, c_ThreadName, SENSOR_MAIN_STACK_SIZE, NULL, tskIDLE_PRIORITY, &s_SensorReader_Main_Handle );
}

/**
* @brief Init the sensor reader thread
*/

void SensorReaderInit
    ( void )
{

}

/**
* @brief Power down the sensor reader thread
*/

void SensorReaderPowerDown
    ( void )
{
     if( s_SensorReader_Main_Handle != NULL )
     {
         vTaskDelete( s_SensorReader_Main_Handle );
     }
}


/**
* @brief Main for the sensor Reader thread
*
* NOTE: Currently simulating the data because I could not get the sensor board to work
*
*/

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
        // Populate Gyro Data
        gyroData.meas[0] += 1.0f;
        gyroData.meas[1] += 10.0f;
        gyroData.meas[2] += -10.0f;
        SensorReader_Debug_Printf(("SR: Tx Gyro x=%f, y=%f, z=%f\r\n", gyroData.meas[0], gyroData.meas[1], gyroData.meas[2] ));

        // Send Gyro data to Sensor Fusion thread
        SensorFusionAddGyroData( &gyroData );
        osDelay(10);

        // Populate Accel Data
        accelData.meas[0] += 2.0f;
        accelData.meas[1] += 20.0f;
        accelData.meas[2] += -20.0f;

        // Send Accel data to Sensor Fusion thread
        SensorReader_Debug_Printf(("SR: Tx Accl x=%f, y=%f, z=%f\r\n", accelData.meas[0], accelData.meas[1], accelData.meas[2] ));
        SensorFusionAddAccelData( &accelData );
        osDelay(10);

        // Populate Compass Data
        cmpsData.meas[0] += 3.0f;
        cmpsData.meas[1] += 30.0f;
        cmpsData.meas[2] += -30.0f;


        // Send Compass data to Sensor Fusion thread
        SensorReader_Debug_Printf(("SR: Tx Cmps x=%f, y=%f, z=%f\r\n", cmpsData.meas[0], cmpsData.meas[1], cmpsData.meas[2] ));
        SensorFusionAddCompassData( &cmpsData );
        osDelay(1000);
    }
}
