#include "JoyconInput.h"

IMPLEMENT_MODULE(FJoyconInputModule, JoyconInput);

#define LOCTEXT_NAMESPACE "FJoyconInputModule"

TArray<UJoycon*> FJoyconInputModule::Joycons = TArray<UJoycon*>();

TSharedPtr<class IInputDevice> FJoyconInputModule::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	FJoyconInputModule::JoyconInputDevice = MakeShareable(new FJoyconInputDevice(InMessageHandler));
	return JoyconInputDevice;
}

void FJoyconInputModule::ShutdownModule()
{
	for (UJoycon* Joycon : FJoyconInputModule::Joycons) hid_close(Joycon->GetDevice());
	hid_exit();
}

#undef LOCTEXT_NAMESPACE