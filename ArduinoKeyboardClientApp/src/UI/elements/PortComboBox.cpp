#include "PortComboBox.h"

#include "../ClientApp.h"
#include "../Globals.h"

UI::PortComboBox::PortComboBox(App::App* app)
	: UIElement(app), selectedItem(NONE), opened(false), active(true)
{
	layer = 100;

	pos = sf::Vector2f(90, 10);


	updateMenu();

	updateVisibleText();
	
	inactiveShade.setPosition(pos);
	inactiveShade.setSize(size);
	inactiveShade.setFillColor(sf::Color(0, 0, 0, 35));
}

void UI::PortComboBox::render(std::shared_ptr<sf::RenderWindow> window) {
	window->draw(bg);
	window->draw(visibleText);

	if (!active) {

		window->draw(inactiveShade);
		
	} else if (opened) {
		
		for (size_t i = 0; i < portIDs.size(); i++) {
			window->draw(items[i]);
		}
		
	}

}

void UI::PortComboBox::onEvent(const Event& event) {
	if (event.type == Event::EventType::COM_PORT_SCAN_STATUS &&
		event.payload.COMPortScanStatus.scanStatus == ERROR_SUCCESS &&
		active) {

		portIDs = event.payload.COMPortScanStatus.portIDs;

		items = std::make_unique<sf::Text[]>(portIDs.size());
		for (size_t i = 0; i < portIDs.size(); i++) {
			items[i] = sf::Text("COM" + std::to_string(portIDs[i]), Global::getFont(), Global::getTextSize());
			items[i].setFillColor(sf::Color::Black);
			items[i].move(pos + sf::Vector2f(2, 2) + sf::Vector2f(0, ITEM_HEIGHT));
		}


	} else if (event.type == Event::EventType::SFML_EVENT &&
				event.payload.sfmlEvent.type == sf::Event::MouseButtonReleased &&
				active) {

		int y = event.getEventCoordinates().y - pos.y;
		
		if (y >= 0 && y <= ITEM_HEIGHT) {

			opened = !opened;

		} else {

			if (!items) return;
			
			selectedItem = (y - ITEM_HEIGHT) / ITEM_HEIGHT;
			opened = false;
			app->setPortID(portIDs[selectedItem]);
			printf("%i\n", selectedItem);

		}

		updateMenu();
		updateVisibleText();

	} else if (event.type == Event::EventType::CONNECT_TO_PORT) {

		active = false;

	} else if (event.type == Event::EventType::DISCONNECT_FROM_PORT) {

		active = true;

	}
}

void UI::PortComboBox::updateMenu() {
	if (opened) {

		if (items) {

			size = sf::Vector2f(100, ITEM_HEIGHT + ITEM_HEIGHT * portIDs.size());
			
		} else {

			size = sf::Vector2f(100, ITEM_HEIGHT * 2);
			
		}
		
	} else {

		size = sf::Vector2f(100, ITEM_HEIGHT);
		
	}

	bg.setPosition(pos);
	bg.setSize(size);
	bg.setOutlineColor(sf::Color::Black);
	bg.setOutlineThickness(2);

}

void UI::PortComboBox::updateVisibleText() {
	if (selectedItem == NONE) {

		visibleText = sf::Text("---", Global::getFont(), Global::getTextSize());

	} else {

		if (!items) return;

		visibleText = sf::Text(items[selectedItem].getString(), Global::getFont(), Global::getTextSize());

	}

	visibleText.setFillColor(sf::Color::Black);
	visibleText.move(pos + sf::Vector2f(2, 2));
}
