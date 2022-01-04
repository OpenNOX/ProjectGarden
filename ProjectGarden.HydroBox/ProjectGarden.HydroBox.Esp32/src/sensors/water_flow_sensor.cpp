#include <map.h>
#include "sensors/water_flow_sensor.h"

using namespace ProjectGarden::HydroBox::Esp32::Sensors;
using namespace ProjectGarden::HydroBox::Shared;

volatile unsigned int WaterFlowSensor::_reservoirFillPulseCount = 0;

WaterFlowSensor::WaterFlowSensor(byte pin, SensorMetadata sensorMetadata, unsigned long readFrequencyMs)
    : BaseSensor(pin, sensorMetadata, readFrequencyMs)
{
    pinMode(pin, INPUT);

    switch (pin)
    {
        case RESERVOIR_FILL_FLOW_DATA_PIN:
            this->_interruptFunction = &this->_reservoir_fill_pulse_counter_isr;
            this->_pulseCount = &WaterFlowSensor::_reservoirFillPulseCount;
            break;

        default:
            break;
    }

    switch (this->sensorMetadata.sensorModel)
    {
        case FL608:
            this->_calibrationFactor = 5.5;
            break;

        default:
            break;
    }

    attachInterrupt(pin, this->_interruptFunction, RISING);
}

WaterFlowSensor::~WaterFlowSensor()
{
    delete this->_pulseCount;
}

// Update function to get_sensor_data and include volume.
MapPair<String, float>* WaterFlowSensor::get_flow_rate(unsigned long loopMsTimestamp)
{
    float flowRate = ((1000.0 / (loopMsTimestamp - this->lastReadMsTimestamp)) * (*this->_pulseCount)) / this->_calibrationFactor;

    (*this->_pulseCount) = 0;

    return new MapPair<String, float> { this->sensorMetadata.mqttTopicBase + "flow_rate_LPM", flowRate };
}

void IRAM_ATTR WaterFlowSensor::_reservoir_fill_pulse_counter_isr()
{
    WaterFlowSensor::_reservoirFillPulseCount += 1;
}