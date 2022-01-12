#include "sensors/ds18b20_sensor.h"
#include <utility.h>

using namespace ProjectGarden::HydroBox::Esp32::Sensors;
using namespace ProjectGarden::HydroBox::Shared;

Ds18b20Sensor::Ds18b20Sensor(SensorMetadata sensorMetadata, unsigned long readFrequencyMs)
    : BaseSensor(sensorMetadata, readFrequencyMs, 1)
{
    _oneWire = new OneWire(sensorMetadata.pin);
    _interface = new DallasTemperature(_oneWire);
    _interface->begin();

    dataMap = new SensorData[dataMapCount];
    dataMap[0].mqttTopic = concat(sensorMetadata.mqttTopicBase, "temperature_C");
    dataMap[0].readSensor = static_cast<ReadSensorCallbackPointer>(&Ds18b20Sensor::temperature);
}

float Ds18b20Sensor::temperature(unsigned long loopMsTimestamp)
{
    _interface->requestTemperatures();

    return _interface->getTempCByIndex(0);
}