#include <sensor_model.h>
#include "sensors/dht22_sensor.h"

using namespace ProjectGarden::HydroBox::Esp32::Sensors;

Dht22Sensor::Dht22Sensor(byte pin, SensorMetadata sensorMetadata, unsigned long readFrequencyMs)
    : BaseSensor(pin, sensorMetadata, readFrequencyMs)
{
    this->_interface = new DHT(pin, 22);
    this->_interface->begin();
}

Dht22Sensor::~Dht22Sensor()
{
    delete this->_interface;
}

Map<String, float>* Dht22Sensor::get_sensor_data()
{
    Map<String, float>* sensorValues = new Map<String, float>();

    float value = this->_interface->readTemperature();
    if (isnan(value) == false)
    {
        sensorValues->insert(
            new MapPair<String, float> { this->sensorMetadata.mqttTopicBase + "temperature_C", value });
    }

    value = this->_interface->readHumidity();
    if (isnan(value) == false)
    {
        sensorValues->insert(new MapPair<String, float> { this->sensorMetadata.mqttTopicBase + "humidity", value });
    }

    return sensorValues;
}
