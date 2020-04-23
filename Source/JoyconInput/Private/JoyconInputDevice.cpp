#include "JoyconInputDevice.h"

DEFINE_LOG_CATEGORY_STATIC(LogJoyconInputDevice, Log, All);

#define LOCTEXT_NAMESPACE "JoyconInputDevice"

#define DEBUG true

// Magic Numbers & Button IDs
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

#define RIGHT_JOYCON_SL 0
#define RIGHT_JOYCON_SR 0
#define RIGHT_JOYCON_UP 0
#define RIGHT_JOYCON_RIGHT 0
#define RIGHT_JOYCON_DOWN 0
#define RIGHT_JOYCON_LEFT 0
#define RIGHT_JOYCON_ZR 0
#define RIGHT_JOYCON_R 0
#define RIGHT_JOYCON_PLUS 0
#define RIGHT_JOYCON_THUMB_IN 0
#define RIGHT_JOYCON_HOME 0
#define RIGHT_JOYCON_AXIS_UP 0
#define RIGHT_JOYCON_AXIS_RIGHT 0
#define RIGHT_JOYCON_AXIS_DOWN 0
#define RIGHT_JOYCON_AXIS_LEFT 0

#define COMBINED_UP 0
#define COMBINED_RIGHT 0
#define COMBINED_DOWN 0
#define COMBINED_LEFT 0
#define COMBINED_X 0
#define COMBINED_A 0
#define COMBINED_B 0
#define COMBINED_Y 0
#define COMBINED_AXIS_UP 0
#define COMBINED_AXIS_RIGHT 0
#define COMBINED_AXIS_DOWN 0
#define COMBINED_AXIS_LEFT 0

#define PRO_L 0
#define PRO_ZL 0
#define PRO_R 0
#define PRO_ZR 0
#define PRO_UP 0
#define PRO_RIGHT 0
#define PRO_DOWN 0
#define PRO_LEFT 0
#define PRO_X 0
#define PRO_A 0
#define PRO_B 0
#define PRO_Y 0
#define PRO_MINUS 0
#define PRO_PLUS 0
#define PRO_CAPTURE 0
#define PRO_HOME 0
#define PRO_LEFT_THUMB_IN 0
#define PRO_RIGHT_THUMB_IN 0
#define PRO_LEFT_AXIS_UP 0
#define PRO_LEFT_AXIS_RIGHT 0
#define PRO_LEFT_AXIS_DOWN 0
#define PRO_LEFT_AXIS_LEFT 0
#define PRO_RIGHT_AXIS_UP 0
#define PRO_RIGHT_AXIS_RIGHT 0
#define PRO_RIGHT_AXIS_DOWN 0
#define PRO_RIGHT_AXIS_LEFT 0

// Button Names
const FKey FLeftJoyconButton::ShoulderLeft("LeftJoycon_ShoulderLeft");
const FKey FLeftJoyconButton::ShoulderRight("LeftJoycon_ShoulderRight");
const FKey FLeftJoyconButton::Up("LeftJoycon_Up");
const FKey FLeftJoyconButton::Right("LeftJoycon_Right");
const FKey FLeftJoyconButton::Down("LeftJoycon_Down");
const FKey FLeftJoyconButton::Left("LeftJoycon_Left");
const FKey FLeftJoyconButton::Bumper("LeftJoycon_Bumper");
const FKey FLeftJoyconButton::Trigger("LeftJoycon_Trigger");
const FKey FLeftJoyconButton::Minus("LeftJoycon_Minus");
const FKey FLeftJoyconButton::ThumbstickIn("LeftJoycon_ThumbstickIn");
const FKey FLeftJoyconButton::Capture("LeftJoycon_Capture");
const FKey FLeftJoyconButton::ThumbstickAxisUp("LeftJoycon_ThumbstickUp");
const FKey FLeftJoyconButton::ThumbstickAxisRight("LeftJoycon_ThumbstickRight");
const FKey FLeftJoyconButton::ThumbstickAxisDown("LeftJoycon_ThumbstickDown");
const FKey FLeftJoyconButton::ThumbstickAxisLeft("LeftJoycon_ThumbstickLeft");
const FKey FLeftJoyconButton::ThumbstickAxisY("LeftJoycon_AxisY");
const FKey FLeftJoyconButton::ThumbstickAxisX("LeftJoycon_AxisX");

const FKey FRightJoyconButton::ShoulderLeft("RightJoycon_ShoulderLeft");
const FKey FRightJoyconButton::ShoulderRight("RightJoycon_ShoulderRight");
const FKey FRightJoyconButton::Up("RightJoycon_Up");
const FKey FRightJoyconButton::Right("RightJoycon_Right");
const FKey FRightJoyconButton::Down("RightJoycon_Down");
const FKey FRightJoyconButton::Left("RightJoycon_Left");
const FKey FRightJoyconButton::Bumper("RightJoycon_Bumper");
const FKey FRightJoyconButton::Trigger("RightJoycon_Trigger");
const FKey FRightJoyconButton::Plus("RightJoycon_Plus");
const FKey FRightJoyconButton::ThumbstickIn("RightJoycon_ThumbstickIn");
const FKey FRightJoyconButton::Home("RightJoycon_Capture");
const FKey FRightJoyconButton::ThumbstickAxisUp("RightJoycon_ThumbstickUp");
const FKey FRightJoyconButton::ThumbstickAxisRight("RightJoycon_ThumbstickRight");
const FKey FRightJoyconButton::ThumbstickAxisDown("RightJoycon_ThumbstickDown");
const FKey FRightJoyconButton::ThumbstickAxisLeft("RightJoycon_ThumbstickLeft");
const FKey FRightJoyconButton::ThumbstickAxisY("RightJoycon_AxisY");
const FKey FRightJoyconButton::ThumbstickAxisX("RightJoycon_AxisX");

const FKey FJoyconButton::LeftJoycon_ShoulderLeft("Combined_Left_ShoulderLeft");
const FKey FJoyconButton::LeftJoycon_ShoulderRight("Combined_Left_ShoulderRight");
const FKey FJoyconButton::RightJoycon_ShoulderLeft("Combined_Right_ShoulderLeft");
const FKey FJoyconButton::RightJoycon_ShoulderRight("Combined_Right_ShoulderRight");
const FKey FJoyconButton::L("Combined_L");
const FKey FJoyconButton::ZL("Combined_ZL");
const FKey FJoyconButton::R("Combined_R");
const FKey FJoyconButton::ZR("Combined_ZR");
const FKey FJoyconButton::Up("Combined_Up");
const FKey FJoyconButton::Right("Combined_Right");
const FKey FJoyconButton::Down("Combined_Down");
const FKey FJoyconButton::Left("Combined_Left");
const FKey FJoyconButton::X("Combined_X");
const FKey FJoyconButton::A("Combined_A");
const FKey FJoyconButton::B("Combined_B");
const FKey FJoyconButton::Y("Combined_Y");
const FKey FJoyconButton::Minus("Combined_Minus");
const FKey FJoyconButton::Plus("Combined_Plus");
const FKey FJoyconButton::Capture("Combined_Capture");
const FKey FJoyconButton::Home("Combined_Home");
const FKey FJoyconButton::LeftThumbstickIn("Combined_LeftThumbstickIn");
const FKey FJoyconButton::RightThumbstickIn("Combined_RightThumbstickIn");
const FKey FJoyconButton::LeftThumbstickUp("Combined_LeftThumbstickUp");
const FKey FJoyconButton::LeftThumbstickRight("Combined_LeftThumbstickRight");
const FKey FJoyconButton::LeftThumbstickDown("Combined_LeftThumbstickDown");
const FKey FJoyconButton::LeftThumbstickLeft("Combined_LeftThumbstickLeft");
const FKey FJoyconButton::RightThumbstickUp("Combined_RightThumbstickUp");
const FKey FJoyconButton::RightThumbstickRight("Combined_RightThumbstickRight");
const FKey FJoyconButton::RightThumbstickDown("Combined_RightThumbstickDown");
const FKey FJoyconButton::RightThumbstickLeft("Combined_RightThumbstickLeft");
const FKey FJoyconButton::LeftThumbstickAxisY("Combined_LeftThumbstickAxisY");
const FKey FJoyconButton::LeftThumbstickAxisX("Combined_LeftThumbstickAxiX");
const FKey FJoyconButton::RightThumbstickAxisY("Combined_RightThumbstickAxisY");
const FKey FJoyconButton::RightThumbstickAxisX("Combined_RightThumbstickAxisX");

const FKey FProControllerButton::L("Pro_L");
const FKey FProControllerButton::ZL("Pro_ZL");
const FKey FProControllerButton::R("Pro_R");
const FKey FProControllerButton::ZR("Pro_ZR");
const FKey FProControllerButton::Up("Pro_Up");
const FKey FProControllerButton::Right("Pro_Right");
const FKey FProControllerButton::Down("Pro_Down");
const FKey FProControllerButton::Left("Pro_Left");
const FKey FProControllerButton::X("Pro_X");
const FKey FProControllerButton::A("Pro_A");
const FKey FProControllerButton::B("Pro_B");
const FKey FProControllerButton::Y("Pro_Y");
const FKey FProControllerButton::Minus("Pro_Minus");
const FKey FProControllerButton::Plus("Pro_Plus");
const FKey FProControllerButton::Capture("Pro_Capture");
const FKey FProControllerButton::Home("Pro_Home");
const FKey FProControllerButton::LeftThumbstickIn("Pro_LeftThumbstickIn");
const FKey FProControllerButton::RightThumbstickIn("Pro_RightThumbstickIn");
const FKey FProControllerButton::LeftThumbstickUp("Pro_LeftThumbstickUp");
const FKey FProControllerButton::LeftThumbstickRight("Pro_LeftThumbstickRight");
const FKey FProControllerButton::LeftThumbstickDown("Pro_LeftThumbstickDown");
const FKey FProControllerButton::LeftThumbstickLeft("Pro_LeftThumbstickLeft");
const FKey FProControllerButton::RightThumbstickUp("Pro_RightThumbstickUp");
const FKey FProControllerButton::RightThumbstickRight("Pro_RightThumbstickRight");
const FKey FProControllerButton::RightThumbstickDown("Pro_RightThumbstickDown");
const FKey FProControllerButton::RightThumbstickLeft("Pro_RightThumbstickLeft");
const FKey FProControllerButton::LeftThumbstickAxisY("Pro_LeftThumbstickAxisY");
const FKey FProControllerButton::LeftThumbstickAxisX("Pro_LeftThumbstickAxiX");
const FKey FProControllerButton::RightThumbstickAxisY("Pro_RightThumbstickAxisY");
const FKey FProControllerButton::RightThumbstickAxisX("Pro_RightThumbstickAxisX");

FJoyconInputDevice::FJoyconInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) : MessageHandler(InMessageHandler)
{
	const FName NAME_LeftJoycon(TEXT("LeftJoycon"));
	const FName NAME_RightJoycon(TEXT("RightJoycon"));
	const FName NAME_Combined(TEXT("Combined"));
	const FName NAME_Pro(TEXT("Pro"));

#ifdef DEBUG
	UE_LOG(LogJoyconInputDevice, Log, TEXT("Creating Inputs..."));
#endif

	// Add input menu categories.
	EKeys::AddMenuCategoryDisplayInfo(NAME_LeftJoycon, LOCTEXT("LeftJoyconSubcategory", "Left Joycon"), TEXT("GraphEditor.PadEvent_16x"));
	EKeys::AddMenuCategoryDisplayInfo(NAME_RightJoycon, LOCTEXT("RightJoyconSubcategory", "Right Joycon"), TEXT("GraphEditor.PadEvent_16x"));
	EKeys::AddMenuCategoryDisplayInfo(NAME_Combined, LOCTEXT("CombinedJoyconSubcategory", "Combined Joycons"), TEXT("GraphEditor.PadEvent_16x"));
	EKeys::AddMenuCategoryDisplayInfo(NAME_Pro, LOCTEXT("ProControllerSubcategory", "Pro Controller"), TEXT("GraphEditor.PadEvent_16x"));

	// Add keys.
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ShoulderLeft, LOCTEXT("LeftJoycon_ShoulderLeft", "Left Joycon - Shoulder Left"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ShoulderRight, LOCTEXT("LeftJoycon_ShoulderRight", "Left Joycon - Shoulder Right"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Up, LOCTEXT("LeftJoycon_Up", "Left Joycon - Up"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Right, LOCTEXT("LeftJoycon_Right", "Left Joycon - Right"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Down, LOCTEXT("LeftJoycon_Down", "Left Joycon - Down"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Left, LOCTEXT("LeftJoycon_Left", "Left Joycon - Left"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Bumper, LOCTEXT("LeftJoycon_Bumper", "Left Joycon - Bumper"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Trigger, LOCTEXT("LeftJoycon_Trigger", "Left Joycon - Trigger"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Minus, LOCTEXT("LeftJoycon_Minus", "Left Joycon - Minus"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickIn, LOCTEXT("LeftJoycon_ThumbstickIn", "Left Joycon - Thumbstick In"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Capture, LOCTEXT("LeftJoycon_Capture", "Left Joycon - Capture"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisUp, LOCTEXT("LeftJoycon_ThumbstickUp", "Left Joycon - Thumbstick Up"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisRight, LOCTEXT("LeftJoycon_ThumbstickRight", "Left Joycon - Thumbstick Right"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisDown, LOCTEXT("LeftJoycon_ThumbstickDown", "Left Joycon - Thumbstick Down"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisLeft, LOCTEXT("LeftJoycon_ThumbstickLeft", "Left Joycon - Thumbstick Left"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisY, LOCTEXT("LeftJoycon_AxisY", "Left Joycon - Thumbstick Up"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisX, LOCTEXT("LeftJoycon_AxisX", "Left Joycon - Thumbstick Up"), FKeyDetails::GamepadKey, NAME_LeftJoycon));

	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ShoulderLeft, LOCTEXT("RightJoycon_ShoulderLeft", "Right Joycon - Shoulder Left"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ShoulderRight, LOCTEXT("RightJoycon_ShoulderRight", "Right Joycon - Shoulder Right"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Up, LOCTEXT("RightJoycon_Up", "Right Joycon - Up"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Right, LOCTEXT("RightJoycon_Right", "Right Joycon - Right"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Down, LOCTEXT("RightJoycon_Down", "Right Joycon - Down"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Left, LOCTEXT("RightJoycon_Left", "Right Joycon - Left"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Bumper, LOCTEXT("RightJoycon_Bumper", "Right Joycon - Bumper"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Trigger, LOCTEXT("RightJoycon_Trigger", "Right Joycon - Trigger"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Plus, LOCTEXT("RightJoycon_Plus", "Right Joycon - Minus"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickIn, LOCTEXT("RightJoycon_ThumbstickIn", "Right Joycon - Thumbstick In"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Home, LOCTEXT("RightJoycon_Home", "Right Joycon - Capture"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisUp, LOCTEXT("RightJoycon_ThumbstickUp", "Right Joycon - Thumbstick Up"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisRight, LOCTEXT("RightJoycon_ThumbstickRight", "Right Joycon - Thumbstick Right"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisDown, LOCTEXT("RightJoycon_ThumbstickDown", "Right Joycon - Thumbstick Down"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisLeft, LOCTEXT("RightJoycon_ThumbstickLeft", "Right Joycon - Thumbstick Left"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisY, LOCTEXT("RightJoycon_AxisY", "Right Joycon - Thumbstick Up"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisX, LOCTEXT("RightJoycon_AxisX", "Right Joycon - Thumbstick Up"), FKeyDetails::GamepadKey, NAME_RightJoycon));

	EKeys::AddKey(FKeyDetails(FJoyconButton::LeftJoycon_ShoulderLeft, LOCTEXT("Combined_Left_ShoulderLeft", "Combined Joycons - Left Joycon - Shoulder Left"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::LeftJoycon_ShoulderRight, LOCTEXT("Combined_Left_ShoulderRight", "Combined Joycons - Left Joycon - Shoulder Right"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::RightJoycon_ShoulderLeft, LOCTEXT("Combined_Right_ShoulderLeft", "Combined Joycons - Right Joycon - Shoulder Left"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::RightJoycon_ShoulderRight, LOCTEXT("Combined_Right_ShoulderRight", "Combined Joycons - Right Joycon - Shoulder Right"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::L, LOCTEXT("Combined_L", "Combined Joycons - L"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::ZL, LOCTEXT("Combined_ZL", "Combined Joycons - ZL"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::R, LOCTEXT("Combined_R", "Combined Joycons - R"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::ZR, LOCTEXT("Combined_ZR", "Combined Joycons - ZR"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::Up, LOCTEXT("Combined_Up", "Combined Joycons - D-Pad Up"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::Right, LOCTEXT("Combined_Right", "Combined Joycons - D-Pad Right"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::Down, LOCTEXT("Combined_Down", "Combined Joycons - D-Pad Down"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::Left, LOCTEXT("Combined_Left", "Combined Joycons - D-Pad Left"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::X, LOCTEXT("Combined_X", "Combined Joycons - X"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::A, LOCTEXT("Combined_A", "Combined Joycons - A"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::B, LOCTEXT("Combined_B", "Combined Joycons - B"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::Y, LOCTEXT("Combined_Y", "Combined Joycons - Y"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::Minus, LOCTEXT("Combined_Minus", "Combined Joycons - Minus"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::Plus, LOCTEXT("Combined_Plus", "Combined Joycons - Plus"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::Capture, LOCTEXT("Combined_Capture", "Combined Joycons - Capture"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::Home, LOCTEXT("Combined_Home", "Combined Joycons - Home"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::LeftThumbstickIn, LOCTEXT("Combined_LeftThumbstickIn", "Combined Joycons - Left Thumbstick In"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::RightThumbstickIn, LOCTEXT("Combined_RightThumbstickIn", "Combined Joycons - Right Thumbstick In"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::LeftThumbstickUp, LOCTEXT("Combined_LeftThumbstickUp", "Combined Joycons - Left Thumbstick Up"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::LeftThumbstickRight, LOCTEXT("Combined_LeftThumbstickRight", "Combined Joycons - Left Thumbstick Right"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::LeftThumbstickDown, LOCTEXT("Combined_LeftThumbstickDown", "Combined Joycons - Left Thumbstick Down"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::LeftThumbstickLeft, LOCTEXT("Combined_LeftThumbstickLeft", "Combined Joycons - Left Thumbstick Left"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::RightThumbstickUp, LOCTEXT("Combined_RightThumbstickUp", "Combined Joycons - Right Thumbstick Up"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::RightThumbstickRight, LOCTEXT("Combined_RightThumbstickRight", "Combined Joycons - Right Thumbstick Right"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::RightThumbstickDown, LOCTEXT("Combined_RightThumbstickDown", "Combined Joycons - Right Thumbstick Down"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::RightThumbstickLeft, LOCTEXT("Combined_RightThumbstickLeft", "Combined Joycons - Right Thumbstick Left"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::LeftThumbstickAxisY, LOCTEXT("Combined_LeftThumbstickAxisY", "Combined Joycons - Left Thumbstick Axis Y"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::LeftThumbstickAxisX, LOCTEXT("Combined_LeftThumbstickAxisX", "Combined Joycons - Left Thumbstick Axis X"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::RightThumbstickAxisY, LOCTEXT("Combined_RightThumbstickAxisY", "Combined Joycons - Right Thumbstick Axis Y"), FKeyDetails::GamepadKey, NAME_Combined));
	EKeys::AddKey(FKeyDetails(FJoyconButton::RightThumbstickAxisX, LOCTEXT("Combined_RightThumbstickAxisX", "Combined Joycons - Right Thumbstick Axis X"), FKeyDetails::GamepadKey, NAME_Combined));

	EKeys::AddKey(FKeyDetails(FProControllerButton::L, LOCTEXT("ProController_L", "Pro Controller - L"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::ZL, LOCTEXT("ProController_ZL", "Pro Controller - ZL"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::R, LOCTEXT("ProController_R", "Pro Controller - R"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::ZR, LOCTEXT("ProController_ZR", "Pro Controller - ZR"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::Up, LOCTEXT("ProController_Up", "Pro Controller - D-Pad Up"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::Right, LOCTEXT("ProController_Right", "Pro Controller - D-Pad Right"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::Down, LOCTEXT("ProController_Down", "Pro Controller - D-Pad Down"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::Left, LOCTEXT("ProController_Left", "Pro Controller - D-Pad Left"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::X, LOCTEXT("ProController_X", "Pro Controller - X"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::A, LOCTEXT("ProController_A", "Pro Controller - A"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::B, LOCTEXT("ProController_B", "Pro Controller - B"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::Y, LOCTEXT("ProController_Y", "Pro Controller - Y"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::Minus, LOCTEXT("ProController_Minus", "Pro Controller - Minus"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::Plus, LOCTEXT("ProController_Plus", "Pro Controller - Plus"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::Capture, LOCTEXT("ProController_Capture", "Pro Controller - Capture"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::Home, LOCTEXT("ProController_Home", "Pro Controller - Home"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::LeftThumbstickIn, LOCTEXT("ProController_LeftThumbstickIn", "Pro Controller - Left Thumbstick In"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::RightThumbstickIn, LOCTEXT("ProController_RightThumbstickIn", "Pro Controller - Right Thumbstick In"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::LeftThumbstickUp, LOCTEXT("ProController_LeftThumbstickUp", "Pro Controller - Left Thumbstick Up"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::LeftThumbstickRight, LOCTEXT("ProController_LeftThumbstickRight", "Pro Controller - Left Thumbstick Right"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::LeftThumbstickDown, LOCTEXT("ProController_LeftThumbstickDown", "Pro Controller - Left Thumbstick Down"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::LeftThumbstickLeft, LOCTEXT("ProController_LeftThumbstickLeft", "Pro Controller - Left Thumbstick Left"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::RightThumbstickUp, LOCTEXT("ProController_RightThumbstickUp", "Pro Controller - Right Thumbstick Up"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::RightThumbstickRight, LOCTEXT("ProController_RightThumbstickRight", "Pro Controller - Right Thumbstick Right"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::RightThumbstickDown, LOCTEXT("ProController_RightThumbstickDown", "Pro Controller - Right Thumbstick Down"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::RightThumbstickLeft, LOCTEXT("ProController_RightThumbstickLeft", "Pro Controller - Right Thumbstick Left"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::LeftThumbstickAxisY, LOCTEXT("ProController_LeftThumbstickAxisY", "Pro Controller - Left Thumbstick Axis Y"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::LeftThumbstickAxisX, LOCTEXT("ProController_LeftThumbstickAxisX", "Pro Controller - Left Thumbstick Axis X"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::RightThumbstickAxisY, LOCTEXT("ProController_RightThumbstickAxisY", "Pro Controller - Right Thumbstick Axis Y"), FKeyDetails::GamepadKey, NAME_Pro));
	EKeys::AddKey(FKeyDetails(FProControllerButton::RightThumbstickAxisX, LOCTEXT("ProController_RightThumbstickAxisX", "Pro Controller - Right Thumbstick Axis X"), FKeyDetails::GamepadKey, NAME_Pro));
}

void FJoyconInputDevice::Tick(float DeltaTime)
{

}

void FJoyconInputDevice::SendControllerEvents()
{

}

void FJoyconInputDevice::SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{

}

bool FJoyconInputDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return true;
}

void FJoyconInputDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{

}

void FJoyconInputDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values)
{

}

FJoyconInputDevice::~FJoyconInputDevice()
{

}