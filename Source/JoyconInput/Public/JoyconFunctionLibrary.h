#pragma once

#include "CoreMinimal.h"

#include "hidapi.h"

#include "Joycon.h"
#include "JoyconInput.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "JoyconFunctionLibrary.generated.h"

UCLASS()
class JOYCONINPUT_API UJoyconFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/*
	Connects to the Joycon devices.
	*/
	UFUNCTION(BlueprintCallable, Category = "JoyconInput")
	static void ConnectJoycons(bool& Success, int32& Count);

	/*
	Disconnects from the Joycon devices.
	*/
	UFUNCTION(BlueprintCallable, Category = "JoyconInput")
	static void DisconnectJoycons(bool& Success);

	/*
	Returns a Joycon from the given Id.
	*/
	UFUNCTION(BlueprintPure, Category = "JoyconInput")
	static void GetJoycon(int32 ControllerId, UJoycon*& Joycon);

	/*
	Returns all connected Joycons.
	*/
	UFUNCTION(BlueprintPure, Category = "JoyconInput")
	static void GetJoycons(TArray<UJoycon*>& Joycons);
};
