#include "Hzpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform\OpenGL\OpenGLShader.h"

namespace Hazel {
	
Shader* Shader::Create(const std::string& FilePath)
{
	switch (Renderer::GetRendererAPI())
	{
	case RendererAPI::ERendererAPI::None:	HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
	case RendererAPI::ERendererAPI::OpenGL:	return new OpenGLShader(FilePath);
	}

	HZ_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

Shader* Shader::Create(const std::string& VertexSrc, const std::string& FragmentSrc)
{
	switch (Renderer::GetRendererAPI())
	{
	case RendererAPI::ERendererAPI::None:	HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
	case RendererAPI::ERendererAPI::OpenGL:	return new OpenGLShader(VertexSrc, FragmentSrc);
	}

	HZ_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

}
