/**
  ******************************************************************************
  * File Name          : SensorApplicationInterface.h
  * Description        : Implementation for the Sensor Application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 Vimal Mehta
  *
  ******************************************************************************
  */

/* Public Includes -----------------------------------------------------------*/

#include "SensorApplicationInterface.h"
#include "SensorFusionInterface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "PrintUtility.h"

#include <queue.h>
#include <string.h>

/* Private Includes ----------------------------------------------------------*/


/* Literal Constants ---------------------------------------------------------*/

#define SENSOR_APP_MAIN_STACK_SIZE      ( 256 )

/* Memory Constants ----------------------------------------------------------*/

static const char* c_ThreadName = "SensorApp_Main";

/* Types ---------------------------------------------------------------------*/

/* Global Variables ----------------------------------------------------------*/

static TaskHandle_t     s_SensorApp_Main_Handle;

/* Procedures ----------------------------------------------------------------*/

static void MainSensorApp
    (
    void* a_Ptr
    );

/**
* @brief Power up the sensor application
*/

void SensorApplicationPowerUp
    ( void )
{
    // Create the sensor application thread
    xTaskCreate( MainSensorApp, c_ThreadName, SENSOR_APP_MAIN_STACK_SIZE, NULL, tskIDLE_PRIORITY, &s_SensorApp_Main_Handle );
}

/**
* @brief Init the sensor application
*/

void SensorApplicationInit
    ( void )
{

}

/**
* @brief Power down the sensor application
*/

void SensorApplicationPowerDown
    ( void )
{
     if( s_SensorApp_Main_Handle != NULL )
     {
         vTaskDelete( s_SensorApp_Main_Handle );
     }
}


/**
* @brief Main for the sensor application thread
*/
static void MainSensorApp
    (
    void*           a_Ptr
    )
{
    for(;;)
    {
        SensorQuaternionDataType quaternionSensorData;

        // Get the Quaternion data from the sensor fusion interface
        SensorFusionGetQuaternionData(&quaternionSensorData);

        // Write the data to the console
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

