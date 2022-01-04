#ifndef PROJECT_GARDEN_HYDRO_BOX_ESP32_SENSORS_DHT22_SENSOR_H
#define PROJECT_GARDEN_HYDRO_BOX_ESP32_SENSORS_DHT22_SENSOR_H

#include <Adafruit_Sensor.h>
#include <base_sensor.h>
#include <DHT.h>

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
     * DHT22 temperature and humidity sensor.
     */
    class Dht22Sensor : public BaseSensor
    {
        public:
            /**
             * Initialize DHT22 sensor.
             * @param pin Pin DHT22 data pin is on.
             * @param sensorMetadata Sensor metadata.
             * @param readFrequencyMs Read frequency in milliseconds.
             */
            Dht22Sensor(byte pin, SensorMetadata sensorMetadata, unsigned long readFrequencyMs);

            /**
             * Deconstruct DHT22 sensor.
             */
            ~Dht22Sensor();

            /**
             * Read sensor to get temperature in Celsius and relative humidity.
             * @return Pointer to map between sensor MQTT topic and environment values. Environment
             * values of `nan` are not included.
             */
            Map<String, float>* get_sensor_data();

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

#endif