#include "sensors/lm393_sensor.h"

using namespace ProjectGarden::HydroBox::Mega2560::Sensors;

Lm393Sensor::Lm393Sensor(SensorMetadata sensorMetadata, unsigned long readFrequencyMs)
    : BaseSensor(sensorMetadata, readFrequencyMs, 1)
{
    dataMap = new SensorData[dataMapCount];
    dataMap[0].mqttTopic = sensorMetadata.mqttTopicBase;
    dataMap[0].readSensor = static_cast<ReadSensorCallbackPointer>(&leakDetected);
}

float Lm393Sensor::leakDetected(unsigned long loopMsTimestamp)
{
    if (analogRead(sensorMetadata.pin) < 1000)
    {
        return 1;
    }

    return 0;
}