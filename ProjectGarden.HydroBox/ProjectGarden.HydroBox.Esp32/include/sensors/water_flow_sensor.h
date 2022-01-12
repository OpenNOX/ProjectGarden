#pragma once

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
     * Water flow sensor used to measure flow rate.
     */
    class WaterFlowSensor : public BaseSensor
    {
        public:
            /**
             * Initialize water flow sensor.
             * @param sensorMetadata Sensor metadata.
             * @param readFrequencyMs Read frequency in milliseconds.
             */
            WaterFlowSensor(SensorMetadata sensorMetadata, unsigned long readFrequencyMs);

            /**
             * Get flow rate measured in liters per minute.
             * @param loopMsTimestamp Main loop milliseconds timestamp to base time measurements on.
             * @return Flow rate measured in liters per minute.
             */
            float flowRate(unsigned long loopMsTimestamp);

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