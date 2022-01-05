#include "sensor_monitor.h"
#include "sensors.h"

using namespace ProjectGarden::HydroBox::Esp32;
using namespace ProjectGarden::HydroBox::Esp32::Sensors;

SensorMonitor::SensorMonitor(const MapPair<byte, SensorMetadata> sensorMetadataMap[], byte sensorCount)
{
    for (byte i = 0; i < sensorCount; i += 1)
    {
        this->addSensor(sensorMetadataMap[i].key, sensorMetadataMap[i].value);
    }
}

Map<String, float> SensorMonitor::checkForNewData(unsigned long loopMsTimestamp)
{
    Map<String, float> sensorData;

    Stack<BaseSensor*> readySensors = this->getReadySensors(loopMsTimestamp);

    for (BaseSensor* readySensor : readySensors)
    {
        switch (readySensor->sensorMetadata.sensorModel)
        {
            case SensorModel::DHT22:
                sensorData.insert(*static_cast<Dht22Sensor*>(readySensor)->get_sensor_data());
                break;

            case DS18B20:
                sensorData.insert(static_cast<Ds18b20Sensor*>(readySensor)->get_temperature());
                break;

            case FL608:
                sensorData.insert(static_cast<WaterFlowSensor*>(readySensor)->get_flow_rate(loopMsTimestamp));
                break;
        }

        readySensor->lastReadMsTimestamp = loopMsTimestamp;
    }

    return sensorData;
}

void SensorMonitor::addSensor(byte pin, const SensorMetadata& sensorMetadata)
{
    switch (sensorMetadata.sensorModel)
    {
        case SensorModel::DHT22:
            this->_sensors.insert(new Dht22Sensor(pin, sensorMetadata, ENVIRONMENT_CHECK_FREQUENCY * 1000));
            break;

        case DS18B20:
            this->_sensors.insert(new Ds18b20Sensor(pin, sensorMetadata, ENVIRONMENT_CHECK_FREQUENCY * 1000));
            break;

        case FL608:
            this->_sensors.insert(new WaterFlowSensor(pin, sensorMetadata, PULSE_COUNT_CHECK_FREQUENCY * 1000));
            break;
    }

    Serial.printf("Added %s sensor on pin %hhu!\n", sensorMetadata.description.c_str(), pin);
}