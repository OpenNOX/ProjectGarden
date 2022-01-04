#ifndef PROJECT_GARDEN_HYDRO_BOX_ESP32_CONSTANTS_H
#define PROJECT_GARDEN_HYDRO_BOX_ESP32_CONSTANTS_H

#include <map.h>
#include <sensor_metadata.h>
#include <sensor_model.h>

using namespace ProjectGarden::HydroBox::Shared;

namespace ProjectGarden
{
namespace HydroBox
{
namespace Esp32
{
    /**
     * Map between sensor data pin and metadata.
     */
    const MapPair<byte, SensorMetadata> SENSOR_METADATA_MAP[] =
    {
        { HYDRO_BOX_ENVIRONMENT_DATA_PIN, { SensorModel::DHT22, "Hydro Box Environment", "data/hydro_box/" } },
        { AMBIENT_ENVIRONMENT_DATA_PIN, { SensorModel::DHT22, "Ambient Environment", "data/ambient/" } },
        { RESERVOIR_TEMPERATURE_DATA_PIN, { DS18B20, "Reservoir Temperature", "data/reservoir/" } },
        { RESERVOIR_FILL_FLOW_DATA_PIN, { FL608, "Reservoir Fill Flow", "data/reservoir/fill_" } },
    };
}
}
}

#endif