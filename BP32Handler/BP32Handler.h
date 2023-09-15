#ifndef XINPUTWRK
#define XINPUTWRK

struct ControllerWork {
  uint8_t DPAD;
  uint16_t BUTTONS;
  int32_t L_X;
  int32_t L_Y;
  int32_t R_X;
  int32_t R_Y;
  int32_t L_BUMP;
  int32_t R_BUMP;
  uint16_t MISC;
};

enum {
  WRK_DPAD_UP = 1 << 0,
  WRK_DPAD_DOWN = 1 << 1,
  WRK_DPAD_RIGHT = 1 << 2,
  WRK_DPAD_LEFT = 1 << 3,
} DPAD;

enum {
  WRK_BUTTON_A = 1 << 0,
  WRK_BUTTON_B = 1 << 1,
  WRK_BUTTON_X = 1 << 2,
  WRK_BUTTON_Y = 1 << 3,
  WRK_BUTTON_SHOULDER_L = 1 << 4,
  WRK_BUTTON_SHOULDER_R = 1 << 5,
  WRK_BUTTON_TRIGGER_L = 1 << 6,
  WRK_BUTTON_TRIGGER_R = 1 << 7,
  WRK_BUTTON_THUMB_L = 1 << 8,
  WRK_BUTTON_THUMB_R = 1 << 9,
} BTN;

enum {
  WRK_MISC_BUTTON_SYSTEM = 1 << 0,
  WRK_MISC_BUTTON_BACK = 1 << 1,    
  WRK_MISC_BUTTON_HOME = 1 << 2,
} MISC;

#endif