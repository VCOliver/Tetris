#pragma once

#include "pch.h"
#include "event.hpp"

class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: event(event)
		{
		}
		
		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (event.GetCategoryFlags() == T::GetStaticCategoryFlags())
			{
				event.Handled |= func(static_cast<T&>(event));
				return true;
			}
			return false;
		}

		template<typename T, typename F>
		bool notify(const F& func)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				event.Handled |= func(static_cast<T&>(event));
				return true;
			}
			return false;
		}
	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}