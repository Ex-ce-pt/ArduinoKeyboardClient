#include "ConnectButton.h"

#include "../ClientApp.h"

UI::ConnectButton::ConnectButton(App::App* app)
	: UIElement(app), active(true)
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

	inactiveShade.setPosition(pos);
	inactiveShade.setSize(size);
	inactiveShade.setFillColor(sf::Color(0, 0, 0, 35));

}

void UI::ConnectButton::render(std::shared_ptr<sf::RenderWindow> window) const {
	window->draw(bg);
	window->draw(text);

	if (active) return;

	window->draw(inactiveShade);
}

void UI::ConnectButton::onEvent(const Event& event) {
	if (event.type == Event::EventType::SFML_EVENT &&
		event.payload.sfmlEvent.type == sf::Event::MouseButtonReleased &&
		active) {
		
		app->invokeConnectToPort();

	} else if (event.type == Event::EventType::CONNECT_TO_PORT) {

		active = false;

	} else if (event.type == Event::EventType::DISCONNECT_FROM_PORT) {

		active = true;

	}
}
