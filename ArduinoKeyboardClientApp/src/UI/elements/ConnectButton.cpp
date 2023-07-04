#include "ConnectButton.h"

#include <iostream>

UI::ConnectButton::ConnectButton(App::App* app)
	: UIElement(app)
{
	pos = sf::Vector2f(200, 10);
	size = sf::Vector2f(90, 35);

	text = sf::Text("Connect", getFont(), 20);
	text.setFillColor(sf::Color::Black);
	text.move(pos + sf::Vector2f(2, 2));

	bg.setPosition(pos);
	bg.setSize(size);
	bg.setOutlineThickness(2);
	bg.setOutlineColor(sf::Color::Black);
}

void UI::ConnectButton::render(std::shared_ptr<sf::RenderWindow> window) const {
	window->draw(bg);
	window->draw(text);
}

void UI::ConnectButton::onEvent(const Event& event) {
	if (event.type == Event::EventType::SFML_EVENT &&
		event.payload.sfmlEvent.type == sf::Event::MouseButtonReleased) {
		// connect
	}
}
