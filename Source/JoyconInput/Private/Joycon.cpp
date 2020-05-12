#include "Joycon.h"

struct brcm_hdr {
	uint8_t cmd;
	uint8_t rumble[9];
};

struct brcm_cmd_01 {
	uint8_t subcmd;
	uint32_t offset;
	uint8_t size;
};

int timing_byte = 0x0;


int get_spi_data(hid_device* handle, uint32_t offset, const uint16_t read_len, uint8_t* test_buf) 
{
	int res;
	uint8_t buf[0x100];
	while (1) {
		memset(buf, 0, sizeof(buf));
		auto hdr = (brcm_hdr*)buf;
		auto pkt = (brcm_cmd_01*)(hdr + 1);
		hdr->cmd = 1;
		hdr->rumble[0] = timing_byte;

		buf[1] = timing_byte;

		timing_byte++;
		if (timing_byte > 0xF) {
			timing_byte = 0x0;
		}
		pkt->subcmd = 0x10;
		pkt->offset = offset;
		pkt->size = read_len;

		for (int i = 11; i < 22; ++i) {
			buf[i] = buf[i + 3];
		}

		res = hid_write(handle, buf, sizeof(*hdr) + sizeof(*pkt));

		res = hid_read(handle, buf, sizeof(buf));

		if ((*(uint16_t*)&buf[0xD] == 0x1090) && (*(uint32_t*)&buf[0xF] == offset)) {
			break;
		}
	}
	if (res >= 0x14 + read_len) {
		for (int i = 0; i < read_len; i++) {
			test_buf[i] = buf[0x14 + i];
		}
	}

	return 0;
}

void UJoycon::Init(hid_device* InDevice, hid_device_info* InInfo, EControllerType InControllerType)
{
	this->Device = InDevice;
	this->DeviceInfo = InInfo;
	this->ControllerType = InControllerType;
	// TODO: Get Colour

	unsigned char Buffer[0x40];
	hid_set_nonblocking(Device, 0);

	// Sets input mode to push at 60Hz
	Buffer[0] = 0x30;
	SendSubcommand(0x01, 0x03, Buffer, 1);

	UE_LOG(LogTemp, Warning, TEXT("Maybe Set input mode?"));

	// Enables Vibration
	Buffer[0] = 0x01;
	SendSubcommand(0x01, 0x48, Buffer, 1);

	// Enables IMU
	Buffer[0] = 0x01;
	SendSubcommand(0x01, 0x40, Buffer, 1);


	// Bruh
	unsigned char factory_stick_cal[0x22];
	memset(factory_stick_cal, 0, 0x12);
	memset(stick_cal_x, 0, 0x3);
	memset(stick_cal_y, 0, 0x3);

	get_spi_data(Device, 0x6020, 0x18, factory_stick_cal);

	stick_cal_x[1] = (factory_stick_cal[4] << 8) & 0xF00 | factory_stick_cal[3];
	stick_cal_y[1] = (factory_stick_cal[5] << 4) | (factory_stick_cal[4] >> 4);
	stick_cal_x[0] = stick_cal_x[1] - ((factory_stick_cal[7] << 8) & 0xF00 | factory_stick_cal[6]);
	stick_cal_y[0] = stick_cal_y[1] - ((factory_stick_cal[8] << 4) | (factory_stick_cal[7] >> 4));
	stick_cal_x[2] = stick_cal_x[1] + ((factory_stick_cal[1] << 8) & 0xF00 | factory_stick_cal[0]);
	stick_cal_y[2] = stick_cal_y[1] + ((factory_stick_cal[2] << 4) | (factory_stick_cal[2] >> 4));
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

	// Rumble Stuff?

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