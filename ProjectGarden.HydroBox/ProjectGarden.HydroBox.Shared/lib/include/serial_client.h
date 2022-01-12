#pragma once

#include <Arduino.h>
#include "sensor_data.h"

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Serial client used to manage serial communication.
     */
    class SerialClient
    {
        public:
            /**
             * Initialize serial client.
             * @param hardwareSerial Pointer to serial interface used to communicate.
             * @param messageReceivedCallback Pointer to callback function used as event handler
             * when a message is received.
             */
            SerialClient(
                HardwareSerial* hardwareSerial,
                void (*messageReceivedCallback)(char const* message));

            /**
             * Process received messages from across serial interface.
             */
            void loop();

            /**
             * Transmit message across serial interface.
             * @param message Message to be transmitted.
             */
            void transmitMessage(const char* message);

        private:
            /**
             * Start message delimiter.
             */
            static const char _START_MESSAGE_DELIMITER = '{';

            /**
             * End message delimiter.
             */
            static const char _END_MESSAGE_DELIMITER = '}';

            /**
             * Pointer to hardware serial interface.
             */
            HardwareSerial* _interface;

            /**
             * Pointer to callback function used as event handler when a message is received.
             * @param mqttTopic MQTT topic message received on.
             * @param message Message received.
             */
            void (*_messageReceivedCallback)(char const* message);

            /**
             * Receive message from across serial interface.
             * @return Received message.
             */
            char* receiveMessage();
    };
}
}
}