#include "Hzpch.h"
#include "OpenGLShader.h"

#include "fstream"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Hazel {

	static GLenum ShaderTypeFromString(const std::string& Type)
	{
		if (Type == "Vertex")
		{
			return  GL_VERTEX_SHADER;
		}
		if (Type == "Fragment" || Type == "Pixel")
		{
			return GL_FRAGMENT_SHADER;
		}

		HZ_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}
	
	OpenGLShader::OpenGLShader(const std::string& FilePath)
	{
		std::string ShaderSource = ReadFile(FilePath);
		auto ShaderSources = PreProcess(ShaderSource);
		Compile(ShaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string & VertexSrc, const std::string & FragmentSrc)
	{
		std::unordered_map<GLenum, std::string> ShaderSources;
		ShaderSources[GL_VERTEX_SHADER] = VertexSrc;
		ShaderSources[GL_FRAGMENT_SHADER] = FragmentSrc;

		Compile(ShaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(0);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& Name, const int Value)
	{
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniform1i(Location, Value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& Name, const float Value)
	{
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniform1f(Location, Value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& Name, const glm::vec2& Values)
	{
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniform2f(Location, Values.x, Values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& Name, const glm::vec3& Values)
	{
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniform3f(Location, Values.x, Values.y, Values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& Name, const glm::vec4& Values)
	{
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniform4f(Location, Values.x, Values.y, Values.z, Values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& MatrixName, const glm::mat3& Matrix)
	{
		GLint Location = glGetUniformLocation(RendererID, MatrixName.c_str());
		glUniformMatrix3fv(Location, 1, GL_FALSE, glm::value_ptr(Matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& MatrixName, const glm::mat4& Matrix)
	{
		GLint Location = glGetUniformLocation(RendererID, MatrixName.c_str());
		glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Matrix));
	}

	std::string OpenGLShader::ReadFile(const std::string& FilePath)
	{
		std::string Result;
		std::ifstream In(FilePath, std::ios::in | std::ios::binary);
		if (In)
		{
			In.seekg(0, std::ios::end);
			Result.resize(In.tellg());
			In.seekg(0, std::ios::beg);
			In.read(&Result[0], Result.size());
			In.close();
		}
		else
		{
			HZ_CORE_ERROR("Could not open file '{0}'", FilePath);
		}

		return Result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& Source)
	{
		std::unordered_map<GLenum, std::string> ShaderSourceMap;

		const char* TypeToken = "#type";
		const size_t TypeTokenLength = strlen(TypeToken);
		size_t Pos = Source.find(TypeToken, 0);
		while (Pos != std::string::npos)
		{
			const size_t Eol = Source.find_first_of("\r\n", Pos);
			HZ_CORE_ASSERT(Eol != std::string::npos, "Syntax error");
			const size_t Begin = Pos + TypeTokenLength + 1;
			const std::string Type = Source.substr(Begin, Eol - Begin);
			HZ_CORE_ASSERT(Type == "Vertex" || Type == "Fragment" || Type == "Pixel", "Invalid shader type specifier");

			const size_t NextLinePos = Source.find_first_not_of("\r\n", Eol);
			Pos = Source.find(TypeToken, NextLinePos);
			ShaderSourceMap[ShaderTypeFromString(Type)] = Source.substr(NextLinePos,
				Pos - (NextLinePos == std::string::npos ? Source.size() - 1 : NextLinePos));
		}

		return ShaderSourceMap;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& ShaderSourceMap)
	{
		HZ_CORE_ASSERT(ShaderSourceMap.size(), "ShaderSourceMap is empty!");
		
		GLuint Program = glCreateProgram();
		std::vector<GLenum> GLShaderIds;
		GLShaderIds.reserve(ShaderSourceMap.size());
		for (const auto& Pair : ShaderSourceMap)
		{
			GLenum Type = Pair.first;
			const std::string& Source = Pair.second;

			const GLuint Shader = glCreateShader(Type);

			// Send the vertex OpenGLShader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCStr = Source.c_str();
			glShaderSource(Shader, 1, &sourceCStr, 0);

			// Compile the vertex Shader
			glCompileShader(Shader);

			GLint isCompiled = 0;
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the Shader anymore.
				glDeleteShader(Shader);

				HZ_CORE_ERROR("{0}", infoLog.data());
				HZ_CORE_ASSERT(false, "Shader compilation failure!")

				break;
			}
			glAttachShader(Program, Shader);
			GLShaderIds.push_back(Shader);
		}
		
		// Link our program
		glLinkProgram(Program);

		// Note the different functions here: glGetProgram* instead of glGetOpenGLShader*.
		GLint isLinked = 0;
		glGetProgramiv(Program, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(Program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(Program);
			// Don't leak OpenGLShaders either.

			for (const auto ShaderId : GLShaderIds)
			{
				glDeleteShader(ShaderId);
			}
			
			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "OpenGLShader linking failure!")

			return;
		}

		// Always detach OpenGLShaders after a successful link.
		for (const auto ShaderId : GLShaderIds)
		{
			glDetachShader(Program, ShaderId);
		}

		RendererID = Program;
	}
}
