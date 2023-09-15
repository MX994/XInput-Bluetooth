#include <Wire.h>
#include <Bluepad32.h>
#include "BP32Handler.h"
#define I2C_PERPHERIAL_ADDRESS 0x69

ControllerPtr connected_controller;

void onConnect(ControllerPtr ctl);
void onDisconnect(ControllerPtr ctl);

void setup() {
  Serial.begin(9600);
  Wire.begin(5, 4, 400000L);
  
  Serial.println("Setting up 360 Controller Dongle...");

  String fv = BP32.firmwareVersion();
  Serial.print("Bluepad32 firmware version is ");
  Serial.println(fv);

  // To get the BD Address (MAC address) call:
  const uint8_t* addr = BP32.localBdAddress();
  Serial.print("BD Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(addr[i], HEX);
    if (i < 5)
      Serial.print(":");
    else
      Serial.println();
  }

  BP32.setup(&onConnect, &onDisconnect);
  BP32.forgetBluetoothKeys();
  BP32.enableNewBluetoothConnections(true);
}

void onConnect(ControllerPtr ctl) {
  if (connected_controller == nullptr) {
    connected_controller = ctl;
    ControllerProperties properties = ctl->getProperties();
    char buf[80];
    sprintf(buf, "BTAddr: %02x:%02x:%02x:%02x:%02x:%02x, VID/PID: %04x:%04x, flags: 0x%02x", properties.btaddr[0], properties.btaddr[1], properties.btaddr[2], properties.btaddr[3], properties.btaddr[4], properties.btaddr[5], properties.vendor_id, properties.product_id, properties.flags);
    Serial.println(buf);
  } else {
    Serial.println("Controller already connected; discarding.");
  }
}

void onDisconnect(ControllerPtr ctl) {
  connected_controller = nullptr; 
}

void HandleGamepad(ControllerPtr gamepad) {
  ControllerWork WRK = {
    .DPAD = gamepad->dpad(),
    .BUTTONS = gamepad->buttons(),
    .L_X = gamepad->axisX(),
    .L_Y = gamepad->axisY(),
    .R_X = gamepad->axisRX(),
    .R_Y = gamepad->axisRY(),
    .L_BUMP = gamepad->brake(),
    .R_BUMP = gamepad->throttle(),
    .MISC = gamepad->miscButtons(),
  };
  Wire.beginTransmission(I2C_PERPHERIAL_ADDRESS);
  Wire.write((unsigned char *)&WRK, sizeof(ControllerWork));
  Wire.endTransmission();
}

void loop() {
  BP32.update();
  if (connected_controller) {
    HandleGamepad(connected_controller);
  }
}