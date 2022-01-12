#pragma once

#include "base_sensor.h"
#include "sensor_data.h"

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Base sensor manager used to manage sensors and their output data.
     */
    class SensorManager
    {
        public:
            /**
             * Initialize base sensor manager.
             * @param sensorCount Number of sensors to be managed.
             * @param newSensorDataCallback Pointer to callback function used as event handler when
             * new data is read.
             */
            SensorManager(const SensorMetadata sensorMetadata[], byte sensorCount,
                void (*newSensorDataCallback)(char const* mqttTopic, float sensorData),
                BaseSensor* (*projectSensorInitializer)(const SensorMetadata& sensorMetadata) = nullptr);

            /**
             * Process sensors and emit new sensor data to callback function.
             * @param loopMsTimestamp Main loop milliseconds timestamp to base time measurements on.
             */
            void loop(unsigned long loopMsTimestamp);

        private:
            /**
             * Array of pointers to monitored sensors.
             */
            BaseSensor** _sensors;

            /**
             * Number of sensors being monitored.
             */
            byte _sensorCount = 0;

            /**
             * Pointer to sensor data points array.
             */
            SensorData** _data;

            /**
             * Number of sensor data points.
             */
            byte _dataCount = 0;

            /**
             * Pointer to callback function used to handle initializing project specific sensors.
             * @param sensorMetadata Sensor metadata.
             * @return nullptr if sensor model should be initialized as part of shared initializer,
             * otherwise pointer to initialized sensor.
             */
            BaseSensor* (*_projectSensorInitializer)(const SensorMetadata& sensorMetadata);

            /**
             * Pointer to callback function used as event handler when new sensor data is read.
             * @param mqttTopic MQTT topic used to identify sensor data.
             * @param sensorData Sensor data value.
             */
            void (*_newSensorDataCallback)(char const* mqttTopic, float sensorData);

            /**
             * Initialize sensors.
             * @param sensorMetadata Sensor metadata.
             */
            void initializeSensors(const SensorMetadata sensorMetadata[]);

            /**
             * Initialize sensor data array.
             */
            void initializeData();
    };
}
}
}