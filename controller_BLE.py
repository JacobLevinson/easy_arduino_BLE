import pygatt
import struct

ADDRESS = "78:21:84:AA:49:9E"  # Replace with the BLE MAC address of your target device

adapter = pygatt.GATTToolBackend()

try:
    adapter.start()

    device = adapter.connect(ADDRESS)

    # Replace with your desired characteristic UUIDs
    characteristic_uuids = ["2101", "2102", "2103"]

    while True:
        values = {}  # Store the values in a dictionary

        for uuid in characteristic_uuids:
            value = device.char_read(uuid)
            hex_string = value.hex()
            # Convert hex to float
            float_value = struct.unpack('f', bytes.fromhex(hex_string))[0]
            values[uuid] = float_value

        # Print the values for x, y, and z in three columns with consistent spacing
        x_str = f"x: {values['2101']:.2f}"
        y_str = f"y: {values['2102']:.2f}"
        z_str = f"z: {values['2103']:.2f}"
        print(f"{x_str:<20}{y_str:<20}{z_str}")

except KeyboardInterrupt:
    pass
finally:
    adapter.stop()
