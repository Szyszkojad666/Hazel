#include "Hzpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel {

VertexArray* VertexArray::Create()
{
	switch (Renderer::GetRendererAPI())
	{
	case RendererAPI::ERendererAPI::None:	HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
	case RendererAPI::ERendererAPI::OpenGL:	return new OpenGLVertexArray();
	}

	HZ_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

}