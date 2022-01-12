#include "serial_client.h"
#include "utility.h"

using namespace ProjectGarden::HydroBox::Shared;

SerialClient::SerialClient(
    HardwareSerial* hardwareSerial, void (*messageReceivedCallback)(char const* message))
    : _interface { hardwareSerial }, _messageReceivedCallback { messageReceivedCallback }
{
    _interface->begin(SERIAL_BAUD_RATE);
}

void SerialClient::loop()
{
    char* receivedMessage = receiveMessage();

    if (receivedMessage != (char*)"")
    {
        _messageReceivedCallback(receivedMessage);
    }
}

void SerialClient::transmitMessage(const char* message)
{
    static char transmissionMessage[64] = { SerialClient::_START_MESSAGE_DELIMITER };
    byte messageLength = strlen(message);

    transmissionMessage[0] = SerialClient::_START_MESSAGE_DELIMITER;
    transmissionMessage[1] = '\0';

    strcat(transmissionMessage, message);

    transmissionMessage[messageLength + 1] = SerialClient::_END_MESSAGE_DELIMITER;
    transmissionMessage[messageLength + 2] = '\0';

    _interface->print(transmissionMessage);
}

char* SerialClient::receiveMessage()
{
    static bool receivingMessage = false;
    static char receivedMessage[64];
    static byte messageIndex = 0;
    static char receivedCharacter;

    while (_interface->available() > 0)
    {
        receivedCharacter = _interface->read();

        if (receivingMessage)
        {
            if (receivedCharacter == SerialClient::_END_MESSAGE_DELIMITER)
            {
                receivingMessage = false;
                receivedMessage[messageIndex] = '\0';
                messageIndex = 0;

                return receivedMessage;
            }
            else
            {
                receivedMessage[messageIndex] = receivedCharacter;
                messageIndex += 1;
            }
        }
        else if (receivedCharacter == SerialClient::_START_MESSAGE_DELIMITER)
        {
            receivingMessage = true;
        }
    }

    return (char*)"";
}