#pragma once

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
     * Board sensor metadata used to initialize sensors.
     */
    const SensorMetadata SENSOR_METADATA[] =
    {
        { HYDRO_BOX_ENVIRONMENT_DATA_PIN, SensorModel::DHT22, "Hydro Box Environment", "sensor_data/hydro_box/" },
        { AMBIENT_ENVIRONMENT_DATA_PIN, SensorModel::DHT22, "Ambient Environment", "sensor_data/ambient/" },
        { RESERVOIR_TEMPERATURE_DATA_PIN, DS18B20, "Reservoir Temperature", "sensor_data/reservoir/" },
        { RESERVOIR_FILL_FLOW_DATA_PIN, FL608, "Reservoir Fill Flow", "sensor_data/reservoir/fill_" },
    };
}
}
}