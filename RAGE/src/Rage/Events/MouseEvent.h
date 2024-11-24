#pragma once

#include "Event.h"

namespace Rage {
	class RAGE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float X, float Y)
			: m_X(X)
			, m_Y(Y)
		{
		}

		inline float GetX() const { return m_X; }
		inline float GetY() const { return m_Y; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: ( " << m_X << ", " << m_Y << " )";
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseMove)
			EVENT_CLASS_CATEGORY(+EventCategory::Input | +EventCategory::Mouse)

	private:
		float m_X{}, m_Y{};

	};

	class RAGE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float XOffset, float YOffset)
			: m_XOffset(XOffset)
			, m_YOffset(YOffset)
		{
		}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffsetY() const { return m_YOffset; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: ( " << m_XOffset << ", " << m_YOffset << " )";
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseScroll)
			EVENT_CLASS_CATEGORY(+EventCategory::Input | +EventCategory::Mouse)

	private:
		float m_XOffset{}, m_YOffset{};

	};

	class RAGE_API MouseButtonEvent : public Event
	{
	public:
		inline int GetButton() const { return m_Button; }
		// using overloded op to convert each category(to int underlying_type_t),
		// can use enum instead of enum class makes it implicitly int
		// but no scoping and safe comparision of same enum type
		EVENT_CLASS_CATEGORY(+EventCategory::Input | +EventCategory::MouseButton)

	protected:
		MouseButtonEvent(int button)
			: m_Button(button)
		{
		}

		int m_Button{};
	};

	class RAGE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPress)
	};

	class RAGE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonRelasedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonRelease)
	};
} // namespace Rage