#pragma once
#include "rgpch.h"

#include "Events/Event.h"
#include "Core.h"

namespace Rage
{
	struct RAGE_API WindowProps
	{
		std::string Title{ "" };
		unsigned int Width{}, Height{};

		WindowProps(std::string title = "Rage",
			unsigned int width = 1920,
			unsigned int height = 1080)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class RAGE_API Window
	{
	public:
		using EventCBfn = std::function<void(Event&)>;
		//virtual ~Window();

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		
		// Window attributes
		virtual void SetEventCBFn(const EventCBfn& callback) = 0;
		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& wp = WindowProps());
	};
}