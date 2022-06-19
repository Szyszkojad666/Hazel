#include "Hzpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Hazel
{
   TRef<Texture2D> Texture2D::Create(const std::string& Path)
    {
       switch (Renderer::GetRendererAPI())
       {
       case RendererAPI::ERendererAPI::None:	HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
       case RendererAPI::ERendererAPI::OpenGL:	return std::make_shared<OpenGLTexture2D>(Path);
       }
       
       HZ_CORE_ASSERT(false, "Unknown RendererAPI")
       return nullptr;
    }
}
