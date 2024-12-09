#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Rage
{
	class RAGE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning{ true };
	};

	// To be defined in client appplication
	Application* CreateApplication();
}

