#include "Globals.h"

static std::unique_ptr<sf::Font> FONT;
static std::unique_ptr<shared::util::c_timer_mgr> TIMER_MANAGER;

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
