#pragma once

#include "RendererAPI.h"

namespace Hazel {

class RenderCommand
{

public:

	inline static void Init()
	{
		RendererAPIptr->Init();
	}
	
	inline static void SetClearColor(const glm::vec4& Color)
	{
		if (RendererAPIptr)
		{
			RendererAPIptr->SetClearColor(Color);
		}
	}
	
	inline static void Clear()
	{
		if (RendererAPIptr)
		{
			RendererAPIptr->Clear();
		}
	}

	inline static void DrawIndexed(const std::shared_ptr<VertexArray>& InVertexArray)
	{
		if (RendererAPIptr)
		{
			RendererAPIptr->DrawIndexed(InVertexArray);
		}
	}

private:

	static RendererAPI* RendererAPIptr;	
};




}