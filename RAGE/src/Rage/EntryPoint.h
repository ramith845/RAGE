#pragma once

#ifdef RG_PLATFORM_WINDOWS
extern Rage::Application* Rage::CreateApplication();
int main(int argc, char** arv)
{
	Rage::Log::Init();
	RG_CLIENT_INFO("Baby Im up!");
	RG_CORE_ERROR("bad Bitch Habbahabba!");

	auto app{ Rage::CreateApplication() };
	app->Run();

	delete app;
	return 0;
}
#endif // RG_PLATFORM_WINDOWS