#pragma once

#include <string>

namespace Hazel {

class Shader
{
public:
	
	Shader(const std::string& VertexSrc, const std::string& FragmentSrc);
	~Shader();

	void Bind() const;
	void Unbind() const;

private:

	uint32_t RendererID;
};
}