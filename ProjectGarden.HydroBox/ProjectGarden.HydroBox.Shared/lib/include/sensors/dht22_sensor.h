#pragma once

#include <Adafruit_Sensor.h>
#include "base_sensor.h"
#include <DHT.h>

using namespace ProjectGarden::HydroBox::Shared;

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
namespace Sensors
{
    /**
     * DHT22 sensor used to measure temperature and humidity sensor.
     */
    class Dht22Sensor : public BaseSensor
    {
        public:
            /**
             * Initialize DHT22 sensor.
             * @param sensorMetadata Sensor metadata.
             * @param readFrequencyMs Read frequency in milliseconds.
             */
            Dht22Sensor(SensorMetadata sensorMetadata, unsigned long readFrequencyMs);

            /**
             * Get temperature reading measured in Celsius.
             * @param loopMsTimestamp Main loop milliseconds timestamp to base time measurements on.
             * @return Temperature reading measured in Celsius.
             */
            float temperature(unsigned long loopMsTimestamp);

            /**
             * Get relative humidity reading.
             * @param loopMsTimestamp Main loop milliseconds timestamp to base time measurements on.
             * @return Relative humidity reading.
             */
            float humidity(unsigned long loopMsTimestamp);

        private:
            /**
             * Pointer to DHT22 sensor interface.
             */
            DHT* _interface;
    };
}
}
}
}