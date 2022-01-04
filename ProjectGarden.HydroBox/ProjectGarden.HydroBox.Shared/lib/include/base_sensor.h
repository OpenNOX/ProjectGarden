#ifndef PROJECT_GARDEN_HYDRO_BOX_SHARED_BASE_SENSOR_H
#define PROJECT_GARDEN_HYDRO_BOX_SHARED_BASE_SENSOR_H

#include <Arduino.h>
#include "map.h"
#include "sensor_metadata.h"
#include "sensor_model.h"

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Base sensor for shared properties between sensors.
     */
    class BaseSensor
    {
        public:
            /**
             * Pin sensor data pin is on.
             */
            const byte pin;

            /**
             * Sensor metadata.
             */
            const SensorMetadata sensorMetadata;

            /**
             * Read frequency in milliseconds.
             */
            const unsigned long readFrequencyMs;

            /**
             * Last read milliseconds timestamp.
             */
            unsigned long lastReadMsTimestamp;

            /**
             * Initialize base sensor.
             * @param pin Pin sensor data pin is on.
             * @param sensorMetadata Sensor metadata.
             * @param readFrequencyMs Read frequency in milliseconds.
             */
            BaseSensor(byte pin, SensorMetadata sensorMetadata, unsigned long readFrequencyMs)
                : pin { pin }, sensorMetadata { sensorMetadata }, readFrequencyMs { readFrequencyMs },
                lastReadMsTimestamp { millis() }
            {
            }

            /**
             * Deconstruct base sensor.
             */
            virtual ~BaseSensor()
            {
            }
    };
}
}
}

#endif