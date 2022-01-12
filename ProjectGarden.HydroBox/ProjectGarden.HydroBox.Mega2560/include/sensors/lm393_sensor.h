#pragma once

#include <base_sensor.h>

using namespace ProjectGarden::HydroBox::Shared;

namespace ProjectGarden
{
namespace HydroBox
{
namespace Mega2560
{
namespace Sensors
{
    /**
     * Soil moisture sensor used to detect leaks.
     */
    class Lm393Sensor : public BaseSensor
    {
        public:
            /**
             * Initialize LM393 sensor.
             * @param sensorMetadata Sensor metadata.
             * @param readFrequencyMs Read frequency in milliseconds.
             */
            Lm393Sensor(SensorMetadata sensorMetadata, unsigned long readFrequencyMs);

            /**
             * Check if a leak has been detected.
             * @param loopMsTimestamp Main loop milliseconds timestamp to base time measurements on.
             * @return 1 if leak has been detected, otherwise 0.
             */
            float leakDetected(unsigned long loopMsTimestamp);
    };
}
}
}
}