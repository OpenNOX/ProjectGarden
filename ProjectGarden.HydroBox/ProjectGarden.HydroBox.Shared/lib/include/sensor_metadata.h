#ifndef PROJECT_GARDEN_HYDRO_BOX_SHARED_SENSOR_METADATA_H
#define PROJECT_GARDEN_HYDRO_BOX_SHARED_SENSOR_METADATA_H

#include <Arduino.h>
#include "sensor_model.h"

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Sensor metadata.
     */
    struct SensorMetadata
    {
        /**
         * Sensor model.
         */
        SensorModel sensorModel;

        /**
         * Sensor description.
         */
        String description;

        /**
         * MQTT topic base.
         */
        String mqttTopicBase;
    };
}
}
}

#endif