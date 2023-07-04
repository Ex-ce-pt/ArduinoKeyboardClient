#include "DisconnectButton.h"

#include "../ClientApp.h"

UI::DisconnectButton::DisconnectButton(App::App* app)
	: UIElement(app), active(false)
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

	inactiveShade.setPosition(pos);
	inactiveShade.setSize(size);
	inactiveShade.setFillColor(sf::Color(0, 0, 0, 35));

}

void UI::DisconnectButton::render(std::shared_ptr<sf::RenderWindow> window) {
	window->draw(bg);
	window->draw(text);

	if (active) return;

	window->draw(inactiveShade);
}

void UI::DisconnectButton::onEvent(const Event& event) {
	if (event.type == Event::EventType::SFML_EVENT &&
		event.payload.sfmlEvent.type == sf::Event::MouseButtonReleased &&
		active) {
		
		app->invokeDisconnectFromPort();

	} else if (event.type == Event::EventType::CONNECT_TO_PORT) {

		active = true;

	} else if (event.type == Event::EventType::DISCONNECT_FROM_PORT) {

		active = false;

	}
}
