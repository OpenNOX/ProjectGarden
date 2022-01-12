#pragma once

#include "sensor_model.h"

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Sensor metadata.
     */
    struct SensorMetadata
    {
        /**
         * Pin sensor data pin is on.
         */
        byte pin;

        /**
         * Sensor model.
         */
        SensorModel sensorModel;

        /**
         * Sensor description.
         */
        const char* description;

        /**
         * MQTT topic base.
         */
        const char* mqttTopicBase;
    };
}
}
}