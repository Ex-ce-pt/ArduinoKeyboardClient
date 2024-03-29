#include "ScanButton.h"

#include "../ClientApp.h"
#include "../Globals.h"

UI::ScanButton::ScanButton(App::App* app)
	: UIElement(app), active(true)
{
	pos = sf::Vector2f(10, 10);
	size = sf::Vector2f(75, 35);

	text = sf::Text("Scan", Global::getFont(), Global::getTextSize());
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

void UI::ScanButton::render(std::shared_ptr<sf::RenderTarget> target) {
	target->draw(bg);
	target->draw(text);

	if (active) return;

	target->draw(inactiveShade);
}

void UI::ScanButton::onEvent(const Event& event) {
	if (event.type == Event::EventType::POSITIONED_SFML_EVENT &&
		event.payload.sfmlEvent.type == sf::Event::MouseButtonReleased &&
		active) {
		
		app->invokeCOMPortScan();

	} else if (event.type == Event::EventType::CONNECT_TO_PORT) {

		active = false;

	} else if (event.type == Event::EventType::DISCONNECT_FROM_PORT) {

		active = true;

	}
}
