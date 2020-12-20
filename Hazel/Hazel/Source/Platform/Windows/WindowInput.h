#pragma once

#include "Hazel/Input.h"

namespace Hazel {

class HWindowInput : public HInput
{

protected:

	virtual bool IsKeyPressedImpl(int Keycode) override;

	virtual bool IsMouseButtonPressedImpl(int Button) override;
	virtual std::pair<float, float> GetMousePositionImpl() override;
};


};
