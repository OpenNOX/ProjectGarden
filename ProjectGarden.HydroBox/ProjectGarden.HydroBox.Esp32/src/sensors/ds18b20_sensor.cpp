#include "sensors/ds18b20_sensor.h"

using namespace ProjectGarden::HydroBox::Esp32::Sensors;
using namespace ProjectGarden::HydroBox::Shared;

Ds18b20Sensor::Ds18b20Sensor(byte pin, SensorMetadata sensorMetadata, unsigned long readFrequencyMs)
    : BaseSensor(pin, sensorMetadata, readFrequencyMs)
{
    this->_oneWire = new OneWire(pin);
    this->_interface = new DallasTemperature(this->_oneWire);
    this->_interface->begin();
}

Ds18b20Sensor::~Ds18b20Sensor()
{
    delete this->_interface;
    delete this->_oneWire;
}

MapPair<String, float>* Ds18b20Sensor::get_temperature(byte oneWireIndex)
{
    this->_interface->requestTemperatures();

    float value = this->_interface->getTempCByIndex(oneWireIndex);
    if (value > 0)
    {
        return new MapPair<String, float> { this->sensorMetadata.mqttTopicBase + "temperature_C", value };
    }

    return nullptr;
}