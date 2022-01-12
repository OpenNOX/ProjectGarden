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

	_mqttClient = new PubSubClient(_wifiClient);

	_mqttClient->setServer(MQTT_ADDRESS, MQTT_PORT);
	_mqttClient->setCallback(callback);
}

void MqttClient::connect()
{
	connectWifi();
	connectMqtt();
}

void MqttClient::publish(const char* topic, const char* message)
{
	_mqttClient->publish(topic, message);
}

void MqttClient::loop()
{
	_mqttClient->loop();
}

void MqttClient::connectWifi()
{
	Serial.printf("Connecting to %s Wi-Fi...\n", WIFI_SSID);

	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(250);
	}

	Serial.printf("Wi-Fi connected! IP Address: %s\n", WiFi.localIP().toString().c_str());
}

void MqttClient::connectMqtt()
{
	Serial.printf("Connecting to %s MQTT Broker server...\n", MQTT_ADDRESS);

	while (_mqttClient->connected() == false)
	{
		if (_mqttClient->connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD))
		{
			Serial.print("MQTT server connected!\n");
		}
	}
}

void MqttClient::mqtt_callback(char *topic, byte *payload, unsigned int length)
{
}
