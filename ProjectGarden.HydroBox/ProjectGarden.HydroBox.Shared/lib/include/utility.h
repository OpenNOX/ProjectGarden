#pragma once

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Common serial baud rate.
     */
    #define SERIAL_BAUD_RATE 115200

    /**
     * Concatenate two strings and return a new string.
     * @param string1 Front of string in concatenated string.
     * @param string2 Back of string in concatenated string.
     * @return Two strings concatenated.
     */
    char* concat(const char* string1, const char* string2);
}
}
}