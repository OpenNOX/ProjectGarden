#include <Arduino.h>
#include "constants.h"
#include "mqtt_client.h"
#include "sensor_monitor.h"
#include <serial_client.h>
#include <shared_constants.h>

using namespace ProjectGarden::HydroBox::Esp32;
using namespace ProjectGarden::HydroBox::Shared;

/**
 * MQTT client to communicate with broker server.
 */
MqttClient* mqttClient;

/**
 * Sensor monitor to handle sensor readings.
 */
SensorMonitor* sensorMonitor;

/**
 * Serial client to communicate with Mega 2560.
 */
SerialClient* mega2560Serial;

/**
 * Loop milliseconds timestamp to base time measurements on.
 */
unsigned long loopMsTimestamp;

/**
 * Initialize board.
 */
void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println();

    mega2560Serial = new SerialClient(&Serial2);
    sensorMonitor = new SensorMonitor(SENSOR_METADATA_MAP, sizeof(SENSOR_METADATA_MAP) / sizeof(SENSOR_METADATA_MAP[0]));

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

    auto sensorData = sensorMonitor->checkForNewData(loopMsTimestamp);

    auto receivedMessage = mega2560Serial->receiveMessage();
    if (receivedMessage.isEmpty() == false)
    {
        sensorData.insert(mega2560Serial->parseSensorData(receivedMessage));
    }

    if (sensorData.isEmpty() == false)
    {
        Serial.println("-------------");

        for (MapPair<String, float> data : sensorData)
        {
            if (data.value != 0)
            {
                Serial.printf("%s: %.2f\n", data.key.c_str(), data.value);
            }
        }
    }

    mqttClient->processIncomingMessages();
}