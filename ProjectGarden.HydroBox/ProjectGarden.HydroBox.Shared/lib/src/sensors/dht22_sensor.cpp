#include "sensors/dht22_sensor.h"
#include <utility.h>

using namespace ProjectGarden::HydroBox::Shared::Sensors;

Dht22Sensor::Dht22Sensor(SensorMetadata sensorMetadata, unsigned long readFrequencyMs)
    : BaseSensor(sensorMetadata, readFrequencyMs, 2)
{
    _interface = new DHT(sensorMetadata.pin, 22);
    _interface->begin();

    dataMap = new SensorData[dataMapCount];
    dataMap[0].mqttTopic = concat(sensorMetadata.mqttTopicBase, "temperature_C");
    dataMap[0].readSensor = static_cast<ReadSensorCallbackPointer>(&Dht22Sensor::temperature);
    dataMap[1].mqttTopic = concat(sensorMetadata.mqttTopicBase, "humidity");
    dataMap[1].readSensor = static_cast<ReadSensorCallbackPointer>(&Dht22Sensor::humidity);
}

float Dht22Sensor::temperature(unsigned long loopMsTimestamp)
{
    return _interface->readTemperature();
}

float Dht22Sensor::humidity(unsigned long loopMsTimestamp)
{
    return _interface->readHumidity();
}