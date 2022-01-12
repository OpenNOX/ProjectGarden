#include "sensor_manager.h"
#include "sensors/dht22_sensor.h"

using namespace ProjectGarden::HydroBox::Shared;
using namespace ProjectGarden::HydroBox::Shared::Sensors;

SensorManager::SensorManager(const SensorMetadata sensorMetadata[], byte sensorCount,
    void (*newSensorDataCallback)(char const* mqttTopic, float sensorData),
    BaseSensor* (*projectSensorInitializer)(const SensorMetadata& sensorMetadata))
{
    _sensorCount = sensorCount;
    _sensors = new BaseSensor*[_sensorCount];

    _newSensorDataCallback = newSensorDataCallback;
    _projectSensorInitializer = projectSensorInitializer;

    initializeSensors(sensorMetadata);
    initializeData();
}

void SensorManager::loop(unsigned long loopMsTimestamp)
{
    for (byte sensorIndex = 0; sensorIndex < _sensorCount; sensorIndex += 1)
    {
        BaseSensor* sensor = _sensors[sensorIndex];

        if (sensor->isReadyToRead(loopMsTimestamp))
        {
            for (byte dataIndex = 0; dataIndex < sensor->dataMapCount; dataIndex += 1)
            {
                SensorData sensorData = sensor->dataMap[dataIndex];

                _newSensorDataCallback(sensorData.mqttTopic, (sensor->*sensorData.readSensor)(loopMsTimestamp));

                sensor->lastReadMsTimestamp = loopMsTimestamp;
            }
        }
    }
}

void SensorManager::initializeSensors(const SensorMetadata sensorMetadata[])
{
    static const char* addedSensorFormat = "Added %s sensor on pin %hhu to sensor monitor!";
    static char message[64];

    for (byte i = 0; i < _sensorCount; i += 1)
    {
        if (_projectSensorInitializer != nullptr)
        {
            _sensors[i] = _projectSensorInitializer(sensorMetadata[i]);
        }

        if (_sensors[i] == nullptr)
        {
            switch (sensorMetadata[i].sensorModel)
            {
                case DHT22:
                    _sensors[i] = new Dht22Sensor(sensorMetadata[i], ENVIRONMENT_CHECK_FREQUENCY * 1000);
                    break;

                default:
                    break;
            }
        }

        snprintf(message, sizeof(message), addedSensorFormat, sensorMetadata[i].description, sensorMetadata[i].pin);

        Serial.println(message);

        _dataCount += _sensors[i]->dataMapCount;
    }
}

void SensorManager::initializeData()
{
    _data = new SensorData*[_dataCount];

    byte sensorDataIndex = 0;
    for (byte sensorIndex = 0; sensorIndex < _sensorCount; sensorIndex += 1)
    {
        BaseSensor* sensor = _sensors[sensorIndex];

        for (byte dataMapIndex = 0; dataMapIndex < sensor->dataMapCount; dataMapIndex += 1)
        {
            _data[sensorDataIndex++] = &sensor->dataMap[dataMapIndex];
        }
    }
}