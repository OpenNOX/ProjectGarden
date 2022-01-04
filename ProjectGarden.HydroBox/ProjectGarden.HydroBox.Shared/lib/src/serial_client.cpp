#include "serial_client.h"
#include "shared_constants.h"

using namespace ProjectGarden::HydroBox::Shared;

SerialClient::SerialClient(HardwareSerial* hardwareSerial) : _interface { hardwareSerial }
{
    this->_interface->begin(SERIAL_BAUD_RATE);
}

void SerialClient::transmitMessage(const String& message)
{
    this->_interface->print(SerialClient::_START_MESSAGE_DELIMITER + message + SerialClient::_END_MESSAGE_DELIMITER);
}

String SerialClient::receiveMessage()
{
    while (this->_interface->available() > 0)
    {
        char readChar = this->_interface->read();

        if (this->_receivingMessage)
        {
            if (readChar == SerialClient::_END_MESSAGE_DELIMITER)
            {
                return this->_receivedMessage;
            }
            else
            {
                this->_receivedMessage += readChar;
            }
        }
        else if (readChar == SerialClient::_START_MESSAGE_DELIMITER)
        {
            this->_receivingMessage = true;
            this->_receivedMessage = "";
        }
    }

    return "";
}

MapPair<String, float> SerialClient::parseSensorData(const String& serialMessage)
{
    byte delimiterIndex = serialMessage.indexOf(SerialClient::_MESSAGE_DELIMITER);
    String mqttTopic = serialMessage.substring(0, delimiterIndex);
    float value = serialMessage.substring(delimiterIndex + 1).toFloat();

    return MapPair<String, float> { mqttTopic, value };
}