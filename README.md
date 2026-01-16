# Edge Impulse Data Forwarder Example for Zephyr

This example streams sensor or camera data over USB CDC (serial) in a format compatible with the Edge Impulse CLI tools (`edge-impulse-data-forwarder`).

## Features
- Streams data in the required serial protocol for Edge Impulse ingestion.
- Compatible with `edge-impulse-data-forwarder` and `edge-impulse-daemon`.
- No network or HTTP server required; all streaming is over USB serial.

## Usage
1. Build and flash the firmware to your device.
2. Connect your device via USB to your computer.
3. Run the Edge Impulse CLI:
   - `edge-impulse-data-forwarder` or `edge-impulse-daemon`
   - The CLI will detect the serial stream and forward data to Edge Impulse Studio.

## Implementation Notes
- The firmware sends data as base64-encoded or raw binary, with framing and metadata compatible with Edge Impulse CLI.
- See the [Edge Impulse documentation](https://docs.edgeimpulse.com/docs/edge-impulse-cli/cli-data-forwarder) for protocol details.

---

**Note:**
- This example is minimal and intended as a starting point for custom data forwarder applications on Zephyr.
