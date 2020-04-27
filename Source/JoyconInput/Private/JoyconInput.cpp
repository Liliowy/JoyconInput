#include "JoyconInput.h"

IMPLEMENT_MODULE(FJoyconInputModule, JoyconInput);

#define LOCTEXT_NAMESPACE "FJoyconInputModule"

TArray<UJoycon*> FJoyconInputModule::Joycons;

TSharedPtr<class IInputDevice> FJoyconInputModule::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	FJoyconInputModule::JoyconInputDevice = MakeShareable(new FJoyconInputDevice(InMessageHandler));
	return JoyconInputDevice;
}

void FJoyconInputModule::ShutdownModule()
{
	for (UJoycon* Joycon : FJoyconInputModule::Joycons) {
		hid_set_nonblocking(Joycon->GetDevice(), 1);
		hid_close(Joycon->GetDevice());
	}
	hid_exit();

	FJoyconInputModule::JoyconInputDevice->~FJoyconInputDevice();
}

#undef LOCTEXT_NAMESPACE