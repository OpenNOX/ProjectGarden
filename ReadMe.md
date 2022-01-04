# Project Garden

## Pre-Build ProjectGarden.HydroBox.Esp32 Steps

1. Rename `ProjectGarden.HydroBox.Esp32/include/secrets.example.h` to be `ProjectGarden.HydroBox.Esp32/include/secrets.h`, and update the file to have appropriate values.
1. Update `ProjectGarden.HydroBox.Esp32/platformio.ini` to have appropriate values under the `build_flags` section.

## To Dos

1. Fix how `ProjectGarden::HydroBox::Esp32::Sensors::PulseCountSensor` gets constructed so that it does not require a static counter variable and function.