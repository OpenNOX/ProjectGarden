#ifndef PROJECT_GARDEN_HYDRO_BOX_SHARED_SERIAL_CLIENT_H
#define PROJECT_GARDEN_HYDRO_BOX_SHARED_SERIAL_CLIENT_H

#include <Arduino.h>
#include "map.h"

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Serial client used to manage serial communication between boards.
     */
    class SerialClient
    {
        public:
            /**
             * Initialize serial client.
             * @param hardwareSerial Pointer to Serial interface used to communicate.
             */
            SerialClient(HardwareSerial* hardwareSerial);

            /**
             * Transmit message across serial interface.
             * @param message Message to be transmitted.
             */
            void transmitMessage(const String& message);

            /**
             * Receive and decode message sent across serial interface.
             * @return Received message.
             */
            String receiveMessage();

            /**
             * Parse sensor data from serial message.
             * @param message Serial message.
             * @return Pointer to sensor data.
             */
            MapPair<String, float> parseSensorData(const String& serialMessage);

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
             * Message delimiter.
             */
            static const char _MESSAGE_DELIMITER = ':';

            /**
             * Pointer to hardware serial interface.
             */
            HardwareSerial* _interface;

            /**
             * Receiving message from serial interface.
             */
            bool _receivingMessage = false;

            /**
             * Received message from serial interface.
             */
            String _receivedMessage = "";
    };
}
}
}

#endif