#pragma once

#include "hidapi.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Joycon.generated.h"

/*
The state that a Player LED can be in.
*/
UENUM(BlueprintType)
enum class ELEDState : uint8
{
	Off,
	On,
	Flashing
};

/*
The type of controller that this is.
*/
UENUM(BlueprintType)
enum class EControllerType : uint8
{
	Left,
	Right
};

UCLASS()
class JOYCONINPUT_API UJoycon : public UObject
{
	GENERATED_BODY()

public:
	/*
	Initialises this controller.
	*/
	void Init(hid_device* InDevice, hid_device_info* InInfo, EControllerType InControllerType);

	/*
	Sends a command to the controller.
	*/
	void SendCommand(int Command, uint8_t* Packet, int Length);

	/*
	Sends a command and subcommand to the controller.
	*/
	void SendSubcommand(int Command, int Subcommand, uint8_t* Packet, int Length);

	/*
	Gets the response from a command.
	*/
	void GetResponse(unsigned char* Buffer, int Length);

	/*
	Applies the changes to the Player LEDs.
	*/
	void ApplyLEDChanges(int32 LEDIndex, ELEDState LEDState, unsigned char* Buffer);

	/*
	Sets the state of the Player LEDs.
	*/
	UFUNCTION(BlueprintCallable, Category = "JoyconInput")
	void SetLEDStates(ELEDState LED_1, ELEDState LED_2, ELEDState LED_3, ELEDState LED_4);

	/*
	Sends a vibration to the controller.
	*/
	UFUNCTION(BlueprintCallable, Category = "JoyconInput")
	void Rumble(int Frequency, int Intensity);

	/*
	Sets the state of the Home LED.
	*/
	UFUNCTION(BlueprintCallable, Category = "JoyconInput")
	void SetHomeLEDState();

	/*
	Gets the colour of the controller.
	*/
	UFUNCTION(BlueprintCallable, Category = "JoyconInput")
	void GetJoyconColor(FLinearColor& OutColor) {
		OutColor = this->Color;
	}

	/*
	Enables NFC input.
	*/
	/*
	UFUNCTION(BlueprintCallable, Category = "JoyconInput")
	void EnableNFC();*/

	/*
	Enables IR input.
	
	UFUNCTION(BlueprintCallable, Category = "JoyconInput")
	void EnableIR();*/

	hid_device* GetDevice() {
		return Device;
	}

	hid_device_info* GetDeviceInfo() {
		return DeviceInfo;
	}

	/*UFUNCTION(BlueprintCallable, Category = "JoyconInput")
	void GetControllerType(EControllerType& OutControllerType) {
		OutControllerType = ControllerType;
	}*/

	EControllerType GetControllerType() {
		return ControllerType;
	}

	TArray<int32> GetPreviousButtons() {
		return PreviousButtons;
	}

	TArray<int32> GetPreviousSharedButtons() {
		return PreviousSharedButtons;
	}

	TArray<int32> PreviousButtons;
	TArray<int32> PreviousSharedButtons;

private:
	hid_device* Device;
	hid_device_info* DeviceInfo;
	EControllerType ControllerType;
	FLinearColor Color;
};