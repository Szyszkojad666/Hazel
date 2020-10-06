#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Hazel {

class HAZEL_API HLayerStack
{
public:

	HLayerStack();
	~HLayerStack();

	void PushLayer(HLayer* Layer);
	void PopLayer(HLayer* Layer);
	void PushOverlay(HLayer* Layer);
	void PopOverlay(HLayer* Layer);

	std::vector<HLayer*>::iterator begin() { return Layers.begin(); }
	std::vector<HLayer*>::iterator end() { return Layers.end(); }

private:

	std::vector<HLayer*> Layers;
	std::vector<HLayer*>::iterator LayerInsert;
};

};