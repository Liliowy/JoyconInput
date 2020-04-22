#pragma once

#include "InputCoreTypes.h"
#include "InputDevice/Public/IInputDeviceModule.h"
#include "ModuleManager.h"

class IJoyconInputModule : public IInputDeviceModule
{
public:
	static inline IJoyconInputModule& Get() {
		return FModuleManager::LoadModuleChecked<IJoyconInputModule>("JoyconInput");
	}

	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("JoyconInput");
	}
};