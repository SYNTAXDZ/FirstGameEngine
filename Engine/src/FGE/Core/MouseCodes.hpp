#pragma once

namespace FGE {
	
    typedef enum class MouseCode : uint16_t {
		// From glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,

		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
	} Mouse;
	
	inline std::ostream& operator<<( std::ostream& os, MouseCode mouseCode ) {
		
        os << static_cast<int32_t>( mouseCode );
		
        return os;
	
    }

}

#define FGE_MOUSE_BUTTON_0      ::FGE::Mouse::Button0
#define FGE_MOUSE_BUTTON_1      ::FGE::Mouse::Button1
#define FGE_MOUSE_BUTTON_2      ::FGE::Mouse::Button2
#define FGE_MOUSE_BUTTON_3      ::FGE::Mouse::Button3
#define FGE_MOUSE_BUTTON_4      ::FGE::Mouse::Button4
#define FGE_MOUSE_BUTTON_5      ::FGE::Mouse::Button5
#define FGE_MOUSE_BUTTON_6      ::FGE::Mouse::Button6
#define FGE_MOUSE_BUTTON_7      ::FGE::Mouse::Button7
#define FGE_MOUSE_BUTTON_LAST   ::FGE::Mouse::ButtonLast
#define FGE_MOUSE_BUTTON_LEFT   ::FGE::Mouse::ButtonLeft
#define FGE_MOUSE_BUTTON_RIGHT  ::FGE::Mouse::ButtonRight
#define FGE_MOUSE_BUTTON_MIDDLE ::FGE::Mouse::ButtonMiddle
