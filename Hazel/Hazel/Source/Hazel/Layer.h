#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Hazel/Core/TimeStep.h"

class HEvent;

// This is meant to be subclassed
namespace Hazel {

class HAZEL_API HLayer
{
public:

	HLayer(const std::string& Name = "Layer");
	virtual ~HLayer();

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(FTimeStep TimeStep) {}
	virtual void OnImGuiRender() {}
	virtual void OnEvent(HEvent& Event) {}

	inline const std::string& GetName() const { return DebugName; }

protected:

	std::string DebugName;
};

}