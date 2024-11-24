#pragma once

#include "Event.h"

namespace Rage {
	class RAGE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() { return m_KeyCode; }
		// using overloded op to convert each category(to int underlying_type_t), 
		// can use enum instead of enum class makes it implicitly int 
		// but no scoping and safe comparision of same enum type
		EVENT_CLASS_CATEGORY(+EventCategory::Input | +EventCategory::Keyboard)

	protected:
		KeyEvent(int KeyCode)
			: m_KeyCode(KeyCode)
		{
		}

		int m_KeyCode{};

	};

	class RAGE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int KeyCode, int RepeatCount)
			: KeyEvent(KeyCode), m_RepeatCount(RepeatCount)
		{
		}


		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << ", repeated: " << m_RepeatCount;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPress)

	private:
		int m_RepeatCount{};
	};

	class RAGE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int KeyCode, int RepeatCount)
			: KeyEvent(KeyCode), m_RepeatCount(RepeatCount)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode << ", repeated: " << m_RepeatCount;
			return ss.str();
		}

		inline int GetRepeatCount() const { return m_RepeatCount; }
		EVENT_CLASS_TYPE(KeyRelease)

	private:
		int m_RepeatCount{};
	};
}