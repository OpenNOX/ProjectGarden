#pragma once

#include <sensor_metadata.h>
#include <sensor_model.h>

using namespace ProjectGarden::HydroBox::Shared;

namespace ProjectGarden
{
namespace HydroBox
{
namespace Mega2560
{
    /**
     * Board sensor metadata used to initialize sensors.
     */
    const SensorMetadata SENSOR_METADATA[] =
    {
        { HYDRO_BOX_ENVIRONMENT_DATA_PIN, SensorModel::DHT22, "Hydro Box Environment", "sensor_data/hydro_box/" },
        { LEAK_DETECTION_REAR_DATA_PIN, LM393, "Rear-Left Leak Detection", "sensor_data/leak_detection/rear_leak_detected" },
        { LEAK_DETECTION_CENTER_DATA_PIN, LM393, "Center Leak Detection", "sensor_data/leak_detection/center_leak_detected" },
        { LEAK_DETECTION_ELBOW_DATA_PIN, LM393, "Under Elbow Leak Detection", "sensor_data/leak_detection/elbow_leak_detected" },
        { LEAK_DETECTION_PUMP_DATA_PIN, LM393, "Pump Leak Detection", "sensor_data/leak_detection/pump_leak_detected" },
    };
}
}
}