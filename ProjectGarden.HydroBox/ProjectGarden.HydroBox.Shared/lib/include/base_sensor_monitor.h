#ifndef PROJECT_GARDEN_HYDRO_BOX_SHARED_BASE_SENSOR_MONITOR_H
#define PROJECT_GARDEN_HYDRO_BOX_SHARED_BASE_SENSOR_MONITOR_H

#include "base_sensor.h"
#include "map.h"
#include "stack.h"

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Base sensor monitor for timing and reading sensor data.
     */
    class BaseSensorMonitor
    {
        public:
            /**
             * Add sensor to manager.
             * @param pin Data pin sensor data pin is on.
             * @param sensorMetadata Sensor metadata.
             */
            virtual void addSensor(byte pin, const SensorMetadata& sensorMetadata) = 0;

            /**
             * Check sensors for new data.
             * @param loopMsTimestamp Loop milliseconds timestamp to check against.
             * @return Map between MQTT topic and sensor value.
             */
            Map<String, float> checkForNewData(unsigned long loopMsTimestamp);

        protected:
            /**
             * List of sensors to monitor.
             */
            Stack<BaseSensor*> _sensors;

            /**
             * Get sensors ready to be checked.
             * @param loopMsTimestamp loop milliseconds timestamp to check against.
             * @returns list of sensors ready to be checked.
             */
            Stack<BaseSensor*> getReadySensors(unsigned long loopMsTimestamp);
    };
}
}
}

#endif