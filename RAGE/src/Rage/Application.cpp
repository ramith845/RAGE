#include "rgpch.h"
#include "Application.h"
#include "ApplicationEvent.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#include "Log.h"

namespace Rage
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizedEvent event{ 1080, 1920 };
		if (event.IsInCategory(EventCategory::Application))
		{
			RG_CORE_TRACE(event.ToString());
		}
		while (true)
		{

		}
	}
}