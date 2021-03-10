#include "Hzpch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Hazel {

static GLenum ShaderDataTypeToOpenGLBaseType(EShaderDataType Type)
{
	switch (Type)
	{
	case EShaderDataType::Float:	return GL_FLOAT;
	case EShaderDataType::Float2:	return GL_FLOAT;
	case EShaderDataType::Float3:	return GL_FLOAT;
	case EShaderDataType::Float4:	return GL_FLOAT;
	case EShaderDataType::Mat3:		return GL_FLOAT;
	case EShaderDataType::Mat4:		return GL_FLOAT;
	case EShaderDataType::Int:		return GL_INT;
	case EShaderDataType::Int2:		return GL_INT;
	case EShaderDataType::Int3:		return GL_INT;
	case EShaderDataType::Int4:		return GL_INT;
	case EShaderDataType::Bool:		return GL_BOOL;
	}

	HZ_CORE_ASSERT(false, "Unkown EShaderDataType!");
	return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
	glCreateVertexArrays(1, &RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteVertexArrays(1, &RendererID);
}

void OpenGLVertexArray::Bind() const
{
	glBindVertexArray(RendererID);
}

void OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(RendererID);
	vertexBuffer->Bind();

	HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!")

	uint32_t index = 0;
	const BufferLayout& Layout = vertexBuffer->GetLayout();
	for (const auto& Element : Layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index
			, Element.GetComponentCount()
			, ShaderDataTypeToOpenGLBaseType(Element.Type)
			, Element.bNormalized ? GL_TRUE : GL_FALSE
			, Layout.GetStride()
			, (const void*)Element.Offset);

		index++;
	}

	VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(RendererID);
	indexBuffer->Bind();

	IndexBufferPtr = indexBuffer;
}

}