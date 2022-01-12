#include "base_sensor.h"
#include "limits.h"

using namespace ProjectGarden::HydroBox::Shared;

BaseSensor::BaseSensor(SensorMetadata sensorMetadata, unsigned long readFrequencyMs, byte dataMapCount)
    : sensorMetadata { sensorMetadata }, readFrequencyMs { readFrequencyMs } , dataMapCount { dataMapCount }
{
}

bool BaseSensor::isReadyToRead(unsigned long loopMsTimestamp)
{
    unsigned long sensorCheckDelta = loopMsTimestamp - lastReadMsTimestamp;

    if (sensorCheckDelta < 0)
    {
        sensorCheckDelta = (ULONG_MAX - lastReadMsTimestamp) + loopMsTimestamp;
    }

    if (readFrequencyMs <= sensorCheckDelta || lastReadMsTimestamp == 0)
    {
        return true;
    }

    return false;
}