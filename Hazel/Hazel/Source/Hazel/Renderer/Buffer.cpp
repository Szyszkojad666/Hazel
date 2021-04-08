#include "Hzpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Hazel {

VertexBuffer* VertexBuffer::Create(float * Vertices, uint32_t Size)
{
	switch (Renderer::GetRendererAPI())
	{
		case RendererAPI::ERendererAPI::None:	HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::ERendererAPI::OpenGL:	return new OpenGLVertexBuffer(Vertices, Size);
	}


	HZ_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* Indices, uint32_t IdxCount)
{
	switch (Renderer::GetRendererAPI())
	{
		case RendererAPI::ERendererAPI::None:	HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::ERendererAPI::OpenGL:	return new OpenGLIndexBuffer(Indices, IdxCount);
	}

	HZ_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

uint32_t BufferElement::GetComponentCount() const
{
	{
		switch (Type)
		{
		case EShaderDataType::Float:	return 1;
		case EShaderDataType::Float2:	return 2;
		case EShaderDataType::Float3:	return 3;
		case EShaderDataType::Float4:	return 4;
		case EShaderDataType::Mat3:		return 3 * 3;
		case EShaderDataType::Mat4:		return 4 * 4;
		case EShaderDataType::Int:		return 1;
		case EShaderDataType::Int2:		return 2;
		case EShaderDataType::Int3:		return 3;
		case EShaderDataType::Int4:		return 4;
		case EShaderDataType::Bool:		return 1;
		}

		HZ_CORE_ASSERT(false, "Unkown EShaderDataType!");
		return 0;
	}
}

void BufferLayout::CalculateOffsetAndStride()
{
	uint32_t Offset = 0;
	Stride = 0;
	for (auto& Element : Elements)
	{
		Element.Offset = Offset;
		Offset += Element.Size;
		Stride += Element.Size;
	}
}

} 