#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel {

class OpenGLVertexBuffer : public VertexBuffer
{
public:

	OpenGLVertexBuffer(float * Vertices, uint32_t Size);
	virtual ~OpenGLVertexBuffer();

	virtual void Bind() const override;
	virtual void UnBind() const override;

private:

	uint32_t RendererID;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:

	OpenGLIndexBuffer(uint32_t* Indices, uint32_t IdxCount);
	virtual ~OpenGLIndexBuffer();

	virtual void Bind() const override;
	virtual void UnBind() const override;

	virtual uint32_t GetCount() const override { return Count; }
private:

	uint32_t RendererID;
	uint32_t Count;
};

}