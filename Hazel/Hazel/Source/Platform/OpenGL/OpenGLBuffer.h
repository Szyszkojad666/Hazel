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

 	inline virtual void SetLayout(const BufferLayout& BufferLayout) override { Layout = BufferLayout; }
	inline virtual const BufferLayout& GetLayout() const override { return Layout; }

private:

	uint32_t RendererID;
	BufferLayout Layout;
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