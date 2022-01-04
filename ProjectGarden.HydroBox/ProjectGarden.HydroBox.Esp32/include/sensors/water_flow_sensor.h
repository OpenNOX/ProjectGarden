#ifndef PROJECT_GARDEN_HYDRO_BOX_ESP32_SENSORS_WATER_FLOW_SENSOR_H
#define PROJECT_GARDEN_HYDRO_BOX_ESP32_SENSORS_WATER_FLOW_SENSOR_H

#include <base_sensor.h>

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
     * Water flow sensor.
     */
    class WaterFlowSensor : public BaseSensor
    {
        public:
            /**
             * Initialize water flow sensor.
             * @param pin Pin water flow sensor data pin is on.
             * @param sensorMetadata Sensor metadata.
             * @param readFrequencyMs Read frequency in milliseconds.
             */
            WaterFlowSensor(byte pin, SensorMetadata sensorMetadata, unsigned long readFrequencyMs);

            /**
             * Deconstruct water flow sensor.
             */
            ~WaterFlowSensor();

            /**
             * Calculate flow rate in liters per minute.
             * @param loopMsTimestamp Loop milliseconds timestamp to use in calculation.
             * @return Pointer to map pair between sensor MQTT topic and flow rate in liters per
             * minute.
             */
            MapPair<String, float>* get_flow_rate(unsigned long loopMsTimestamp);

        private:
            /**
             * Reservoir fill pulse count.
             */
            static volatile unsigned int _reservoirFillPulseCount;

            /**
             * Reservoir fill pulse counter interrupt service routine.
             */
            static void IRAM_ATTR _reservoir_fill_pulse_counter_isr();

            /**
             * Interrupt function used to count number of pulses.
             */
            void (*_interruptFunction)();

            /**
             * Pulse count.
             */
            volatile unsigned int* _pulseCount;

            /**
             * Number of pulses the hall-effect flow sensor outputs per second per liter/minute
             * of flow.
             */
            float _calibrationFactor;
    };
}
}
}
}

#endif