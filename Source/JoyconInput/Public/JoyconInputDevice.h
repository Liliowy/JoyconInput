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


	virtual ~FJoyconInputDevice();

private:
	bool HandleInput(int Index, UJoycon* Joycon);
	bool HandleLeftJoyconInput(int Index, UJoycon* Joycon, uint8_t* Packet);
	bool HandleRightJoyconInput(int Index, UJoycon* Joycon, uint8_t* Packet);
	bool HandleCombinedJoyconInput(int Index, UJoycon* Joycon, uint8_t* Packet);
	bool HandleProControllerInput(int Index, UJoycon* Joycon, uint8_t* Packet);

	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
};