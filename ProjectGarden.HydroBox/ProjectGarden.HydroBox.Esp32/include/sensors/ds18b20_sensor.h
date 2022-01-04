#ifndef PROJECT_GARDEN_HYDRO_BOX_ESP32_SENSORS_DS18B20_SENSOR_H
#define PROJECT_GARDEN_HYDRO_BOX_ESP32_SENSORS_DS18B20_SENSOR_H

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
     * DS18B20 waterproof temperature probe sensor.
     */
    class Ds18b20Sensor : public BaseSensor
    {
        public:
            /**
             * Initialize DS18B20 sensor.
             * @param pin Pin DS18B20 data pin is on.
             * @param sensorMetadata Sensor metadata.
             * @param readFrequencyMs Read frequency in milliseconds.
             */
            Ds18b20Sensor(byte pin, SensorMetadata sensorMetadata, unsigned long readFrequencyMs);

            /**
             * Deconstruct DS18B20 sensor.
             */
            ~Ds18b20Sensor();

            /**
             * Read sensor to get temperature in Celsius.
             * @param oneWireIndex Sensor index to read.
             * @return Pointer to map pair between sensor MQTT topic and temperature in Celsius.
             * Temperature values below 0 are not included.
             */
            MapPair<String, float>* get_temperature(byte oneWireIndex = 0);

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

#endif