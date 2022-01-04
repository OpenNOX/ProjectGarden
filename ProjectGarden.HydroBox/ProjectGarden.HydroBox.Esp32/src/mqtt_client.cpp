#include "mqtt_client.h"
#include "secrets.h"

using namespace ProjectGarden::HydroBox::Esp32;

MqttClient::MqttClient()
{
	// TEMPORARY LAMBDA FUNCTION.
	auto callback = [&](char *topic, byte *payload, unsigned int length)
	{
		MqttClient::mqtt_callback(topic, payload, length);
	};

	this->_mqttClient = new PubSubClient(this->_wifiClient);

	this->_mqttClient->setServer(MQTT_ADDRESS, MQTT_PORT);
	this->_mqttClient->setCallback(callback);
}

void MqttClient::connect()
{
	this->connectWifi();
	this->connectMqtt();
}

void MqttClient::publish(String topic, String message)
{
	this->_mqttClient->publish(topic.c_str(), message.c_str());
}

void MqttClient::processIncomingMessages()
{
	this->_mqttClient->loop();
}

void MqttClient::connectWifi()
{
	Serial.printf("Connecting to %s Wi-Fi...\n", WIFI_SSID);

	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(250);
	}

	Serial.printf("\nWi-Fi connected! IP Address: %s\n", WiFi.localIP().toString().c_str());
}

void MqttClient::connectMqtt()
{
	Serial.printf("Connecting to %s MQTT Broker server...\n", MQTT_ADDRESS);

	while (this->_mqttClient->connected() == false)
	{
		if (this->_mqttClient->connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD))
		{
			Serial.print("MQTT server connected!\n");
		}
	}
}

void MqttClient::mqtt_callback(char *topic, byte *payload, unsigned int length)
{
}
