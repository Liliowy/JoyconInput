#pragma once

#include "InputCoreTypes.h"

struct FLeftJoyconButton
{
	// Single Controller Shoulder Buttons
	static const FKey ShoulderLeft; // SL
	static const FKey ShoulderRight; // SR

	// Combined Controller Shoulder Buttons - Not typically used with single controllers.
	static const FKey Bumper; // L Button
	static const FKey Trigger; // ZL

	// Thumbstick Button
	static const FKey ThumbstickIn;

	// Thumbstick Axis - These are different values on combined controllers.
	static const FKey ThumbstickAxisUp; // Thumbstick Up
	static const FKey ThumbstickAxisRight; // Thumbstick Right
	static const FKey ThumbstickAxisDown; // Thumbstick Down
	static const FKey ThumbstickAxisLeft; // Thumbstick Left
	static const FKey ThumbstickAxisY; // Thumbstick Y Axis
	static const FKey ThumbstickAxisX; // Thumbstick X Axis

	// D-Pad Buttons - These are also different values on combined controllers.
	static const FKey Up; // D-Pad Up
	static const FKey Right; // D-Pad Right
	static const FKey Down; // D-Pad Down
	static const FKey Left; // D-Pad Left

	// Special Buttons
	static const FKey Minus; // - Button
	static const FKey Capture; // Screenshot Button
};

struct FRightJoyconButton
{

	// Singer Controller Shoulder Buttons
	static const FKey ShoulderLeft; // SL
	static const FKey ShoulderRight; // SR

	// Combined Controller Shoulder Buttons - Not typically used with single controllers.
	static const FKey Bumper; // R
	static const FKey Trigger; // ZR

	// Thumbstick Buttons
	static const FKey ThumbstickIn;

	// Thumbstick Axis - These are different values on combined controllers.
	static const FKey ThumbstickAxisUp; // Thumbstick Up
	static const FKey ThumbstickAxisRight; // Thumbstick Right
	static const FKey ThumbstickAxisDown; // Thumbstick Down
	static const FKey ThumbstickAxisLeft; // Thumbstick Left
	static const FKey ThumbstickAxisY; // Thumbstick Y Axis
	static const FKey ThumbstickAxisX; // Thumbstick X Axis

	// D-Pad Buttons - These are also different values on combined controllers.
	// Y is Up when the controller is not combined, etc.
	static const FKey Up; // D-Pad Y
	static const FKey Right; // D-Pad X
	static const FKey Down; // D-Pad A
	static const FKey Left; // D-Pad B

	// Special Buttons
	static const FKey Plus; // + Button
	static const FKey Home; // Home Button
};

// Combined Joycons
struct FJoyconButton
{
	// Single Controller Shoulder Buttons - Not typically used with combined controllers.
	static const FKey LeftJoycon_ShoulderLeft;
	static const FKey LeftJoycon_ShoulderRight;
	static const FKey RightJoycon_ShoulderLeft;
	static const FKey RightJoycon_ShoulderRight;

	// Combined Controller Shoulder Buttons
	static const FKey L;
	static const FKey ZL;
	static const FKey R;
	static const FKey ZR;

	// Thumbstick Buttons
	static const FKey LeftThumbstickIn;
	static const FKey RightThumbstickIn;

	// Thumbstick Axis
	static const FKey LeftThumbstickUp;
	static const FKey LeftThumbstickRight;
	static const FKey LeftThumbstickDown;
	static const FKey LeftThumbstickLeft;

	static const FKey RightThumbstickUp;
	static const FKey RightThumbstickRight;
	static const FKey RightThumbstickDown;
	static const FKey RightThumbstickLeft;

	static const FKey LeftThumbstickAxisY;
	static const FKey LeftThumbstickAxisX;
	static const FKey RightThumbstickAxisY;
	static const FKey RightThumbstickAxisX;

	// D-Pad Buttons
	static const FKey Up;
	static const FKey Right;
	static const FKey Down;
	static const FKey Left;

	// Face Buttons
	static const FKey X;
	static const FKey A;
	static const FKey B;
	static const FKey Y;

	// Special Buttons
	static const FKey Minus;
	static const FKey Plus;
	static const FKey Capture;
	static const FKey Home;
};

// Pro Controller
struct FProControllerButton
{
	// Shoulder Buttons
	static const FKey L;
	static const FKey ZL;
	static const FKey R;
	static const FKey ZR;

	// Thumbstick Buttons
	static const FKey LeftThumbstickIn;
	static const FKey RightThumbstickIn;

	// Thumbstick Axis
	static const FKey LeftThumbstickUp;
	static const FKey LeftThumbstickRight;
	static const FKey LeftThumbstickDown;
	static const FKey LeftThumbstickLeft;

	static const FKey RightThumbstickUp;
	static const FKey RightThumbstickRight;
	static const FKey RightThumbstickDown;
	static const FKey RightThumbstickLeft;

	static const FKey LeftThumbstickAxisY;
	static const FKey LeftThumbstickAxisX;
	static const FKey RightThumbstickAxisY;
	static const FKey RightThumbstickAxisX;

	// D-Pad Buttons
	static const FKey Up;
	static const FKey Right;
	static const FKey Down;
	static const FKey Left;

	// Face Buttons
	static const FKey X;
	static const FKey A;
	static const FKey B;
	static const FKey Y;

	// Special Buttons
	static const FKey Minus;
	static const FKey Plus;
	static const FKey Capture;
	static const FKey Home;
};