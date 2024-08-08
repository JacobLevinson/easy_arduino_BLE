# easy_arduino_BLE
An extremely simple method of streaming Bluetooth Low Energy data from your Arduino to a PC.

I made this project because after many hours of issues and searching the Arch Wiki,
I found out that there is a bug in the linux kernel that conflicts with my specific Intel Wifi/Bluetooth Chip.
This bug does not allow for passive BLE scanning to work correctly, so the project I made actively just connects using
the BLE Address of the Arduino.

For this example here I have an Arduino Nano 33 IOT sending its IMU accelerometer data over BLE to a PC.

# Setup
1. Upload and run print_bleaddr to your arduino and note down the address printed out in the Serial monitor. You will need this.
2. Upload and run peripheral_BLE.ino to your arduino. Note you will need the ArduinoBLE Library installed.
3. Modify controller_BLE.py and replace the "address" variable's value with the address from step 1.
4.  **Before proceeding to step 5, make sure to install the `pygatt` library by running the following command:**
   pip install pygatt   
5. Run the controller_BLE.py python program on you PC.

The IMU accelerometer data should be printing to your terminal now!
