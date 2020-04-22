#pragma once

#include "IJoyconInputModule.h"
#include "Joycon.h"

class FJoyconInputModule : public IJoyconInputModule
{
public:
	virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);

	virtual void ShutdownModule() override;

	TSharedPtr<class FJoyconInputDevice> JoyconInputDevice;

	static TArray<UJoycon*> GetJoycons() {
		return Joycons;
	}

private:
	static TArray<UJoycon*> Joycons;
};
