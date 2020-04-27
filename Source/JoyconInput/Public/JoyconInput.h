#pragma once

#include "IJoyconInputModule.h"
#include "Joycon.h"
#include "JoyconInputDevice.h"

class FJoyconInputModule : public IJoyconInputModule
{
public:
	virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);

	virtual void ShutdownModule() override;

	TSharedPtr<class FJoyconInputDevice> JoyconInputDevice;

public:
	static TArray<UJoycon*> Joycons;
};
