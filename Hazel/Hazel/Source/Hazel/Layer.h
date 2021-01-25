#pragma once

#include "Core.h"
#include "Event/Event.h"

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
	virtual void OnUpdate() {}
	virtual void OnImGuiRender() {}
	virtual void OnEvent(HEvent& Event) {}

	inline const std::string& GetName() const { return DebugName; }

protected:

	std::string DebugName;
};

}