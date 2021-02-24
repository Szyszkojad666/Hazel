#pragma once

namespace Hazel {

enum class ERendererAPI
{
	None = 0, OpenGL =1
};

class Renderer
{

public:

	inline static ERendererAPI GetRendererAPI() { return RendererAPI; }
	
private:

	static ERendererAPI RendererAPI;
};
}