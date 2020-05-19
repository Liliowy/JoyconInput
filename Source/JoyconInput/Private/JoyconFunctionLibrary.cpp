#include "JoyconFunctionLibrary.h"

#include "Engine/Engine.h"

#define JOYCON_VENDOR 0x57E
#define LEFT_JOYCON 0x2006
#define RIGHT_JOYCON 0x2007
#define PRO_CONTROLLER 0x2009

void UJoyconFunctionLibrary::ConnectJoycons(bool& Success, int32& Count)
{
	FJoyconInputModule::Joycons = TArray<UJoycon*>();

	hid_device_info* Devices = hid_enumerate(JOYCON_VENDOR, 0x00);

	if (Devices == nullptr) {
		hid_free_enumeration(Devices);
		Success = false;
		return;
	}

	hid_device_info* Device = Devices;
	while (Device) {
		UJoycon* Joycon = NewObject<UJoycon>();

		switch (Device->product_id) {
		case LEFT_JOYCON:
			Joycon->Init(hid_open_path(Device->path), Device, EControllerType::Left);
			break;
		case RIGHT_JOYCON:
			Joycon->Init(hid_open_path(Device->path), Device, EControllerType::Right);
			break;
		}

		FJoyconInputModule::Joycons.Add(Joycon);
		Count++;

		Device = Device->next;
	}

	hid_free_enumeration(Devices);
	Success = true;
}

void UJoyconFunctionLibrary::DisconnectJoycons(bool& Success)
{
	for (UJoycon* Joycon : FJoyconInputModule::Joycons) {
		if (!Joycon) continue;
		hid_close(Joycon->GetDevice());
	}
	
	Success = (hid_exit() == 0);
}

void UJoyconFunctionLibrary::GetJoycon(int32 ControllerId, UJoycon*& Joycon)
{
	Joycon = FJoyconInputModule::Joycons[ControllerId];
}

void UJoyconFunctionLibrary::GetJoycons(TArray<UJoycon*>& Joycons)
{
	Joycons = FJoyconInputModule::Joycons;
}