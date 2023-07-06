#include "BindingClearButton.h"

#include "../../Globals.h"

UI::BindingSettings::BindingClearButton::BindingClearButton(const sf::Vector2f& pos, const sf::Vector2f& size)
	: UIElement(NULL)
{
	this->pos = pos;
	this->size = size;

	bg.setPosition(pos);
	bg.setSize(size);
	bg.setOutlineColor(sf::Color::Black);
	bg.setOutlineThickness(2);

	text = sf::Text("Clear", Global::getFont(), Global::getTextSize());
	text.setFillColor(sf::Color::Black);
	text.move(pos + sf::Vector2f(5, 5));

}

void UI::BindingSettings::BindingClearButton::render(std::shared_ptr<sf::RenderTarget> target) {
	target->draw(bg);
	target->draw(text);
}

void UI::BindingSettings::BindingClearButton::onEvent(const Event& event) { }
