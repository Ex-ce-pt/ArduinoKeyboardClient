#include "Globals.h"

#include <unordered_map>

static std::unique_ptr<sf::Font> FONT;
static std::unique_ptr<shared::util::c_timer_mgr> TIMER_MANAGER;

static std::unordered_map<sf::Keyboard::Key, const char*> KEY_NAMES = {
	{ sf::Keyboard::A,			   "a"				},
	{ sf::Keyboard::B,			   "b"				},
	{ sf::Keyboard::C,			   "c"				},
	{ sf::Keyboard::D,			   "d"				},
	{ sf::Keyboard::E,			   "e"				},
	{ sf::Keyboard::F,			   "f"				},
	{ sf::Keyboard::G,			   "g"				},
	{ sf::Keyboard::H,			   "h"				},
	{ sf::Keyboard::I,			   "i"				},
	{ sf::Keyboard::J,			   "j"				},
	{ sf::Keyboard::K,			   "k"				},
	{ sf::Keyboard::L,			   "l"				},
	{ sf::Keyboard::M,			   "m"				},
	{ sf::Keyboard::N,			   "n"				},
	{ sf::Keyboard::O,			   "o"				},
	{ sf::Keyboard::P,			   "p"				},
	{ sf::Keyboard::Q,			   "q"				},
	{ sf::Keyboard::R,			   "r"				},
	{ sf::Keyboard::S,			   "s"				},
	{ sf::Keyboard::T,			   "t"				},
	{ sf::Keyboard::U,			   "u"				},
	{ sf::Keyboard::V,			   "v"				},
	{ sf::Keyboard::W,			   "w"				},
	{ sf::Keyboard::X,			   "x"				},
	{ sf::Keyboard::Y,			   "y"				},
	{ sf::Keyboard::Z,			   "z"				},
	{ sf::Keyboard::Num0,		   "0"				},
	{ sf::Keyboard::Num1,		   "1"				},
	{ sf::Keyboard::Num2,		   "2"				},
	{ sf::Keyboard::Num3,		   "3"				},
	{ sf::Keyboard::Num4,		   "4"				},
	{ sf::Keyboard::Num5,		   "5"				},
	{ sf::Keyboard::Num6,		   "6"				},
	{ sf::Keyboard::Num7,		   "7"				},
	{ sf::Keyboard::Num8,		   "8"				},
	{ sf::Keyboard::Num9,		   "9"				},
	{ sf::Keyboard::Escape,		   "esc"			},
	{ sf::Keyboard::LControl,	   "ctrl"			},
	{ sf::Keyboard::LShift,		   "shift"			},
	{ sf::Keyboard::LAlt,		   "alt"			},
	{ sf::Keyboard::LSystem,	   "wnd"			},
	{ sf::Keyboard::RControl,	   "ctrl"			},
	{ sf::Keyboard::RShift,		   "shift"			},
	{ sf::Keyboard::RAlt,		   "alt"			},
	{ sf::Keyboard::RSystem,	   "wnd"			},
	{ sf::Keyboard::Menu,		   "menu"			},
	{ sf::Keyboard::LBracket,	   "["				},
	{ sf::Keyboard::RBracket,	   "]"				},
	{ sf::Keyboard::Semicolon,	   ";"				},
	{ sf::Keyboard::Comma,		   ","				},
	{ sf::Keyboard::Period,		   "."				},
	{ sf::Keyboard::Quote,		   "'"				},
	{ sf::Keyboard::Slash,		   "/"				},
	{ sf::Keyboard::Backslash,	   "\\"				},
	{ sf::Keyboard::Tilde,		   "~"				},
	{ sf::Keyboard::Equal,		   "="				},
	{ sf::Keyboard::Hyphen,		   "-"				},
	{ sf::Keyboard::Space,		   "space"			},
	{ sf::Keyboard::Enter,		   "enter"			},
	{ sf::Keyboard::Backspace,	   "backspace"		},
	{ sf::Keyboard::Tab,		   "tab"			},
	{ sf::Keyboard::PageUp,		   "page up"		},
	{ sf::Keyboard::PageDown,	   "page down"		},
	{ sf::Keyboard::End,		   "end"			},
	{ sf::Keyboard::Home,		   "home"			},
	{ sf::Keyboard::Insert,		   "insert"			},
	{ sf::Keyboard::Delete,		   "delete"			},
	{ sf::Keyboard::Add,		   "+"				},
	{ sf::Keyboard::Subtract,	   "-"				},
	{ sf::Keyboard::Multiply,	   "*"				},
	{ sf::Keyboard::Divide,		   "/"				},
	{ sf::Keyboard::Left,		   "left arrow"		},
	{ sf::Keyboard::Right,		   "right arrow"	},
	{ sf::Keyboard::Up,			   "up arrow"		},
	{ sf::Keyboard::Down,		   "down arrow"		},
	{ sf::Keyboard::Numpad0,	   "numpad 0"		},
	{ sf::Keyboard::Numpad1,	   "numpad 1"		},
	{ sf::Keyboard::Numpad2,	   "numpad 2"		},
	{ sf::Keyboard::Numpad3,	   "numpad 3"		},
	{ sf::Keyboard::Numpad4,	   "numpad 4"		},
	{ sf::Keyboard::Numpad5,	   "numpad 5"		},
	{ sf::Keyboard::Numpad6,	   "numpad 6"		},
	{ sf::Keyboard::Numpad7,	   "numpad 7"		},
	{ sf::Keyboard::Numpad8,	   "numpad 8"		},
	{ sf::Keyboard::Numpad9,	   "numpad 9"		},
	{ sf::Keyboard::F1,			   "F1"				},
	{ sf::Keyboard::F2,			   "F2"				},
	{ sf::Keyboard::F3,			   "F3"				},
	{ sf::Keyboard::F4,			   "F4"				},
	{ sf::Keyboard::F5,			   "F5"				},
	{ sf::Keyboard::F6,			   "F6"				},
	{ sf::Keyboard::F7,			   "F7"				},
	{ sf::Keyboard::F8,			   "F8"				},
	{ sf::Keyboard::F9,			   "F9"				},
	{ sf::Keyboard::F10,		   "F1"				},
	{ sf::Keyboard::F11,		   "F1"				},
	{ sf::Keyboard::F12,		   "F1"				},
	{ sf::Keyboard::F13,		   "F1"				},
	{ sf::Keyboard::F14,		   "F1"				},
	{ sf::Keyboard::F15,		   "F1"				},
	{ sf::Keyboard::Pause,		   "pause"			}
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

const char* Global::keycodeToCString(sf::Keyboard::Key key) {
    try {

        return KEY_NAMES.at(key);

    } catch (std::out_of_range e) {

        return nullptr;

    }
}
