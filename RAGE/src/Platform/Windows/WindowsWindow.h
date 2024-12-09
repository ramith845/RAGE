#pragma once

#include "Window.h"
#include "GLFW/glfw3.h"

namespace Rage
{
	class RAGE_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& wp);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		// Window attributes
		void SetEventCBFn(const EventCBfn& callback) override;
		void SetVSync(bool enable) override;
		bool IsVSync() const override;


		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;

			bool VSync;

			EventCBfn EventCB;
		};
	private:
		virtual void Init(const WindowProps& wp);
		virtual void Shutdown();
	private:

		WindowData m_Data;
		GLFWwindow* m_Window;
	};

	
}