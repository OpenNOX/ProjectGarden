#pragma once

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

        /**
         * Leak detection sensor.
         */
        LM393,
    };
}
}
}