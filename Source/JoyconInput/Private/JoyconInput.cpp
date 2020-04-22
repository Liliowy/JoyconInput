#include "JoyconInput.h"
#include "JoyconInputDevice.h"

IMPLEMENT_MODULE(FJoyconInputModule, JoyconInput);

#define LOCTEXT_NAMESPACE "FJoyconInputModule"

TSharedPtr<class IInputDevice> FJoyconInputModule::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	FJoyconInputModule::JoyconInputDevice = MakeShareable(new FJoyconInputDevice(InMessageHandler));
	return JoyconInputDevice;
}

void FJoyconInputModule::ShutdownModule()
{
	FJoyconInputModule::JoyconInputDevice->~FJoyconInputDevice();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FJoyconInputModule, JoyconInput)