#pragma once

#include "Hazel/Core.h"

namespace Hazel {

class HAZEL_API HInput
{
public:
		
	inline static bool IsKeyPressed(int Keycode) { return InputInstance->IsKeyPressedImpl(Keycode); }

	inline static bool IsMouseButtonPressed(int Button) { return InputInstance->IsMouseButtonPressedImpl(Button); }
	inline static std::pair<float, float> GetMousePosition() { return InputInstance->GetMousePositionImpl(); }

protected:
	
	virtual bool IsKeyPressedImpl(int Keycode) = 0;

	virtual bool IsMouseButtonPressedImpl(int Button) = 0;
	virtual std::pair<float, float> GetMousePositionImpl() = 0;

private:
	
	static HInput* InputInstance;

};

};