#pragma once

#ifdef RG_PLATFORM_WINDOWS
extern Rage::Application* Rage::CreateApplication();
int main()
{
	auto app{ Rage::CreateApplication()};
	app->Run();

	delete app;
	return 0;
}
#endif // RG_PLATFORM_WINDOWS