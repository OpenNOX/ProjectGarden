#include "sensors/water_flow_sensor.h"
#include <utility.h>

using namespace ProjectGarden::HydroBox::Esp32::Sensors;
using namespace ProjectGarden::HydroBox::Shared;

volatile unsigned int WaterFlowSensor::_reservoirFillPulseCount = 0;

WaterFlowSensor::WaterFlowSensor(SensorMetadata sensorMetadata, unsigned long readFrequencyMs)
    : BaseSensor(sensorMetadata, readFrequencyMs, 1)
{
    dataMap = new SensorData[dataMapCount];
    dataMap[0].mqttTopic = concat(sensorMetadata.mqttTopicBase, "flow_rate_LPM");
    dataMap[0].readSensor = static_cast<ReadSensorCallbackPointer>(&WaterFlowSensor::flowRate);

    pinMode(sensorMetadata.pin, INPUT);

    switch (sensorMetadata.pin)
    {
        case RESERVOIR_FILL_FLOW_DATA_PIN:
            _interruptFunction = &_reservoir_fill_pulse_counter_isr;
            _pulseCount = &WaterFlowSensor::_reservoirFillPulseCount;
            break;

        default:
            break;
    }

    switch (sensorMetadata.sensorModel)
    {
        case FL608:
            _calibrationFactor = 5.5;
            break;

        default:
            break;
    }

    attachInterrupt(sensorMetadata.pin, _interruptFunction, RISING);
}

float WaterFlowSensor::flowRate(unsigned long loopMsTimestamp)
{
    float flowRate = ((1000.0 / (loopMsTimestamp - lastReadMsTimestamp)) * (*_pulseCount)) / _calibrationFactor;

    (*_pulseCount) = 0;

    return flowRate;
}

void IRAM_ATTR WaterFlowSensor::_reservoir_fill_pulse_counter_isr()
{
    WaterFlowSensor::_reservoirFillPulseCount += 1;
}