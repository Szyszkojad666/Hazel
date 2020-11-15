#pragma once

#include "Hazel/Core.h"
#include "Hazel/Layer.h"
#include "Hazel/Event/AppEvent.h"
#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Event/MouseEvent.h"

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

	bool OnMouseButtonPressed(HMouseButtonPressedEvent& Event);
	bool OnMouseButtonReleased(HMouseButtonReleasedEvent& Event);
	bool OnMouseMoved(HMouseMovedEvent& Event);
	bool OnMouseScrolled(HMouseScrolledEvent& Event);
	bool OnKeyPressed(HKeyPressedEvent& Event);
	bool OnKeyReleased(HKeyReleasedEvent& Event);
	bool OnKeyTyped(HKeyTypedEvent& Event);
	bool OnWindowResised(HWindowResizeEvent& Event);

private:

	float PreviousTime = 0.f;
};
}