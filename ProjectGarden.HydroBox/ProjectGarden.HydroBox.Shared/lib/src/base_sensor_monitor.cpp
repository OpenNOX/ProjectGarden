#include "base_sensor_monitor.h"
#include "limits.h"

using namespace ProjectGarden::HydroBox::Shared;

Stack<BaseSensor*> BaseSensorMonitor::getReadySensors(unsigned long loopMsTimestamp)
{
    Stack<BaseSensor*> readySensors;

    for (BaseSensor* sensor : this->_sensors)
    {
        unsigned long sensorCheckDelta = loopMsTimestamp - sensor->lastReadMsTimestamp;

        if (sensorCheckDelta < 0)
        {
            sensorCheckDelta = (ULONG_MAX - sensor->lastReadMsTimestamp) + loopMsTimestamp;
        }

        if (sensor->readFrequencyMs <= sensorCheckDelta)
        {
            readySensors.insert(sensor);
        }
    }

    return readySensors;
}