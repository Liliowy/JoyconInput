#include "Joycon.h"

TArray<int32> PreviousButtons = TArray<int32>();
TArray<int32> PreviousSharedButtons = TArray<int32>();

void UJoycon::Init(hid_device* InDevice, hid_device_info* InInfo, EControllerType InControllerType)
{
	this->Device = InDevice;
	this->DeviceInfo = InInfo;
	this->ControllerType = InControllerType;

	unsigned char Buffer[0x40];
	hid_set_nonblocking(Device, 0);

	// Sets input mode to push at 60Hz
	Buffer[0] = 0x30;
	SendSubcommand(0x01, 0x03, Buffer, 1);

	// Enables Vibration
	Buffer[0] = 0x01;
	SendSubcommand(0x01, 0x48, Buffer, 1);

	// Enables IMU
	Buffer[0] = 0x01;
	SendSubcommand(0x01, 0x40, Buffer, 1);
}

void UJoycon::SendCommand(int Command, uint8_t* Packet, int Length)
{
	unsigned char Buffer[0x40];
	memset(Buffer, 0, 0x40);
	Buffer[0] = Command;

	if (Packet != nullptr && Length != 0) memcpy(Buffer + 1, Packet, Length);
	GetResponse(Buffer, Length + 1);

	if (Packet) memcpy(Packet, Buffer, 0x40);
}

void UJoycon::SendSubcommand(int Command, int Subcommand, uint8_t* Packet, int Length)
{
	unsigned char Buffer[0x40];
	memset(Buffer, 0, 0x40);

	Buffer[9] = Subcommand;
	if (Packet && Length != 0) memcpy(Buffer + 10, Packet, Length);
	SendCommand(Command, Buffer, Length + 10);

	if (Packet) memcpy(Packet, Buffer, 0x40);
}

void UJoycon::GetResponse(unsigned char* Buffer, int Length)
{
	int Result;
	Result = hid_write(Device, Buffer, Length);
	Result = hid_read(Device, Buffer, 0x40);
}

void UJoycon::ApplyLEDChanges(int32 LEDIndex, ELEDState LEDState, unsigned char* Buffer)
{
	switch (LEDState) {
	case ELEDState::On:
		Buffer[0] |= 1 << (LEDIndex - 1);
		break;
	case ELEDState::Flashing:
		Buffer[0] |= 1 << (LEDIndex + 3);
		break;
	default:
		break;
	}
}

void UJoycon::SetLEDStates(ELEDState LED_1, ELEDState LED_2, ELEDState LED_3, ELEDState LED_4)
{
	unsigned char Buffer[0x40];
	memset(Buffer, 0, 0x40);

	ApplyLEDChanges(1, LED_1, Buffer);
	ApplyLEDChanges(2, LED_2, Buffer);
	ApplyLEDChanges(3, LED_3, Buffer);
	ApplyLEDChanges(4, LED_4, Buffer);

	SendSubcommand(0x01, 0x30, Buffer, 1);
}

void UJoycon::Rumble(int Frequency, int Intensity)
{
	unsigned char Buffer[0x40];
	memset(Buffer, 0, 0x40);

	Buffer[Intensity + 1] = 0x1;
	Buffer[Intensity + 5] = 0x1;
	Buffer[1] = Frequency;

	SendCommand(0x01, Buffer, 0x9);
}

void UJoycon::SetHomeLEDState()
{
	unsigned char Buffer[0x40];
	memset(Buffer, 0, 0x40);

	Buffer[0] = 15;

	SendSubcommand(0x01, 0x38, Buffer, 1);
}