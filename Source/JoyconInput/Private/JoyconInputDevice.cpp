#include "JoyconInputDevice.h"

DEFINE_LOG_CATEGORY_STATIC(LogJoyconInputDevice, Log, All);

#define LOCTEXT_NAMESPACE "JoyconInputDevice"

#define BLUETOOTH 0
#define GAME_BUTTON 1
#define SECONDARY_BUTTON 2
#define THUMBSTICK 3

#define BLUETOOTH_BUTTON 0x3F

#define LEFT_JOYCON_SL 0x10
#define LEFT_JOYCON_SR 0x20
#define LEFT_JOYCON_DPAD_UP 0x08
#define LEFT_JOYCON_DPAD_RIGHT 0x02
#define LEFT_JOYCON_DPAD_DOWN 0x01
#define LEFT_JOYCON_DPAD_LEFT 0x04 
#define LEFT_JOYCON_ZL 0x80
#define LEFT_JOYCON_L 0x40
#define LEFT_JOYCON_MINUS 0x01
#define LEFT_JOYCON_THUMB_IN 0x04
#define LEFT_JOYCON_CAPTURE 0x20
#define LEFT_JOYCON_AXIS_UP 0x00
#define LEFT_JOYCON_AXIS_RIGHT 0x02
#define LEFT_JOYCON_AXIS_DOWN 0x04
#define LEFT_JOYCON_AXIS_LEFT 0x06

const FKey FLeftJoyconButton::ShoulderLeft("LeftJoycon_ShoulderLeft");
const FKey FLeftJoyconButton::ShoulderRight("LeftJoycon_ShoulderRight");
const FKey FLeftJoyconButton::Up("LeftJoycon_Up");
const FKey FLeftJoyconButton::Left("LeftJoycon_Left");
const FKey FLeftJoyconButton::Down("LeftJoycon_Down");
const FKey FLeftJoyconButton::Right("LeftJoycon_Right");
const FKey FLeftJoyconButton::Bumper("LeftJoycon_Bumper");
const FKey FLeftJoyconButton::Trigger("LeftJoycon_Trigger");
const FKey FLeftJoyconButton::Minus("LeftJoycon_Minus");
