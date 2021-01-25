#include "Hzpch.h"
#include "LayerStack.h"

namespace Hazel {

HLayerStack::HLayerStack()
{
}

HLayerStack::~HLayerStack()
{
	for (const HLayer* Layer : Layers)
	{
		delete  Layer;
	}
}

void HLayerStack::PushLayer(HLayer* Layer)
{
	Layers.emplace(Layers.begin() + LayerInsertIdx, Layer);
	LayerInsertIdx++;
}

void HLayerStack::PopLayer(HLayer* Layer)
{
	auto It = std::find(begin(), end(), Layer);
	if (It != end())
	{
		Layers.erase(It);
		LayerInsertIdx--;
	}
}

void HLayerStack::PushOverlay(HLayer* Layer)
{
	Layers.emplace_back(Layer);
}

void HLayerStack::PopOverlay(HLayer* Layer)
{
	auto It = std::find(begin(), end(), Layer);
	if (It != end())
	{
		Layers.erase(It);
	}
}

};