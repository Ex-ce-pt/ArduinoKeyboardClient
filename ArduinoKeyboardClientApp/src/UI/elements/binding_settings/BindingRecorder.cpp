#include "BindingRecorder.h"

UI::BindingSettings::BindingRecorder::BindingRecorder(const sf::Vector2f& pos, const sf::Vector2f& size)
	: UIElement(NULL)
{
	this->pos = pos;
	this->size = size;

	bg.setPosition(pos);
	bg.setSize(size);
	bg.setOutlineColor(sf::Color::Black);
	bg.setOutlineThickness(2);
}

void UI::BindingSettings::BindingRecorder::render(std::shared_ptr<sf::RenderTarget> target) {
	target->draw(bg);
}

void UI::BindingSettings::BindingRecorder::onEvent(const Event& event) { }
