#pragma once

#include <string>
#include "glm/glm.hpp"

namespace Hazel {

class Shader
{
public:
	
	Shader(const std::string& VertexSrc, const std::string& FragmentSrc);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void UploadUniformMat4(const std::string& MatrixName, const glm::mat4& Matrix);

private:

	uint32_t RendererID;
};
}