#include <XInput.h>
#include <Wire.h>
#include "TeensyXInput.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define I2C_ADDRESS 0x69
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ControllerWork *FRAME;
uint32_t CNTRLWRK_CNT = sizeof(ControllerWork);

void setup() {  
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  Wire.begin(I2C_ADDRESS);
	XInput.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  FRAME = (ControllerWork *)malloc(CNTRLWRK_CNT);
}

void loop() {
  // Parse frame data.
  memset(FRAME, 0, sizeof(ControllerWork));
  Wire.readBytes((unsigned char *)FRAME, sizeof(ControllerWork));

  // ABXY
  XInput.setButton(BUTTON_A, FRAME->BUTTONS & WRK_BUTTON_A);
  XInput.setButton(BUTTON_B, FRAME->BUTTONS & WRK_BUTTON_B);
  XInput.setButton(BUTTON_X, FRAME->BUTTONS & WRK_BUTTON_X);
  XInput.setButton(BUTTON_Y, FRAME->BUTTONS & WRK_BUTTON_Y);

  // L1 & R1
  XInput.setButton(BUTTON_LB, FRAME->BUTTONS & WRK_BUTTON_SHOULDER_L);
  XInput.setButton(BUTTON_RB, FRAME->BUTTONS & WRK_BUTTON_SHOULDER_R);

  // L2 & R2
  XInput.setButton(TRIGGER_LEFT, FRAME->BUTTONS & WRK_BUTTON_TRIGGER_L);
  XInput.setButton(TRIGGER_RIGHT, FRAME->BUTTONS & WRK_BUTTON_TRIGGER_R);
  
  // L3 & R3
  XInput.setButton(BUTTON_L3, FRAME->BUTTONS & WRK_BUTTON_THUMB_L);
  XInput.setButton(BUTTON_R3, FRAME->BUTTONS & WRK_BUTTON_THUMB_R);

  // Misc buttons.
  XInput.setButton(BUTTON_BACK, FRAME->MISC & WRK_MISC_BUTTON_BACK);
  XInput.setButton(BUTTON_LOGO, FRAME->MISC & WRK_MISC_BUTTON_SYSTEM);
  XInput.setButton(BUTTON_START, FRAME->MISC & WRK_MISC_BUTTON_HOME);

  // DPad
  XInput.setDpad(FRAME->DPAD & WRK_DPAD_UP, FRAME->DPAD & WRK_DPAD_DOWN, FRAME->DPAD & WRK_DPAD_LEFT, FRAME->DPAD & WRK_DPAD_RIGHT);

  // Joystick
  XInput.setJoystickRange(-508, 512);
  XInput.setJoystickX(JOY_LEFT, FRAME->L_X);
  XInput.setJoystickY(JOY_LEFT, -FRAME->L_Y);
  XInput.setJoystickX(JOY_RIGHT, FRAME->R_X);
  XInput.setJoystickY(JOY_RIGHT, -FRAME->R_Y);
}
