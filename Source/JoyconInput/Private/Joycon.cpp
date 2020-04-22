#include "Joycon.h"

#define DEBUG true

DEFINE_LOG_CATEGORY_STATIC(LogJoycon, Log, All);

void UJoycon::Init(hid_device* Device, EControllerType ControllerType)
{
	this->Device = Device;
	this->ControllerType = ControllerType;

#ifdef DEBUG
	FString ControllerStr(UEnum::GetValueAsString<EControllerType>(ControllerType));
	UE_LOG(LogJoycon, Log, TEXT("%s Controller Created"), *ControllerStr);
#endif
}

void UJoycon::SendCommand(int Command, uint8_t* Data, int Len)
{
#ifdef DEBUG
	UE_LOG(LogJoycon, Log, TEXT("Sending Command: %s"), *FString::FromInt(Command));
#endif

	memset(Buffer, 0, 64);
	Buffer[0] = Command;

	if (Data != nullptr && Len != 0) memcpy(Buffer + (1), Data, Len);

	GetResponse(Buffer, Len + (1));

	if (Data) memcpy(Data, Buffer, 64);
}

void UJoycon::SendSubcommand(int Command, int Subcommand, uint8_t* Data, int Len)
{
#ifdef DEBUG
	UE_LOG(LogJoycon, Log, TEXT("Sending Command & Subcommand: %s : %s"), *FString::FromInt(Command), *FString::FromInt(Subcommand));
#endif

	memset(Buffer, 0, 64);
	Buffer[9] = Subcommand;

	if (Data && Len != 0) memcpy(Buffer + 10, Data, Len);

	SendCommand(Command, Buffer, 10 + Len);

	if (Data) memcpy(Data, Buffer, 64);
}

void UJoycon::GetResponse(unsigned char* Buf, int Len)
{
	int Res;
	Res = hid_write(Device, Buf, Len);
	Res = hid_read(Device, Buf, 64);
}

void UJoycon::ApplyLEDs(int32 LEDIndex, ELEDMode LEDMode)
{
	switch (LEDMode) {
	case ELEDMode::On:
		Buffer[0] |= 1 << (LEDIndex - 1);
		break;
	case ELEDMode::Flashing:
		Buffer[0] |= 1 << (LEDIndex + 3);
		break;
	default:
		break;
	}
}

void UJoycon::SetLEDModes(ELEDMode LED_1, ELEDMode LED_2, ELEDMode LED_3, ELEDMode LED_4)
{
	memset(Buffer, 0, 64);

	ApplyLEDs(1, LED_1);
	ApplyLEDs(2, LED_2);
	ApplyLEDs(3, LED_3);
	ApplyLEDs(4, LED_4);

	SendSubcommand(1, 0x30, Buffer, 1);
}