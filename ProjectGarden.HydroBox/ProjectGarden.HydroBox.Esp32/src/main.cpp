#include <Arduino.h>
#include "constants.h"
#include "mqtt_client.h"
#include <sensor_manager.h>
#include "sensors/ds18b20_sensor.h"
#include "sensors/water_flow_sensor.h"
#include <serial_client.h>
#include <utility.h>

using namespace ProjectGarden::HydroBox::Esp32;
using namespace ProjectGarden::HydroBox::Esp32::Sensors;
using namespace ProjectGarden::HydroBox::Shared;

/**
 * Sensor manager to handle sensor readings.
 */
SensorManager* sensorManager;

/**
 * Serial client to communicate with Mega 2560.
 */
SerialClient* mega2560Serial;

/**
 * MQTT client to communicate with broker server.
 */
MqttClient* mqttClient;

/**
 * Loop milliseconds timestamp to base time measurements on.
 */
unsigned long loopMsTimestamp;

/**
 * Project specific sensor initializer.
 * @param sensorMetadata Constant reference to sensor metadata.
 * @return nullptr if shared sensor initializer should be used, otherwise pointer to new project
 * specific sensor.
 */
BaseSensor* projectSensorInitializer(const SensorMetadata& sensorMetadata)
{
    switch (sensorMetadata.sensorModel)
    {
        case DS18B20: return new Ds18b20Sensor(sensorMetadata, ENVIRONMENT_CHECK_FREQUENCY * 1000);
        case FL608: return new WaterFlowSensor(sensorMetadata, PULSE_COUNT_CHECK_FREQUENCY * 1000);
        default: return nullptr;
    }
}

/**
 * Handle when new sensor data is read.
 * @param mqttTopic MQTT topic used to identify sensor data.
 * @param sensorData Sensor data value.
 */
void sensorDataHandler(const char* mqttTopic, float sensorData)
{
    static char sensorDataBuffer[16];

    snprintf(sensorDataBuffer, sizeof(sensorDataBuffer), "%.2f", sensorData);

    Serial.printf("%s:%s\n", mqttTopic, sensorDataBuffer);

    // mqttClient->publish(mqttTopic, sensorDataBuffer);
}

/**
 * Callback function used when message is received on serial connection.
 * @param message Message received.
 */
void serialMessageReceivedHandler(const char* message)
{
    static char mqttTopic[128];
    static char sensorData[16];

    byte delimiterIndex = strchr(message, ':') - message;
    byte dataLength = strlen(message) - delimiterIndex;

    memcpy(mqttTopic, &message[0], delimiterIndex);
    mqttTopic[delimiterIndex] = '\0';

    memcpy(sensorData, &message[delimiterIndex + 1], dataLength);
    sensorData[dataLength + 1] = '\0';

    sensorDataHandler(mqttTopic, atof(sensorData));
}

/**
 * Initialize board.
 */
void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println();

    sensorManager = new SensorManager(SENSOR_METADATA, sizeof(SENSOR_METADATA) / sizeof(SENSOR_METADATA[0]),
        &sensorDataHandler, &projectSensorInitializer);
    mega2560Serial = new SerialClient(&Serial2, &serialMessageReceivedHandler);

    Serial.println();

    mqttClient = new MqttClient();
    mqttClient->connect();

    Serial.println();
}

/**
 * Board main loop.
 */
void loop()
{
    loopMsTimestamp = millis();

    sensorManager->loop(loopMsTimestamp);
    mega2560Serial->loop();
    mqttClient->loop();
}