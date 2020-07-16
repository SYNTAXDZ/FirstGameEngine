#pragma once

namespace FGE {
	
    typedef enum class KeyCode : uint16_t {
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<( std::ostream& os, KeyCode keyCode ) {
		
        os << static_cast<int32_t>( keyCode );
		
        return os;
	
    }

}

// From glfw3.h
#define FGE_KEY_SPACE           ::FGE::Key::Space
#define FGE_KEY_APOSTROPHE      ::FGE::Key::Apostrophe    /* ' */
#define FGE_KEY_COMMA           ::FGE::Key::Comma         /* , */
#define FGE_KEY_MINUS           ::FGE::Key::Minus         /* - */
#define FGE_KEY_PERIOD          ::FGE::Key::Period        /* . */
#define FGE_KEY_SLASH           ::FGE::Key::Slash         /* / */
#define FGE_KEY_0               ::FGE::Key::D0
#define FGE_KEY_1               ::FGE::Key::D1
#define FGE_KEY_2               ::FGE::Key::D2
#define FGE_KEY_3               ::FGE::Key::D3
#define FGE_KEY_4               ::FGE::Key::D4
#define FGE_KEY_5               ::FGE::Key::D5
#define FGE_KEY_6               ::FGE::Key::D6
#define FGE_KEY_7               ::FGE::Key::D7
#define FGE_KEY_8               ::FGE::Key::D8
#define FGE_KEY_9               ::FGE::Key::D9
#define FGE_KEY_SEMICOLON       ::FGE::Key::Semicolon     /* ; */
#define FGE_KEY_EQUAL           ::FGE::Key::Equal         /* = */
#define FGE_KEY_A               ::FGE::Key::A
#define FGE_KEY_B               ::FGE::Key::B
#define FGE_KEY_C               ::FGE::Key::C
#define FGE_KEY_D               ::FGE::Key::D
#define FGE_KEY_E               ::FGE::Key::E
#define FGE_KEY_F               ::FGE::Key::F
#define FGE_KEY_G               ::FGE::Key::G
#define FGE_KEY_H               ::FGE::Key::H
#define FGE_KEY_I               ::FGE::Key::I
#define FGE_KEY_J               ::FGE::Key::J
#define FGE_KEY_K               ::FGE::Key::K
#define FGE_KEY_L               ::FGE::Key::L
#define FGE_KEY_M               ::FGE::Key::M
#define FGE_KEY_N               ::FGE::Key::N
#define FGE_KEY_O               ::FGE::Key::O
#define FGE_KEY_P               ::FGE::Key::P
#define FGE_KEY_Q               ::FGE::Key::Q
#define FGE_KEY_R               ::FGE::Key::R
#define FGE_KEY_S               ::FGE::Key::S
#define FGE_KEY_T               ::FGE::Key::T
#define FGE_KEY_U               ::FGE::Key::U
#define FGE_KEY_V               ::FGE::Key::V
#define FGE_KEY_W               ::FGE::Key::W
#define FGE_KEY_X               ::FGE::Key::X
#define FGE_KEY_Y               ::FGE::Key::Y
#define FGE_KEY_Z               ::FGE::Key::Z
#define FGE_KEY_LEFT_BRACKET    ::FGE::Key::LeftBracket   /* [ */
#define FGE_KEY_BACKSLASH       ::FGE::Key::Backslash     /* \ */
#define FGE_KEY_RIGHT_BRACKET   ::FGE::Key::RightBracket  /* ] */
#define FGE_KEY_GRAVE_ACCENT    ::FGE::Key::GraveAccent   /* ` */
#define FGE_KEY_WORLD_1         ::FGE::Key::World1        /* non-US #1 */
#define FGE_KEY_WORLD_2         ::FGE::Key::World2        /* non-US #2 */

/* Function keys */
#define FGE_KEY_ESCAPE          ::FGE::Key::Escape
#define FGE_KEY_ENTER           ::FGE::Key::Enter
#define FGE_KEY_TAB             ::FGE::Key::Tab
#define FGE_KEY_BACKSPACE       ::FGE::Key::Backspace
#define FGE_KEY_INSERT          ::FGE::Key::Insert
#define FGE_KEY_DELETE          ::FGE::Key::Delete
#define FGE_KEY_RIGHT           ::FGE::Key::Right
#define FGE_KEY_LEFT            ::FGE::Key::Left
#define FGE_KEY_DOWN            ::FGE::Key::Down
#define FGE_KEY_UP              ::FGE::Key::Up
#define FGE_KEY_PAGE_UP         ::FGE::Key::PageUp
#define FGE_KEY_PAGE_DOWN       ::FGE::Key::PageDown
#define FGE_KEY_HOME            ::FGE::Key::Home
#define FGE_KEY_END             ::FGE::Key::End
#define FGE_KEY_CAPS_LOCK       ::FGE::Key::CapsLock
#define FGE_KEY_SCROLL_LOCK     ::FGE::Key::ScrollLock
#define FGE_KEY_NUM_LOCK        ::FGE::Key::NumLock
#define FGE_KEY_PRINT_SCREEN    ::FGE::Key::PrintScreen
#define FGE_KEY_PAUSE           ::FGE::Key::Pause
#define FGE_KEY_F1              ::FGE::Key::F1
#define FGE_KEY_F2              ::FGE::Key::F2
#define FGE_KEY_F3              ::FGE::Key::F3
#define FGE_KEY_F4              ::FGE::Key::F4
#define FGE_KEY_F5              ::FGE::Key::F5
#define FGE_KEY_F6              ::FGE::Key::F6
#define FGE_KEY_F7              ::FGE::Key::F7
#define FGE_KEY_F8              ::FGE::Key::F8
#define FGE_KEY_F9              ::FGE::Key::F9
#define FGE_KEY_F10             ::FGE::Key::F10
#define FGE_KEY_F11             ::FGE::Key::F11
#define FGE_KEY_F12             ::FGE::Key::F12
#define FGE_KEY_F13             ::FGE::Key::F13
#define FGE_KEY_F14             ::FGE::Key::F14
#define FGE_KEY_F15             ::FGE::Key::F15
#define FGE_KEY_F16             ::FGE::Key::F16
#define FGE_KEY_F17             ::FGE::Key::F17
#define FGE_KEY_F18             ::FGE::Key::F18
#define FGE_KEY_F19             ::FGE::Key::F19
#define FGE_KEY_F20             ::FGE::Key::F20
#define FGE_KEY_F21             ::FGE::Key::F21
#define FGE_KEY_F22             ::FGE::Key::F22
#define FGE_KEY_F23             ::FGE::Key::F23
#define FGE_KEY_F24             ::FGE::Key::F24
#define FGE_KEY_F25             ::FGE::Key::F25

/* Keypad */
#define FGE_KEY_KP_0            ::FGE::Key::KP0
#define FGE_KEY_KP_1            ::FGE::Key::KP1
#define FGE_KEY_KP_2            ::FGE::Key::KP2
#define FGE_KEY_KP_3            ::FGE::Key::KP3
#define FGE_KEY_KP_4            ::FGE::Key::KP4
#define FGE_KEY_KP_5            ::FGE::Key::KP5
#define FGE_KEY_KP_6            ::FGE::Key::KP6
#define FGE_KEY_KP_7            ::FGE::Key::KP7
#define FGE_KEY_KP_8            ::FGE::Key::KP8
#define FGE_KEY_KP_9            ::FGE::Key::KP9
#define FGE_KEY_KP_DECIMAL      ::FGE::Key::KPDecimal
#define FGE_KEY_KP_DIVIDE       ::FGE::Key::KPDivide
#define FGE_KEY_KP_MULTIPLY     ::FGE::Key::KPMultiply
#define FGE_KEY_KP_SUBTRACT     ::FGE::Key::KPSubtract
#define FGE_KEY_KP_ADD          ::FGE::Key::KPAdd
#define FGE_KEY_KP_ENTER        ::FGE::Key::KPEnter
#define FGE_KEY_KP_EQUAL        ::FGE::Key::KPEqual

#define FGE_KEY_LEFT_SHIFT      ::FGE::Key::LeftShift
#define FGE_KEY_LEFT_CONTROL    ::FGE::Key::LeftControl
#define FGE_KEY_LEFT_ALT        ::FGE::Key::LeftAlt
#define FGE_KEY_LEFT_SUPER      ::FGE::Key::LeftSuper
#define FGE_KEY_RIGHT_SHIFT     ::FGE::Key::RightShift
#define FGE_KEY_RIGHT_CONTROL   ::FGE::Key::RightControl
#define FGE_KEY_RIGHT_ALT       ::FGE::Key::RightAlt
#define FGE_KEY_RIGHT_SUPER     ::FGE::Key::RightSuper
#define FGE_KEY_MENU            ::FGE::Key::Menu
