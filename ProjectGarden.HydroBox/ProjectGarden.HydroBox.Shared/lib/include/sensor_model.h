#ifndef PROJECT_GARDEN_HYDRO_BOX_SHARED_SENSOR_MODEL_H
#define PROJECT_GARDEN_HYDRO_BOX_SHARED_SENSOR_MODEL_H

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Sensor model.
     */
    enum SensorModel
    {
        /**
         * Humidity and temperature sensor.
         */
        DHT22,

        /**
         * Waterproof temperature sensor.
         */
        DS18B20,

        /**
         * Water flow sensor.
         */
        FL608,
    };
}
}
}

#endif