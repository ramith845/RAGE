#include "rgpch.h"
#include "WindowsWindow.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace Rage
{
	static bool s_GLFW_Initialized = false;

	Window* Window::Create(const WindowProps& wp)
	{
		return new WindowsWindow(wp);
	}

	WindowsWindow::WindowsWindow(const WindowProps& wp)
	{
		Init(wp);
	}

	void WindowsWindow::Init(const WindowProps& wp)
	{
		m_Data.Width = wp.Width;
		m_Data.Height = wp.Height;
		m_Data.Title = wp.Title;
		RG_CORE_INFO("Create window {0} {1} {2}", wp.Title, wp.Width, wp.Height);

		if (!s_GLFW_Initialized)
		{
			int success = glfwInit();
			RG_CORE_ASSERT(success, "Couldn't initialize GLFW!")
			{
				s_GLFW_Initialized = true;
			}
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data->Width = width;
				data->Height = height;
				WindowResizedEvent event{ static_cast<float>(width), static_cast<float>(height) };
				data->EventCB(event);
			}
		);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				WindowCloseEvent event;
				data->EventCB(event);
			}
		);

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data->EventCB(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data->EventCB(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data->EventCB(event);
					break;
				}
				default:
				{
					RG_CORE_ERROR("Event type not recognized!");
					break;
				}
				}
			}
		);

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data->EventCB(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data->EventCB(event);
					break;
				}
				default:
				{
					RG_CORE_ERROR("Event type not recognized!");
					break;
				}
				}
			}
		);

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				MouseScrolledEvent event{ static_cast<float>(xOffset), static_cast<float>(yOffset) };
				data->EventCB(event);
			}
		);

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				MouseMovedEvent event{ static_cast<float>(xPos), static_cast<float>(yPos) };
				data->EventCB(event);
			}
		);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	unsigned int WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}

	unsigned int WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}

	bool WindowsWindow::IsVSync() const { return m_Data.VSync; }

	void WindowsWindow::SetEventCBFn(const EventCBfn& callback)
	{
		m_Data.EventCB = callback;
	}

	void WindowsWindow::OnUpdate()
	{
		glClearColor(1.f, 1.f, 0.5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
		glfwWindowShouldClose(m_Window);
	}

	void WindowsWindow::SetVSync(bool enable)
	{
		if (enable)
		{
			glfwSwapInterval(1);
		}
		else
			glfwSwapInterval(0);
		m_Data.VSync = enable;
	}

}