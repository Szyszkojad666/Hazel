#pragma once
#include <string>

#include "glm/glm.hpp"
#include "Hazel/Renderer/Shader.h"

// TODO:: REMOVE
typedef unsigned int GLenum;

namespace Hazel {

	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const std::string& FilePath);
		OpenGLShader(const std::string& VertexSrc, const std::string& FragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string& Name, const int Value);

		void UploadUniformFloat(const std::string& Name, const float Value);
		void UploadUniformFloat2(const std::string& Name, const glm::vec2& Values);
		void UploadUniformFloat3(const std::string& Name, const glm::vec3& Values);
		void UploadUniformFloat4(const std::string& Name, const glm::vec4& Values);

		void UploadUniformMat3(const std::string& MatrixName, const glm::mat3& Matrix);
		void UploadUniformMat4(const std::string& MatrixName, const glm::mat4& Matrix);

	private:

		std::string ReadFile(const std::string& FilePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& Source);
		void Compile(const std::unordered_map<GLenum, std::string>& ShaderSourceMap);

	private:

		uint32_t RendererID;
	};
}
