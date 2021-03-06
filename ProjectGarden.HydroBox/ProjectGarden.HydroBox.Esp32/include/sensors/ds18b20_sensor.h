#pragma once

#include <base_sensor.h>
#include <DallasTemperature.h>

using namespace ProjectGarden::HydroBox::Shared;

namespace ProjectGarden
{
namespace HydroBox
{
namespace Esp32
{
namespace Sensors
{
    /**
     * DS18B20 waterproof probe sensor used to measure temperature.
     */
    class Ds18b20Sensor : public BaseSensor
    {
        public:
            /**
             * Initialize DS18B20 sensor.
             * @param sensorMetadata Sensor metadata.
             * @param readFrequencyMs Read frequency in milliseconds.
             */
            Ds18b20Sensor(SensorMetadata sensorMetadata, unsigned long readFrequencyMs);

            /**
             * Get temperature reading measured in Celsius.
             * @param loopMsTimestamp Main loop milliseconds timestamp to base time measurements on.
             * @return Temperature reading measured in Celsius.
             */
            float temperature(unsigned long loopMsTimestamp);

        private:
            /**
             * Pointer to DallasTemperature interface dependency.
             */
            OneWire* _oneWire;

            /**
             * Pointer to DS18B20 sensor interface.
             */
            DallasTemperature* _interface;
    };
}
}
}
}