#pragma once

#include <string>

namespace Hazel {

class Shader
{
public:
	
	virtual ~Shader() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	//virtual void UploadUniformBuffer();

	static Shader* Create(const std::string& FilePath);
	static Shader* Create(const std::string& VertexSrc, const std::string& FragmentSrc);
};
}