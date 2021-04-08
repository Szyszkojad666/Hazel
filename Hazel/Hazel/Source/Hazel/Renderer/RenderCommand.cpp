#include "Hzpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel {

	RendererAPI* RenderCommand::RendererAPIptr = new OpenGLRendererAPI;

}