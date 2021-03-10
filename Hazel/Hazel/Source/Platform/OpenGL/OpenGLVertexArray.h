#pragma once

#include <memory>
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Buffer.h"

namespace Hazel {

class OpenGLVertexArray : public VertexArray
{
public:

	OpenGLVertexArray();
	virtual ~OpenGLVertexArray();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
	virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

	inline virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return VertexBuffers; }
	inline virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return IndexBufferPtr; }

private:

	uint32_t RendererID;
	std::vector<std::shared_ptr<VertexBuffer>> VertexBuffers;
	std::shared_ptr<IndexBuffer> IndexBufferPtr;
};

}