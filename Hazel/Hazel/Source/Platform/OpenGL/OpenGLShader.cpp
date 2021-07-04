#include "Hzpch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Hazel {

	OpenGLShader::OpenGLShader(const std::string & VertexSrc, const std::string & FragmentSrc)
	{
		// Create an empty vertex OpenGLShader handle
		GLuint vertexOpenGLShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex OpenGLShader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = VertexSrc.c_str();
		glShaderSource(vertexOpenGLShader, 1, &source, 0);

		// Compile the vertex Shader
		glCompileShader(vertexOpenGLShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexOpenGLShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexOpenGLShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexOpenGLShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the Shader anymore.
			glDeleteShader(vertexOpenGLShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Vertex OpenGLShader compilation failure!");

			return;
		}

		// Create an empty fragment OpenGLShader handle
		GLuint fragmentOpenGLShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment OpenGLShader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = FragmentSrc.c_str();
		glShaderSource(fragmentOpenGLShader, 1, &source, 0);

		// Compile the fragment OpenGLShader
		glCompileShader(fragmentOpenGLShader);

		glGetShaderiv(fragmentOpenGLShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentOpenGLShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentOpenGLShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the OpenGLShader anymore.
			glDeleteShader(fragmentOpenGLShader);
			// Either of them. Don't leak OpenGLShaders.
			glDeleteShader(vertexOpenGLShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Fragment OpenGLShader compilation failure!");

			return;
		}

		// Vertex and fragment OpenGLShaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		RendererID = glCreateProgram();
		GLuint program = RendererID;

		// Attach our OpenGLShaders to our program
		glAttachShader(program, vertexOpenGLShader);
		glAttachShader(program, fragmentOpenGLShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetOpenGLShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak OpenGLShaders either.
			glDeleteShader(vertexOpenGLShader);
			glDeleteShader(fragmentOpenGLShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "OpenGLShader linking failure!");

			return;
		}

		// Always detach OpenGLShaders after a successful link.
		glDetachShader(program, vertexOpenGLShader);
		glDetachShader(program, fragmentOpenGLShader);
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

}
