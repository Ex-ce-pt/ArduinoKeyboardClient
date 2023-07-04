#include "DisconnectButton.h"

#include <iostream>

UI::DisconnectButton::DisconnectButton(App::App* app)
	: UIElement(app)
{
	pos = sf::Vector2f(300, 10);
	size = sf::Vector2f(130, 35);

	text = sf::Text("Disconnect", getFont(), 20);
	text.setFillColor(sf::Color::Black);
	text.move(pos + sf::Vector2f(2, 2));
	
	bg.setPosition(pos);
	bg.setSize(size);
	bg.setOutlineThickness(2);
	bg.setOutlineColor(sf::Color::Black);

}

void UI::DisconnectButton::render(std::shared_ptr<sf::RenderWindow> window) const {
	window->draw(bg);
	window->draw(text);
}

void UI::DisconnectButton::onEvent(const Event& event) {
	if (event.type == Event::EventType::SFML_EVENT &&
		event.payload.sfmlEvent.type == sf::Event::MouseButtonReleased) {
		// disconnect
	}
}
