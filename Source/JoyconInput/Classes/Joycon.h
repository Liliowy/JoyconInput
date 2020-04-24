#pragma once

#include "CoreMinimal.h"
#include "hidapi.h"
#include "UObject/NoExportTypes.h"
#include "Joycon.generated.h"

// How a player LED can act.
UENUM(BlueprintType)
enum class ELEDMode : uint8
{
	Off, // The LED is off.
	On, // The LED is on.
	Flashing // The LED is flashing.
};

// The type of switch controller.
UENUM(BlueprintType)
enum class EControllerType : uint8
{
	Left, // The left Joycon.
	Right, // The right Joycon.
	Combined, // Both Joycons combined.
	Pro // The Pro Controller.
};

UCLASS()
class JOYCONINPUT_API UJoycon : public UObject
{
	GENERATED_BODY()
	
public:

	// Acts as a constructor due to NewObject<> call.
	void Init(hid_device* Device, EControllerType ControllerType);

	// Sends a command to the Joycon.
	void SendCommand(int Command, uint8_t* Data, int Len);

	// Sends a command and subcommand to the Joycon.
	void SendSubcommand(int Command, int Subcommand, uint8_t* Data, int Len);

	// Gets the response from a command.
	void GetResponse(unsigned char* Buf, int Len);

	// Applies the LED changes.
	void ApplyLEDs(int32 LEDIndex, ELEDMode LEDMode);

	// Blueprint node to set the modes of the LEDs.
	UFUNCTION(BlueprintCallable, Category = "JoyconInput")
	void SetLEDModes(ELEDMode LED_1, ELEDMode LED_2, ELEDMode LED_3, ELEDMode LED4);

	/*
		To Do:
		GetRotation()
		GetAcceleration()
		
		Rumble / Vibrate, IR Sensor, NFC Reader.
	*/

	// Returns the HID Device.
	hid_device* GetDevice() {
		return Device;
	}

	// Returns the type of controller that this is.
	EControllerType GetControllerType() {
		return ControllerType;
	}

	// Returns the button that was previously pressed.
	int GetPreviousButton() {
		return PreviousButton;
	}

	void SetPreviousButton(int InPreviousButton) {
		this->PreviousButton = InPreviousButton;
	}
private:
	// A pointer to the HID Device.
	hid_device* Device;

	// The type of controller that this is.
	EControllerType ControllerType;

	// The button that was previously pressed. Used for holding buttons.
	int PreviousButton;

	unsigned char Buffer[0x40];
};
