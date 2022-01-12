#pragma once

#include <PubSubClient.h>
#include <WiFi.h>

namespace ProjectGarden
{
namespace HydroBox
{
namespace Esp32
{
    /**
     * MQTT client for communicating with a MQTT Broker server.
     */
    class MqttClient
    {
        public:
            /**
             * Initialize MQTT client.
             */
            MqttClient();

            /**
             * Connect to Wi-Fi network and MQTT Broker server.
             */
            void connect();

            /**
             * Publish message to specified topic.
             * @param topic Topic to publish to.
             * @param message Message to publish.
             */
            void publish(const char* topic, const char* message);

            /**
             * Process incoming messages and maintain connection to MQTT Broker server.
             */
            void loop();

        private:
            /**
             * Connect to Wi-Fi network.
             */
            void connectWifi();

            /**
             * Connect to MQTT Broker server.
             */
            void connectMqtt();

            /**
             *
             * TEMPORARY FUNCTION
             *
             */
            void mqtt_callback(char* topic, byte* payload, unsigned int length);

            /**
             * Mosquitto client.
             */
            PubSubClient* _mqttClient;

            /**
             * Wi-Fi client.
             */
            WiFiClient _wifiClient;
    };
}
}
}