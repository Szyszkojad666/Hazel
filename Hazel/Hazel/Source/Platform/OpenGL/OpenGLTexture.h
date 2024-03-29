﻿#pragma once

#include "Hazel/Renderer/Texture.h"

namespace Hazel
{
    class OpenGLTexture2D : public Texture2D
    {
    public:

        OpenGLTexture2D(const std::string& Path);
        virtual ~OpenGLTexture2D() override;

        virtual uint32_t GetWidth() const override { return m_Width; }
        virtual uint32_t GetHeight() const override { return m_Height; }
        
        virtual void Bind(uint32_t Slot = 0) const override;

    private:
        
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_RendererID;

        std::string CachedPath;
    };    
}

