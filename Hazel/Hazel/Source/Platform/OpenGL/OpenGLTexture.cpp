#include "Hzpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include "glad/glad.h"

namespace Hazel
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& Path)
        : CachedPath(Path)
    {
        int InWidth, InHeight, InChannels;
        stbi_uc* Data = stbi_load(Path.c_str(), &InWidth, &InHeight, &InChannels, 0);
        HZ_CORE_ASSERT(Data, "Failed To Load Image")
        m_Width = InWidth;
        m_Height = InHeight;

        GLenum InternalFormat = 0;
        GLenum DataFormat = 0;

        if (InChannels == 4)
        {
            InternalFormat = GL_RGBA8;
            DataFormat = GL_RGBA;
        }
        else if (InChannels == 3)
        {
            InternalFormat = GL_RGB8;
            DataFormat = GL_RGB;
        }

        HZ_CORE_ASSERT(InternalFormat & DataFormat, "Format not supported");
        
        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, InternalFormat, m_Width, m_Height);
        
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, DataFormat, GL_UNSIGNED_BYTE, Data);
        
        stbi_image_free(Data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t Slot) const
    {
        glBindTextureUnit(Slot, m_RendererID);
    }
}
