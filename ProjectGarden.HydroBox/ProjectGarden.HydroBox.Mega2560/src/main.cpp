#include <Arduino.h>
#include <serial_client.h>
#include <shared_constants.h>

using namespace ProjectGarden::HydroBox::Shared;

/**
 * Serial client to communicate with ESP32.
 */
SerialClient* esp32Serial;

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

    esp32Serial = new SerialClient(&Serial3);
}

/**
 * Board main loop.
 */
void loop()
{
    Serial.println("Writing '{testing/data/serial_test:99910.05603}' to Serial 3.");
    Serial3.print("{testing/data/serial_test:99910.05603}");

    delay(15000);
}