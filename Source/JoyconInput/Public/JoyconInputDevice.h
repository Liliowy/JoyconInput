#pragma once

#include "JoyconInput.h"
#include "JoyconInputState.h"

#include "InputDevice/Public/IInputDevice.h"
#include "OutputDevice.h"

class FJoyconInputDevice : public IInputDevice
{
public:
	FJoyconInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& MessageHandler);

	virtual void Tick(float DeltaTime) override;
	virtual void SendControllerEvents() override;
	virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
	virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
	virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values) override;

	bool IsPressed(int Input, int Button);
	bool IsReleased(int Input, int Button);

	virtual ~FJoyconInputDevice();

	void CalcAnalogStick2
	(
		float& pOutX,       // out: resulting stick X value
		float& pOutY,       // out: resulting stick Y value
		uint16_t x,              // in: initial stick X value
		uint16_t y,              // in: initial stick Y value
		uint16_t x_calc[3],      // calc -X, CenterX, +X
		uint16_t y_calc[3]       // calc -Y, CenterY, +Y
	);

private:
	bool HandleInput(int Index, UJoycon* Joycon);
	bool HandleLeftJoyconInput(int Index, UJoycon* Joycon, uint8_t* Packet);
	bool HandleRightJoyconInput(int Index, UJoycon* Joycon, uint8_t* Packet);
	bool HandleCombinedJoyconInput(int Index, UJoycon* Joycon, uint8_t* Packet);
	bool HandleProControllerInput(int Index, UJoycon* Joycon, uint8_t* Packet);

	TMap<int, FName> LeftPrimaryButtons;
	TMap<int, FName> LeftSecondaryButtons;
	TMap<int, FName> LeftAxisButtons;

	TMap<int, FName> RightPrimaryButtons;
	TMap<int, FName> RightSecondaryButtons;
	TMap<int, FName> RightAxisButtons;

	TMap<int, FName> ProPrimaryButtons;
	TMap<int, FName> ProSecondaryButtons;
	TMap<int, FName> ProAxisButtons;

	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
};