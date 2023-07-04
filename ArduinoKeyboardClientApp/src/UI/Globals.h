#pragma once

#include <SFML/Graphics.hpp>

namespace Global {

	void initGlobals();
	void freeGlobals();

	const sf::Font& getFont();
	int getTextSize();

}
