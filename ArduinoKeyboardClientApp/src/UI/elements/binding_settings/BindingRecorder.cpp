#include "BindingRecorder.h"

#include "../../Globals.h"

UI::BindingSettings::BindingRecorder::BindingRecorder(const sf::Vector2f& pos, const sf::Vector2f& size)
	: UIElement(NULL)
{
	this->pos = pos;
	this->size = size;

	bg.setPosition(pos);
	bg.setSize(size);
	bg.setOutlineThickness(2);

	setSelected(false);

	text = sf::Text("", Global::getFont(), Global::getTextSize());
	text.setFillColor(sf::Color::Black);
	text.move(pos + sf::Vector2f(5, 5));
}

void UI::BindingSettings::BindingRecorder::render(std::shared_ptr<sf::RenderTarget> target) {
	target->draw(bg);
	target->draw(text);
}

void UI::BindingSettings::BindingRecorder::onEvent(const Event& event) { }

void UI::BindingSettings::BindingRecorder::setSelected(bool flag) {
	bg.setOutlineColor(flag ? sf::Color(200, 200, 200) : sf::Color::Black);
}

void UI::BindingSettings::BindingRecorder::setText(const std::string& t) {
	text.setString(t);
}
