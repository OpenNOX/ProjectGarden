#ifndef PROJECT_GARDEN_HYDRO_BOX_ESP32_SENSOR_MONITOR_H
#define PROJECT_GARDEN_HYDRO_BOX_ESP32_SENSOR_MONITOR_H

#include <base_sensor_monitor.h>
#include <sensor_metadata.h>

using namespace ProjectGarden::HydroBox::Shared;

namespace ProjectGarden
{
namespace HydroBox
{
namespace Esp32
{
    /**
     * Sensor monitor for timing and reading sensor data.
     */
    class SensorMonitor : public BaseSensorMonitor
    {
        public:
            /**
             * Initialize sensor monitor.
             * @param sensorMetadataMap Map between sensor data pin and metadata.
             */
            SensorMonitor(const MapPair<byte, SensorMetadata> sensorMetadataMap[]);

            /**
             * Check sensors for new data.
             * @param loopMsTimestamp Loop milliseconds timestamp to check against.
             * @return Map between MQTT topic and returned sensor value.
             */
            Map<String, float> checkForNewData(unsigned long loopMsTimestamp);

        private:
            /**
             * Add sensor to list of sensors to monitor.
             * @param pin Pin sensor data pin is on.
             * @param sensorMetadata Sensor metadata.
             */
            void addSensor(byte pin, const SensorMetadata& sensorMetadata);
    };
}
}
}

#endif