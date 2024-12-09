#pragma once

#include "Core.h"
#include "Log.h"

namespace Rage {
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMove,
		KeyPress, KeyRelease,
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
	};

	enum class EventCategory
	{
		None = 0,
		Application = BIT(0),
		Input = BIT(1),
		Keyboard = BIT(2),
		Mouse = BIT(3),
		MouseButton = BIT(4),
	};

	class RAGE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetEventCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) const
		{
			return static_cast<int>(category) & GetEventCategoryFlags();
		}

	protected:
		bool m_Handled{ false };
	};


#define EVENT_CLASS_TYPE(type) static  EventType   GetStaticType() { return EventType::##type; }\
							   virtual EventType   GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategoryFlags() const override { return category; }

	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{

		}

		template <typename T>
		bool Dispatch(EventFn<T> function)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = function(*dynamic_cast<T*>(&m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline constexpr auto operator+(EventCategory ec) noexcept
	{
		return static_cast<std::underlying_type_t<EventCategory>>(ec);
	}
	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.ToString();
	}

	template<typename T>
	struct fmt::formatter<T, std::enable_if_t<std::is_base_of<Event, T>::value, char>>
		: fmt::formatter<std::string>
	{
		auto format(const T& event, fmt::format_context& ctx) const -> decltype(ctx.out())
		{
			return fmt::format_to(ctx.out(), "{}", event.ToString());
		}
	};

	template <typename... T>
	std::string StringFromArgs(fmt::format_string<T...> fmt, T&&... args) {
		return fmt::format(fmt, std::forward<T>(args)...);
	}

}