#include <Arduino.h>
#include "constants.h"
#include <sensor_manager.h>
#include "sensors/lm393_sensor.h"
#include <serial_client.h>
#include <utility.h>

using namespace ProjectGarden::HydroBox::Mega2560;
using namespace ProjectGarden::HydroBox::Mega2560::Sensors;
using namespace ProjectGarden::HydroBox::Shared;

/**
 * Sensor manager to handle sensor readings.
 */
SensorManager* sensorManager;

/**
 * Serial client to communicate with ESP32.
 */
SerialClient* esp32Serial;

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
        case LM393: return new Lm393Sensor(sensorMetadata, ENVIRONMENT_CHECK_FREQUENCY * 1000);
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
    static char messageBuffer[128];
    static char sensorDataBuffer[16];

    strcpy(messageBuffer, mqttTopic);
    strcat(messageBuffer, ":");

    dtostrf(sensorData, strlen(sensorDataBuffer) - 2, 2, sensorDataBuffer);
    strcat(messageBuffer, sensorDataBuffer);

    Serial.println(messageBuffer);

    esp32Serial->transmitMessage(messageBuffer);
}

/**
 * Callback function used as event handler when a message is received on serial connection.
 * @param message Message received.
 */
void serialMessageReceivedHandler(const char* message)
{
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
    esp32Serial = new SerialClient(&Serial3, &serialMessageReceivedHandler);

    Serial.println();
}

/**
 * Board main loop.
 */
void loop()
{
    loopMsTimestamp = millis();

    sensorManager->loop(loopMsTimestamp);
    esp32Serial->loop();
}