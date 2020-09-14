#include "Application.h"
#include "Event/AppEvent.h"
#include "Log.h"

namespace Hazel {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent Resize(1200, 720);
		HZ_CORE_TRACE(Resize);

		while (true)
		{

		}
	}
}


