# Edge Impulse Data Forwarder Example for Zephyr

This example streams sensors data over USB CDC (serial) in a format compatible with the Edge Impulse CLI tools (`edge-impulse-data-forwarder`).

## Features
- Streams data in the required serial protocol for Edge Impulse ingestion.
- Compatible with `edge-impulse-data-forwarder` and `edge-impulse-daemon`.
- No network or HTTP server required; all streaming is over USB serial.

## Usage
1. Config then build and flash the firmware to your device.
2. Connect your device via USB to your computer.
3. Run the Edge Impulse CLI:
   - `edge-impulse-data-forwarder`
   - The CLI will detect the serial stream and forward data to Edge Impulse Studio.

## Config
Key settings are:
- `SAMPLING_FREQUENCY_HZ` The required sampling frequency
- `SENSOR_CHAN_NUMBER` Numer of channels to be read from the sensor
- `SENSOR_CHAN_READ` Index of the [enum sensor_channel](https://docs.zephyrproject.org/latest/doxygen/html/group__sensor__interface.html#gaaa1b502bc029b10d7b23b0a25ef4e934)
- `SENSOR_NAME` The name of the sensor supported by Zephyr
- `SENSOR_ALIAS_NAME` Name of the alias

> [!NOTE]
> To set the sensor you want to use, you need to conifg one of the between `CONFIG_SENSOR_ALIAS_NAME` and `CONFIG_SENSOR_NAME`.
> You might need to set the peripherl needed to communicate with the sensor.

### Using a shield
If you are using a shield, rememebr to pass it using the --shield parameter ie
'west build -b <your board> --shield <shield name>

See [Shields](https://docs.zephyrproject.org/latest/hardware/porting/shields.html) for a list of the supported shields.

---

**Note:**
- This example is minimal and intended as a starting point for custom data forwarder applications on Zephyr.
