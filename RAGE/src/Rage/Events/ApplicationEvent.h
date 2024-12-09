#pragma once

#include "Events/Event.h"

namespace Rage
{
	class RAGE_API WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(float width, float height)
			:m_Width(width), m_Height(height)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizedEvent: " << "( " << m_Width << ", " << m_Height << " )";
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(+EventCategory::Application)

	private:
		float m_Height{}, m_Width{};
	};

	class RAGE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{
		}

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(+EventCategory::Application)
	};
}