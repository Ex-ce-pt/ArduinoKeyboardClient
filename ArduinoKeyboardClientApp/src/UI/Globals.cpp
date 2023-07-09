#include "Globals.h"

#include <unordered_map>
#include <Windows.h>

static std::unique_ptr<sf::Font> FONT;
static std::unique_ptr<shared::util::c_timer_mgr> TIMER_MANAGER;

static std::unordered_map<sf::Keyboard::Key, std::pair<const char*, int>> KEY_NAMES = {
	{ sf::Keyboard::A,			   { "a",			(int) 'a'	} },
	{ sf::Keyboard::B,			   { "b",			(int) 'b'	} },
	{ sf::Keyboard::C,			   { "c",			(int) 'c'	} },
	{ sf::Keyboard::D,			   { "d",			(int) 'd'	} },
	{ sf::Keyboard::E,			   { "e",			(int) 'e'	} },
	{ sf::Keyboard::F,			   { "f",			(int) 'f'	} },
	{ sf::Keyboard::G,			   { "g",			(int) 'g'	} },
	{ sf::Keyboard::H,			   { "h",			(int) 'h'	} },
	{ sf::Keyboard::I,			   { "i",			(int) 'i'	} },
	{ sf::Keyboard::J,			   { "j",			(int) 'j'	} },
	{ sf::Keyboard::K,			   { "k",			(int) 'k'	} },
	{ sf::Keyboard::L,			   { "l",			(int) 'l'	} },
	{ sf::Keyboard::M,			   { "m",			(int) 'm'	} },
	{ sf::Keyboard::N,			   { "n",			(int) 'n'	} },
	{ sf::Keyboard::O,			   { "o",			(int) 'o'	} },
	{ sf::Keyboard::P,			   { "p",			(int) 'p'	} },
	{ sf::Keyboard::Q,			   { "q",			(int) 'q'	} },
	{ sf::Keyboard::R,			   { "r",			(int) 'r'	} },
	{ sf::Keyboard::S,			   { "s",			(int) 's'	} },
	{ sf::Keyboard::T,			   { "t",			(int) 't'	} },
	{ sf::Keyboard::U,			   { "u",			(int) 'u'	} },
	{ sf::Keyboard::V,			   { "v",			(int) 'v'	} },
	{ sf::Keyboard::W,			   { "w",			(int) 'w'	} },
	{ sf::Keyboard::X,			   { "x",			(int) 'x'	} },
	{ sf::Keyboard::Y,			   { "y",			(int) 'y'	} },
	{ sf::Keyboard::Z,			   { "z",			(int) 'z'	} },
	{ sf::Keyboard::Num0,		   { "0",			(int) '0'	} },
	{ sf::Keyboard::Num1,		   { "1",			(int) '1'	} },
	{ sf::Keyboard::Num2,		   { "2",			(int) '2'	} },
	{ sf::Keyboard::Num3,		   { "3",			(int) '3'	} },
	{ sf::Keyboard::Num4,		   { "4",			(int) '4'	} },
	{ sf::Keyboard::Num5,		   { "5",			(int) '5'	} },
	{ sf::Keyboard::Num6,		   { "6",			(int) '6'	} },
	{ sf::Keyboard::Num7,		   { "7",			(int) '7'	} },
	{ sf::Keyboard::Num8,		   { "8",			(int) '8'	} },
	{ sf::Keyboard::Num9,		   { "9",			(int) '9'	} },
	{ sf::Keyboard::Escape,		   { "esc",			VK_ESCAPE	} },
	{ sf::Keyboard::LControl,	   { "ctrl",		VK_LCONTROL } },
	{ sf::Keyboard::LShift,		   { "shift",		VK_LSHIFT	} },
	{ sf::Keyboard::LAlt,		   { "alt",			VK_LMENU	} },
	{ sf::Keyboard::LSystem,	   { "wnd",			VK_LWIN		} },
	{ sf::Keyboard::RControl,	   { "ctrl",		VK_RCONTROL } },
	{ sf::Keyboard::RShift,		   { "shift",		VK_RSHIFT	} },
	{ sf::Keyboard::RAlt,		   { "alt",			VK_RMENU	} },
	{ sf::Keyboard::RSystem,	   { "wnd",			VK_RWIN		} },
	{ sf::Keyboard::Menu,		   { "menu",		VK_MENU		} },
	{ sf::Keyboard::LBracket,	   { "[",			(int) '['	} },
	{ sf::Keyboard::RBracket,	   { "]",			(int) ']'	} },
	{ sf::Keyboard::Semicolon,	   { ";",			(int) ';'	} },
	{ sf::Keyboard::Comma,		   { ",",			(int) ','	} },
	{ sf::Keyboard::Period,		   { ".",			(int) '.'	} },
	{ sf::Keyboard::Quote,		   { "'",			(int) '\''	} },
	{ sf::Keyboard::Slash,		   { "/",			(int) '/'	} },
	{ sf::Keyboard::Backslash,	   { "\\",			(int) '\\'	} },
	{ sf::Keyboard::Tilde,		   { "~",			(int) '~'	} },
	{ sf::Keyboard::Equal,		   { "=",			(int) '='	} },
	{ sf::Keyboard::Hyphen,		   { "-",			(int) '-'	} },
	{ sf::Keyboard::Space,		   { "space",		VK_SPACE	} },
	{ sf::Keyboard::Enter,		   { "enter",		VK_RETURN	} },
	{ sf::Keyboard::Backspace,	   { "backspace",	VK_BACK		} },
	{ sf::Keyboard::Tab,		   { "tab",			VK_TAB		} },
	{ sf::Keyboard::PageUp,		   { "page up",		VK_PRIOR	} },
	{ sf::Keyboard::PageDown,	   { "page down",	VK_NEXT		} },
	{ sf::Keyboard::End,		   { "end",			VK_END		} },
	{ sf::Keyboard::Home,		   { "home",		VK_HOME		} },
	{ sf::Keyboard::Insert,		   { "insert",		VK_INSERT	} },
	{ sf::Keyboard::Delete,		   { "delete",		VK_DELETE	} },
	{ sf::Keyboard::Add,		   { "+",			(int) '+'	} },
	{ sf::Keyboard::Subtract,	   { "-",			(int) '-'	} },
	{ sf::Keyboard::Multiply,	   { "*",			(int) '*'	} },
	{ sf::Keyboard::Divide,		   { "/",			(int) '/'	} },
	{ sf::Keyboard::Left,		   { "left arrow",	VK_LEFT		} },
	{ sf::Keyboard::Right,		   { "right arrow", VK_RIGHT	} },
	{ sf::Keyboard::Up,			   { "up arrow",	VK_UP		} },
	{ sf::Keyboard::Down,		   { "down arrow",	VK_DOWN		} },
	{ sf::Keyboard::Numpad0,	   { "numpad 0",	VK_NUMPAD0	} },
	{ sf::Keyboard::Numpad1,	   { "numpad 1",	VK_NUMPAD1	} },
	{ sf::Keyboard::Numpad2,	   { "numpad 2",	VK_NUMPAD2	} },
	{ sf::Keyboard::Numpad3,	   { "numpad 3",	VK_NUMPAD3	} },
	{ sf::Keyboard::Numpad4,	   { "numpad 4",	VK_NUMPAD4	} },
	{ sf::Keyboard::Numpad5,	   { "numpad 5",	VK_NUMPAD5	} },
	{ sf::Keyboard::Numpad6,	   { "numpad 6",	VK_NUMPAD6	} },
	{ sf::Keyboard::Numpad7,	   { "numpad 7",	VK_NUMPAD7	} },
	{ sf::Keyboard::Numpad8,	   { "numpad 8",	VK_NUMPAD8	} },
	{ sf::Keyboard::Numpad9,	   { "numpad 9",	VK_NUMPAD9	} },
	{ sf::Keyboard::F1,			   { "F1",			VK_F1		} },
	{ sf::Keyboard::F2,			   { "F2",			VK_F2		} },
	{ sf::Keyboard::F3,			   { "F3",			VK_F3		} },
	{ sf::Keyboard::F4,			   { "F4",			VK_F4		} },
	{ sf::Keyboard::F5,			   { "F5",			VK_F5		} },
	{ sf::Keyboard::F6,			   { "F6",			VK_F6		} },
	{ sf::Keyboard::F7,			   { "F7",			VK_F7		} },
	{ sf::Keyboard::F8,			   { "F8",			VK_F8		} },
	{ sf::Keyboard::F9,			   { "F9",			VK_F9		} },
	{ sf::Keyboard::F10,		   { "F10",			VK_F10		} },
	{ sf::Keyboard::F11,		   { "F11",			VK_F11		} },
	{ sf::Keyboard::F12,		   { "F12",			VK_F12		} },
	{ sf::Keyboard::F13,		   { "F13",			VK_F13		} },
	{ sf::Keyboard::F14,		   { "F14",			VK_F14		} },
	{ sf::Keyboard::F15,		   { "F15",			VK_F15		} },
	{ sf::Keyboard::Pause,		   { "pause",		VK_PAUSE	} }
};

void Global::initGlobals() {
	FONT = std::make_unique<sf::Font>();
	FONT->loadFromFile("CONSOLA.ttf");

	TIMER_MANAGER = std::make_unique<shared::util::c_timer_mgr>();
}

void Global::freeGlobals() {
	FONT.release();
	TIMER_MANAGER.release();
}

const sf::Font& Global::getFont() {
	return *FONT.get();
}

int Global::getTextSize() {
	return 20;
}

const shared::util::c_timer_mgr& Global::getTimerManager() {
	return *TIMER_MANAGER.get();
}

const char* Global::sfmlKeycodeToCString(sf::Keyboard::Key key) {
    try {

        return KEY_NAMES.at(key).first;

    } catch (std::out_of_range e) {

		fprintf(stderr, "Coulnd't find a key with a code %i\n", key);
        return nullptr;

    }
}

int Global::sfmlKeycodeToWindowsKeycode(sf::Keyboard::Key key) {
	try {

		return KEY_NAMES.at(key).second;

	} catch (std::out_of_range e) {

		fprintf(stderr, "Couldn't find a key with a code %i\n", key);
		return -1;
	}
}
