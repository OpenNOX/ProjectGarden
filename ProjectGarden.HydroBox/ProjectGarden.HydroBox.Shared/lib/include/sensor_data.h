#pragma once

#include "base_sensor.h"

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    class BaseSensor;

    struct SensorData
    {
        /**
         * MQTT topic used to identify sensor reading.
         */
        const char* mqttTopic;

        /**
         * Pointer to callback function that returns sensor reading for MQTT topic.
         * @param loopMsTimestamp Main loop milliseconds timestamp to base time measurements on.
         */
        float (BaseSensor::*readSensor)(unsigned long loopMsTimestamp) = nullptr;
    };
}
}
}