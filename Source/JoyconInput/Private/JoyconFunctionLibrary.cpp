#include "JoyconFunctionLibrary.h"

#define DEBUG true

#define JOYCON_VENDOR 0x057e
#define LEFT_JOYCON_ID 0x2006
#define RIGHT_JOYCON_ID 0x2007
#define PRO_CONTROLLER_ID 0x2009

DEFINE_LOG_CATEGORY_STATIC(LogJoyconFunctionLibrary, Log, All);

void UJoyconFunctionLibrary::ConnectJoycons(bool& Success, int32& Count)
{
#ifdef DEBUG
	UE_LOG(LogJoyconFunctionLibrary, Log, TEXT("Searching for Joycons..."));
#endif

	hid_device_info* Devices = hid_enumerate(JOYCON_VENDOR, 0);

	if (Devices == nullptr) {
#ifdef DEBUG
		UE_LOG(LogJoyconFunctionLibrary, Log, TEXT("No Joycons Found"));
#endif

		hid_free_enumeration(Devices);
		Success = false;
		return;
	}

	int JoyconCount = 0;
	hid_device_info* Device = Devices;

	while (Devices) {
		if (Device->product_id == LEFT_JOYCON_ID) {
			UJoycon* Joycon = NewObject<UJoycon>();
			Joycon->Init(hid_open_path(Device->path), EControllerType::Left);
			FJoyconInputModule::GetJoycons().Add(Joycon);
			JoyconCount++;
		}

		if (Device->product_id == RIGHT_JOYCON_ID) {
			UJoycon* Joycon = NewObject<UJoycon>();
			Joycon->Init(hid_open_path(Device->path), EControllerType::Right);
			FJoyconInputModule::GetJoycons().Add(Joycon);
			JoyconCount++;
		}

		if (Device->product_id == PRO_CONTROLLER_ID) {
			UJoycon* Joycon = NewObject<UJoycon>();
			Joycon->Init(hid_open_path(Device->path), EControllerType::Right);
			FJoyconInputModule::GetJoycons().Add(Joycon);
			JoyconCount++;
		}

		Device = Device->next;
	}

	hid_free_enumeration(Devices);
	Success = true;
	Count = JoyconCount;

#ifdef DEBUG
	UE_LOG(LogJoyconFunctionLibrary, Log, TEXT("Found %d Joycons"), *FString::FromInt(JoyconCount));
#endif
}

void UJoyconFunctionLibrary::DisconnectJoycons(bool& Success)
{
#ifdef DEBUG
	UE_LOG(LogJoyconFunctionLibrary, Log, TEXT("Disconnecting Joycons..."));
#endif

	for (UJoycon* Joycon : FJoyconInputModule::GetJoycons()) hid_close(Joycon->GetDevice());
	Success = (hid_exit() == 0);
}

void UJoyconFunctionLibrary::GetJoycon(int32 ControllerId, UJoycon*& Joycon)
{
	FJoyconInputModule::GetJoycons().Find(Joycon, ControllerId);
}

void UJoyconFunctionLibrary::GetJoycons(TArray<UJoycon*>& Joycons)
{
	Joycons = FJoyconInputModule::GetJoycons();
}