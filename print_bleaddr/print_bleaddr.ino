#include <ArduinoBLE.h>

void setup() {
  Serial.begin(9600);

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  String address = BLE.address();
  Serial.print("BLE MAC Address: ");
  Serial.println(address);
}

void loop() {
  // Your code here
}
