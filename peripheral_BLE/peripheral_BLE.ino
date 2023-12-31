#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

#define BLE_UUID_ACCELEROMETER_SERVICE "1101"
#define BLE_UUID_ACCELEROMETER_X "2101"
#define BLE_UUID_ACCELEROMETER_Y "2102"
#define BLE_UUID_ACCELEROMETER_Z "2103"

#define BLE_DEVICE_NAME "Arduino"
#define BLE_LOCAL_NAME "Arduino"

BLEService accelerometerService(BLE_UUID_ACCELEROMETER_SERVICE);

BLEFloatCharacteristic accelerometerCharacteristicX(BLE_UUID_ACCELEROMETER_X, BLERead | BLENotify);
BLEFloatCharacteristic accelerometerCharacteristicY(BLE_UUID_ACCELEROMETER_Y, BLERead | BLENotify);
BLEFloatCharacteristic accelerometerCharacteristicZ(BLE_UUID_ACCELEROMETER_Z, BLERead | BLENotify);

float x, y, z;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  // initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");

  // initialize BLE
  if (!BLE.begin()) {
    Serial.println("Starting Bluetooth® Low Energy module failed!");
    while (1)
      ;
  }

  // set advertised local name and service UUID
  //
  BLE.setLocalName(BLE_LOCAL_NAME);
  BLE.setAdvertisedService(accelerometerService);
  //

  // add characteristics and service
  //
  accelerometerService.addCharacteristic(accelerometerCharacteristicX);
  accelerometerService.addCharacteristic(accelerometerCharacteristicY);
  accelerometerService.addCharacteristic(accelerometerCharacteristicZ);

  // Add the service to the BLE stack
  BLE.addService(accelerometerService);
  //

  // start advertising
  //
  BLE.advertise();
  //

  Serial.println("BLE Accelerometer Peripheral");
}

void loop() {
  Serial.println("Starting Loop");
  BLEDevice central = BLE.central();
  float x, y, z;
  if (central) {
    // A central device (your Linux PC) has connected.
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    while (central.connected()) {
      // Read accelerometer data
      if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(x, y, z);

        // Update Bluetooth characteristics with accelerometer data
        accelerometerCharacteristicX.writeValue(x);
        accelerometerCharacteristicY.writeValue(y);
        accelerometerCharacteristicZ.writeValue(z);
      }
    }
    BLE.advertise();

  }
}
