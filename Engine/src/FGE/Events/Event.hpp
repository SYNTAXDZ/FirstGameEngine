#pragma once

#include "../Core/Base.hpp"

#include <string>
#include <iostream>
#include <functional>
#include <sstream>
#include <utility>

namespace FGE {

    enum class EventType {

        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowMoved,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled

    };

    enum EventCategory {

        None                     = 0,
        EventCategoryApplication = BIT( 0 ),
        EventCategoryInput       = BIT( 1 ),
        EventCategoryKeyboard    = BIT( 2 ),
        EventCategoryMouse       = BIT( 3 ),
        EventCategoryMouseButton = BIT( 4 )

    };

// this macro i just a helper to impliment GetEventType() and Getname() in derived classes of Event class
#define EVENT_CLASS_TYPE( type ) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }


// This Macro Help us to Impliment GetCategoryFlags() on derived classes of Event class
#define EVENT_CLASS_CATEGORY( category ) virtual int GetCategoryFlags() const override { return category; }

    class Event {

    public:
        bool Handled = false;

        virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory( EventCategory category ) {

			return GetCategoryFlags() & category;
		
        }
        
    };

    class EventDispatcher {

	template<typename T>
	using EventFn = std::function<bool( T& )>;
	
    public:
		EventDispatcher( Event& event ) : m_Event( event ) {}

		template<typename T>
		bool Dispatch( EventFn<T> func ) {

			if( m_Event.GetEventType() == T::GetStaticType() ) {

				m_Event.Handled = func( *( T* )&m_Event );
				
                return true;
			
            }
			
            return false;
		
        }
	
    private:
		Event& m_Event;

	};

	inline std::ostream& operator<<( std::ostream& os, const Event& e ) {
		
        return os << e.ToString();
	
    }

}