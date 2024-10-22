#pragma once

#include "Core.h"

namespace Rage
{
	class RAGE_API Application
	{
	public:
		Application();
		virtual ~Application();
	
		void Run();
	};

	// To be defined in client appplication
	Application* CreateApplication();
}

