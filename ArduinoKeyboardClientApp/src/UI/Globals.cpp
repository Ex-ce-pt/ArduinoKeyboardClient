#include "Globals.h"

static std::unique_ptr<sf::Font> FONT;

void Global::initGlobals() {
	FONT = std::make_unique<sf::Font>();
	FONT->loadFromFile("CONSOLA.ttf");
}

void Global::freeGlobals() {
	FONT.release();
}

const sf::Font& Global::getFont() {
	return *FONT.get();
}

int Global::getTextSize() {
	return 20;
}
