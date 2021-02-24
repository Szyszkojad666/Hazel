#include "Hzpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {

VertexBuffer* VertexBuffer::Create(float * Vertices, uint32_t Size)
{
	switch (Renderer::GetRendererAPI())
	{
		case ERendererAPI::None:	HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case ERendererAPI::OpenGL:	return new OpenGLVertexBuffer(Vertices, Size);
	}


	HZ_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* Indices, uint32_t IdxCount)
{
	switch (Renderer::GetRendererAPI())
	{
		case ERendererAPI::None:	HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case ERendererAPI::OpenGL:	return new OpenGLIndexBuffer(Indices, IdxCount);
	}


	HZ_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

} 