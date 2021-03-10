#include "Hzpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel {

VertexArray* VertexArray::Create()
{
	switch (Renderer::GetRendererAPI())
	{
	case ERendererAPI::None:	HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
	case ERendererAPI::OpenGL:	return new OpenGLVertexArray();
	}

	HZ_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

}