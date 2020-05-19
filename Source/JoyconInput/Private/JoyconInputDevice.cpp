#include "JoyconInputDevice.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogJoyconInputDevice, Log, All);

#define LOCTEXT_NAMESPACE "JoyconInputDevice"

#define RIGHT_BUTTON 3
#define SHARED_BUTTON 4
#define LEFT_BUTTON 5

TMap<int32, FName> LeftButtons = TMap<int32, FName>();
TMap<int32, FName> SharedButtons = TMap<int32, FName>();
TMap<int32, FName> RightButtons = TMap<int32, FName>();

// Button Names
const FKey FLeftJoyconButton::ShoulderLeft("LeftJoycon_ShoulderLeft");
const FKey FLeftJoyconButton::ShoulderRight("LeftJoycon_ShoulderRight");
const FKey FLeftJoyconButton::Up("LeftJoycon_Up");
const FKey FLeftJoyconButton::Right("LeftJoycon_Right");
const FKey FLeftJoyconButton::Down("LeftJoycon_Down");
const FKey FLeftJoyconButton::Left("LeftJoycon_Left");
const FKey FLeftJoyconButton::Bumper("LeftJoycon_Bumper");
const FKey FLeftJoyconButton::Trigger("LeftJoycon_Trigger");
const FKey FLeftJoyconButton::Minus("LeftJoycon_Minus");
const FKey FLeftJoyconButton::ThumbstickIn("LeftJoycon_ThumbstickIn");
const FKey FLeftJoyconButton::Capture("LeftJoycon_Capture");
const FKey FLeftJoyconButton::ThumbstickAxisUp("LeftJoycon_ThumbstickUp");
const FKey FLeftJoyconButton::ThumbstickAxisRight("LeftJoycon_ThumbstickRight");
const FKey FLeftJoyconButton::ThumbstickAxisDown("LeftJoycon_ThumbstickDown");
const FKey FLeftJoyconButton::ThumbstickAxisLeft("LeftJoycon_ThumbstickLeft");
const FKey FLeftJoyconButton::ThumbstickAxisUpRight("LeftJoycon_ThumbstickUpRight");
const FKey FLeftJoyconButton::ThumbstickAxisUpLeft("LeftJoycon_ThumbstickUpLeft");
const FKey FLeftJoyconButton::ThumbstickAxisDownRight("LeftJoycon_ThumbstickDownRight");
const FKey FLeftJoyconButton::ThumbstickAxisDownLeft("LeftJoycon_ThumbstickDownLeft");
const FKey FLeftJoyconButton::ThumbstickAxisY("LeftJoycon_AxisY");
const FKey FLeftJoyconButton::ThumbstickAxisX("LeftJoycon_AxisX");

const FKey FRightJoyconButton::ShoulderLeft("RightJoycon_ShoulderLeft");
const FKey FRightJoyconButton::ShoulderRight("RightJoycon_ShoulderRight");
const FKey FRightJoyconButton::Up("RightJoycon_Up");
const FKey FRightJoyconButton::Right("RightJoycon_Right");
const FKey FRightJoyconButton::Down("RightJoycon_Down");
const FKey FRightJoyconButton::Left("RightJoycon_Left");
const FKey FRightJoyconButton::Bumper("RightJoycon_Bumper");
const FKey FRightJoyconButton::Trigger("RightJoycon_Trigger");
const FKey FRightJoyconButton::Plus("RightJoycon_Plus");
const FKey FRightJoyconButton::ThumbstickIn("RightJoycon_ThumbstickIn");
const FKey FRightJoyconButton::Home("RightJoycon_Capture");
const FKey FRightJoyconButton::ThumbstickAxisUp("RightJoycon_ThumbstickUp");
const FKey FRightJoyconButton::ThumbstickAxisRight("RightJoycon_ThumbstickRight");
const FKey FRightJoyconButton::ThumbstickAxisDown("RightJoycon_ThumbstickDown");
const FKey FRightJoyconButton::ThumbstickAxisLeft("RightJoycon_ThumbstickLeft");
const FKey FRightJoyconButton::ThumbstickAxisUpRight("RightJoycon_ThumbstickUpRight");
const FKey FRightJoyconButton::ThumbstickAxisUpLeft("RightJoycon_ThumbstickUpLeft");
const FKey FRightJoyconButton::ThumbstickAxisDownRight("RightJoycon_ThumbstickDownRight");
const FKey FRightJoyconButton::ThumbstickAxisDownLeft("RightJoycon_ThumbstickDownLeft");
const FKey FRightJoyconButton::ThumbstickAxisY("RightJoycon_AxisY");
const FKey FRightJoyconButton::ThumbstickAxisX("RightJoycon_AxisX");

FJoyconInputDevice::FJoyconInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) : MessageHandler(InMessageHandler)
{
	const FName NAME_LeftJoycon(TEXT("LeftJoycon"));
	const FName NAME_RightJoycon(TEXT("RightJoycon"));

	// Mapping Buttons
	LeftButtons.Add(0x80, FLeftJoyconButton::Trigger.GetFName());
	LeftButtons.Add(0x40, FLeftJoyconButton::Bumper.GetFName());
	LeftButtons.Add(0x20, FLeftJoyconButton::ShoulderLeft.GetFName());
	LeftButtons.Add(0x10, FLeftJoyconButton::ShoulderRight.GetFName());
	LeftButtons.Add(0x08, FLeftJoyconButton::Down.GetFName());
	LeftButtons.Add(0x04, FLeftJoyconButton::Up.GetFName());
	LeftButtons.Add(0x01, FLeftJoyconButton::Right.GetFName());
	LeftButtons.Add(0x02, FLeftJoyconButton::Left.GetFName());

	SharedButtons.Add(0x20, FLeftJoyconButton::Capture.GetFName());
	SharedButtons.Add(0x08, FLeftJoyconButton::ThumbstickIn.GetFName());
	SharedButtons.Add(0x01, FLeftJoyconButton::Minus.GetFName());
	SharedButtons.Add(0x10, FRightJoyconButton::Home.GetFName());
	SharedButtons.Add(0x04, FRightJoyconButton::ThumbstickIn.GetFName());
	SharedButtons.Add(0x02, FRightJoyconButton::Plus.GetFName());

	RightButtons.Add(0x80, FRightJoyconButton::Trigger.GetFName());
	RightButtons.Add(0x40, FRightJoyconButton::Bumper.GetFName());
	RightButtons.Add(0x20, FRightJoyconButton::ShoulderLeft.GetFName());
	RightButtons.Add(0x10, FRightJoyconButton::ShoulderRight.GetFName());
	RightButtons.Add(0x08, FRightJoyconButton::Down.GetFName());
	RightButtons.Add(0x04, FRightJoyconButton::Left.GetFName());
	RightButtons.Add(0x02, FRightJoyconButton::Right.GetFName());
	RightButtons.Add(0x01, FRightJoyconButton::Up.GetFName());

	// Add input menu categories.
	EKeys::AddMenuCategoryDisplayInfo(NAME_LeftJoycon, LOCTEXT("LeftJoyconSubcategory", "Left Joycon"), TEXT("GraphEditor.PadEvent_16x"));
	EKeys::AddMenuCategoryDisplayInfo(NAME_RightJoycon, LOCTEXT("RightJoyconSubcategory", "Right Joycon"), TEXT("GraphEditor.PadEvent_16x"));

	// Add keys.
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ShoulderLeft, LOCTEXT("LeftJoycon_ShoulderLeft", "Left Joycon - Shoulder Left"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ShoulderRight, LOCTEXT("LeftJoycon_ShoulderRight", "Left Joycon - Shoulder Right"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Up, LOCTEXT("LeftJoycon_Up", "Left Joycon - Up"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Right, LOCTEXT("LeftJoycon_Right", "Left Joycon - Right"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Down, LOCTEXT("LeftJoycon_Down", "Left Joycon - Down"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Left, LOCTEXT("LeftJoycon_Left", "Left Joycon - Left"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Bumper, LOCTEXT("LeftJoycon_Bumper", "Left Joycon - Bumper"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Trigger, LOCTEXT("LeftJoycon_Trigger", "Left Joycon - Trigger"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Minus, LOCTEXT("LeftJoycon_Minus", "Left Joycon - Minus"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickIn, LOCTEXT("LeftJoycon_ThumbstickIn", "Left Joycon - Thumbstick In"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::Capture, LOCTEXT("LeftJoycon_Capture", "Left Joycon - Capture"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisUp, LOCTEXT("LeftJoycon_ThumbstickUp", "Left Joycon - Thumbstick Up"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisUpRight, LOCTEXT("LeftJoycon_ThumbstickUpRight", "Left Joycon - Thumbstick Up Right"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisRight, LOCTEXT("LeftJoycon_ThumbstickRight", "Left Joycon - Thumbstick Right"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisDownRight, LOCTEXT("LeftJoycon_ThumbstickDownRight", "Left Joycon - Thumbstick Down Right"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisDown, LOCTEXT("LeftJoycon_ThumbstickDown", "Left Joycon - Thumbstick Down"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisDownLeft, LOCTEXT("LeftJoycon_ThumbstickDownLeft", "Left Joycon - Thumbstick Down Left"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisLeft, LOCTEXT("LeftJoycon_ThumbstickLeft", "Left Joycon - Thumbstick Left"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisUpLeft, LOCTEXT("LeftJoycon_ThumbstickUpLeft", "Left Joycon - Thumbstick Up Left"), FKeyDetails::GamepadKey, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisY, LOCTEXT("LeftJoycon_AxisY", "Left Joycon - Thumbstick Axis Y"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis, NAME_LeftJoycon));
	EKeys::AddKey(FKeyDetails(FLeftJoyconButton::ThumbstickAxisX, LOCTEXT("LeftJoycon_AxisX", "Left Joycon - Thumbstick Axis X"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis, NAME_LeftJoycon));

	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ShoulderLeft, LOCTEXT("RightJoycon_ShoulderLeft", "Right Joycon - Shoulder Left"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ShoulderRight, LOCTEXT("RightJoycon_ShoulderRight", "Right Joycon - Shoulder Right"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Up, LOCTEXT("RightJoycon_Up", "Right Joycon - Up"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Right, LOCTEXT("RightJoycon_Right", "Right Joycon - Right"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Down, LOCTEXT("RightJoycon_Down", "Right Joycon - Down"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Left, LOCTEXT("RightJoycon_Left", "Right Joycon - Left"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Bumper, LOCTEXT("RightJoycon_Bumper", "Right Joycon - Bumper"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Trigger, LOCTEXT("RightJoycon_Trigger", "Right Joycon - Trigger"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Plus, LOCTEXT("RightJoycon_Plus", "Right Joycon - Minus"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickIn, LOCTEXT("RightJoycon_ThumbstickIn", "Right Joycon - Thumbstick In"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::Home, LOCTEXT("RightJoycon_Home", "Right Joycon - Home"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisUp, LOCTEXT("RightJoycon_ThumbstickUp", "Right Joycon - Thumbstick Up"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisRight, LOCTEXT("RightJoycon_ThumbstickRight", "Right Joycon - Thumbstick Right"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisDown, LOCTEXT("RightJoycon_ThumbstickDown", "Right Joycon - Thumbstick Down"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisLeft, LOCTEXT("RightJoycon_ThumbstickLeft", "Right Joycon - Thumbstick Left"), FKeyDetails::GamepadKey, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisY, LOCTEXT("RightJoycon_AxisY", "Right Joycon - Thumbstick Axis Y"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis, NAME_RightJoycon));
	EKeys::AddKey(FKeyDetails(FRightJoyconButton::ThumbstickAxisX, LOCTEXT("RightJoycon_AxisX", "Right Joycon - Thumbstick Axis X"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis, NAME_RightJoycon));
}

void FJoyconInputDevice::Tick(float DeltaTime)
{

}

void FJoyconInputDevice::SendControllerEvents()
{
	if (!FJoyconInputModule::Joycons.IsValidIndex(0)) return;

	int Index = 0;
	for (UJoycon* Joycon : FJoyconInputModule::Joycons) {
		if (!Joycon || Joycon == nullptr) continue;
		if (Joycon->GetDevice() == nullptr) continue;
		HandleInput(Index, Joycon);
		Index++;
	}
}

bool FJoyconInputDevice::HandleInput(int Index, UJoycon* Joycon)
{
	if (!Joycon) return false;
	unsigned char Packet[0x64];
	if (hid_set_nonblocking(Joycon->GetDevice(), 1) == -1) return false;
	memset(Packet, 0, 0x64);
	if (hid_read(Joycon->GetDevice(), Packet, 0x64) == -1) return false;

	if (Packet[0] != 0x30) return false;

	if (Joycon->GetControllerType() == EControllerType::Left) HandleLeftJoyconInput(Index, Joycon, Packet);
	if (Joycon->GetControllerType() == EControllerType::Right) HandleRightJoyconInput(Index, Joycon, Packet);

	return true;
}

bool FJoyconInputDevice::HandleLeftJoyconInput(int Index, UJoycon* Joycon, uint8_t* Packet)
{

	for (auto& Button : LeftButtons) {
		if (IsPressed(Packet[LEFT_BUTTON], Button.Key) && Joycon->PreviousButtons.Find(Button.Key) == INDEX_NONE) {
			MessageHandler->OnControllerButtonPressed(Button.Value, Index, false);
			Joycon->PreviousButtons.Add(Button.Key);
		}

		if (!IsPressed(Packet[LEFT_BUTTON], Button.Key) && Joycon->PreviousButtons.Find(Button.Key) != INDEX_NONE) {
			MessageHandler->OnControllerButtonReleased(Button.Value, Index, false);
			Joycon->PreviousButtons.Remove(Button.Key);
		}
	}

	for (auto& Button : SharedButtons) {
		if (IsPressed(Packet[SHARED_BUTTON], Button.Key) && Joycon->PreviousSharedButtons.Find(Button.Key) == INDEX_NONE) {
			MessageHandler->OnControllerButtonPressed(Button.Value, Index, false);
			Joycon->PreviousSharedButtons.Add(Button.Key);
		}

		if (!IsPressed(Packet[SHARED_BUTTON], Button.Key) && Joycon->PreviousSharedButtons.Find(Button.Key) != INDEX_NONE) {
			MessageHandler->OnControllerButtonReleased(Button.Value, Index, false);
			Joycon->PreviousSharedButtons.Remove(Button.Key);
		}
	}


	uint8_t* StickAxis = Packet + 6;
	uint16_t uStickY = StickAxis[0] | ((StickAxis[1] & 0xF) << 8);
	uint16_t uStickX = (StickAxis[1] >> 4) | (StickAxis[2] << 4);

	float StickY = uStickY;
	float StickX = uStickX;

	float NormalisedY = (StickY - 695) / (3065 - 695);
	float NormalisedX = (StickX - 1210) / (3355 - 1210);

	NormalisedY = FMath::RoundFromZero((NormalisedY * 100)) / 100;
	NormalisedX = FMath::RoundFromZero((NormalisedX * 100)) / 100;
	NormalisedY = FMath::Clamp(NormalisedY, 0.0f, 1.0f);
	NormalisedX = FMath::Clamp(NormalisedX, 0.0f, 1.0f);

	MessageHandler->OnControllerAnalog(FLeftJoyconButton::ThumbstickAxisX.GetFName(), Index, NormalisedX);
	MessageHandler->OnControllerAnalog(FLeftJoyconButton::ThumbstickAxisY.GetFName(), Index, NormalisedY);

	return true;
}

bool FJoyconInputDevice::HandleRightJoyconInput(int Index, UJoycon* Joycon, uint8_t* Packet)
{

	for (auto& Button : RightButtons) {
		if (IsPressed(Packet[RIGHT_BUTTON], Button.Key) && Joycon->PreviousButtons.Find(Button.Key) == INDEX_NONE) {
			MessageHandler->OnControllerButtonPressed(Button.Value, Index, false);
			Joycon->PreviousButtons.Add(Button.Key);
		}

		if (!IsPressed(Packet[RIGHT_BUTTON], Button.Key) && Joycon->PreviousButtons.Find(Button.Key) != INDEX_NONE) {
			MessageHandler->OnControllerButtonReleased(Button.Value, Index, false);
			Joycon->PreviousButtons.Remove(Button.Key);
		}
	}

	for (auto& Button : SharedButtons) {
		if (IsPressed(Packet[SHARED_BUTTON], Button.Key) && Joycon->PreviousSharedButtons.Find(Button.Key) == INDEX_NONE) {
			MessageHandler->OnControllerButtonPressed(Button.Value, Index, false);
			Joycon->PreviousSharedButtons.Add(Button.Key);
		}

		if (!IsPressed(Packet[SHARED_BUTTON], Button.Key) && Joycon->PreviousSharedButtons.Find(Button.Key) != INDEX_NONE) {
			MessageHandler->OnControllerButtonReleased(Button.Value, Index, false);
			Joycon->PreviousSharedButtons.Remove(Button.Key);
		}
	}

	uint8_t* StickAxis = Packet + 9;
	uint16_t uStickY = StickAxis[0] | ((StickAxis[1] & 0xF) << 8);
	uint16_t uStickX = (StickAxis[1] >> 4) | (StickAxis[2] << 4);

	UE_LOG(LogTemp, Warning, TEXT("Y: %i | X: %i"), uStickY, uStickX);

	float StickY = uStickY;
	float StickX = uStickX;

	float NormalisedY = (StickY - 3410) / (850 - 3410);
	float NormalisedX = (StickX - 2890) / (735 - 2890);

	NormalisedY = FMath::RoundFromZero((NormalisedY * 100)) / 100;
	NormalisedX = FMath::RoundFromZero((NormalisedX * 100)) / 100;
	NormalisedY = FMath::Clamp(NormalisedY, 0.0f, 1.0f);
	NormalisedX = FMath::Clamp(NormalisedX, 0.0f, 1.0f);

	MessageHandler->OnControllerAnalog(FRightJoyconButton::ThumbstickAxisX.GetFName(), Index, NormalisedX);
	MessageHandler->OnControllerAnalog(FRightJoyconButton::ThumbstickAxisY.GetFName(), Index, NormalisedY);

	return true;
}

bool FJoyconInputDevice::IsPressed(int Input, int Button)
{
	return (Button & Input) != 0;
}

bool FJoyconInputDevice::IsReleased(int Input, int Button)
{
	return false;
}

void FJoyconInputDevice::SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	this->MessageHandler = InMessageHandler;
}

bool FJoyconInputDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return true;
}

void FJoyconInputDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{

}

void FJoyconInputDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values)
{

}

FJoyconInputDevice::~FJoyconInputDevice()
{

}