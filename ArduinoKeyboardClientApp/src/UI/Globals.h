#pragma once

#include <SFML/Graphics.hpp>

#include "../lib/timer/timer.hpp"

namespace Global {

	void initGlobals();
	void freeGlobals();

	const sf::Font& getFont();
	int getTextSize();
	const shared::util::c_timer_mgr& getTimerManager();
	const char* sfmlKeycodeToCString(sf::Keyboard::Key key);
	int sfmlKeycodeToWindowsKeycode(sf::Keyboard::Key key);

}
