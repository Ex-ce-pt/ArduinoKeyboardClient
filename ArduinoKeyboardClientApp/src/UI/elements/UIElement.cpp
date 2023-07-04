#include "UIElement.h"

static std::unique_ptr<sf::Font> FONT;

UI::UIElement::UIElement(App::App* app)
	: app(app), pos(sf::Vector2f()), size(sf::Vector2f()), layer(0)
{}

void UI::UIElement::onEvent(const Event& event) { };

bool UI::UIElement::intersects(const sf::Vector2f& point) const {
	return point.x >= pos.x &&
		point.x <= pos.x + size.x &&
		point.y >= pos.y &&
		point.y <= pos.y + size.y;
}

const sf::Vector2f& UI::UIElement::getPos() const {
	return pos;
}

const sf::Vector2f& UI::UIElement::getSize() const {
	return size;
}

int UI::UIElement::getLayer() const {
	return layer;
}

bool UI::compareElementsByLayer(std::shared_ptr<UIElement> first, std::shared_ptr<UIElement> second) {
	return first->getLayer() < second->getLayer();
}

void UI::initFont() {
	FONT = std::make_unique<sf::Font>();
	FONT->loadFromFile("CONSOLA.ttf");
}

void UI::deleteFont() {
	FONT.release();
}

const sf::Font& UI::getFont() {
	return *FONT.get();
}
