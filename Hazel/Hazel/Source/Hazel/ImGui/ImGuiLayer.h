#pragma once

#include "Hazel/Core.h"
#include "Hazel/Layer.h"

namespace Hazel {

class HAZEL_API ImGuiLayer : public HLayer
{
public:
	ImGuiLayer();
	~ImGuiLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(HEvent& Event);


private:

	float PreviousTime = 0.f;
};
}