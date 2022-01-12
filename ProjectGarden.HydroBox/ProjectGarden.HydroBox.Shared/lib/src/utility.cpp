#include <Arduino.h>
#include "utility.h"

char* ProjectGarden::HydroBox::Shared::concat(const char* string1, const char* string2)
{
    byte bufferSize = strlen(string1) + strlen(string2) + 1;
    char* buffer = new char[bufferSize];

    strcpy(buffer, string1);
    strcat(buffer, string2);

    buffer[bufferSize - 1] = '\0';

    return buffer;
}