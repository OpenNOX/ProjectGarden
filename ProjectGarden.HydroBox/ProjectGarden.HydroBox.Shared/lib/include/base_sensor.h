#pragma once

#include <Arduino.h>
#include "sensor_data.h"
#include "sensor_metadata.h"

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    struct SensorData;

    /**
     * Base sensor.
     */
    class BaseSensor
    {
        public:
            /**
             * Sensor metadata.
             */
            const SensorMetadata sensorMetadata;

            /**
             * Read frequency in milliseconds.
             */
            const unsigned long readFrequencyMs;

            /**
             * Data map between MQTT topic and its value getter.
             */
            SensorData* dataMap;

            /**
             * Number of pairs that map between MQTT topic and its value getter.
             */
            const byte dataMapCount;

            /**
             * Last read milliseconds timestamp.
             */
            unsigned long lastReadMsTimestamp = 0;

            /**
             * Initialize base sensor.
             * @param sensorMetadata Sensor metadata.
             * @param readFrequencyMs Read frequency in milliseconds.
             * @param dataMapCount Number of pairs that map between MQTT topic and its value getter.
             */
            BaseSensor(SensorMetadata sensorMetadata, unsigned long readFrequencyMs, byte dataMapCount);

            /**
             * Check if the read frequency duration has elapsed since the last read.
             * @param loopMsTimestamp Main loop milliseconds timestamp to base time measurements on.
             */
            bool isReadyToRead(unsigned long loopMsTimestamp);
    };

    /**
     * Base sensor function pointer used to call value getter in sensor data map.
     */
    typedef float (BaseSensor::*ReadSensorCallbackPointer)(unsigned long);
}
}
}