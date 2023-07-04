#include "PortComboBox.h"

#include <iostream>

UI::PortComboBox::PortComboBox(App::App* app)
	: UIElement(app), selectedItem(NONE), opened(false), itemsCount(0)
{
	layer = 100;

	pos = sf::Vector2f(90, 10);

	updateMenu();

	updateVisibleText();
}

void UI::PortComboBox::render(std::shared_ptr<sf::RenderWindow> window) const {
	window->draw(bg);
	window->draw(visibleText);

	if (!opened) return;

	for (size_t i = 0; i < itemsCount; i++) {
		window->draw(items[i]);
	}
}

void UI::PortComboBox::onEvent(const Event& event) {
	if (event.type == Event::EventType::COM_PORT_SCAN_STATUS &&
		event.payload.COMPortScanStatus.scanStatus == ERROR_SUCCESS) {
		const auto& portsFound = event.payload.COMPortScanStatus.portIDs;

		itemsCount = portsFound.size();
		items = std::make_unique<sf::Text[]>(itemsCount);
		for (size_t i = 0; i < itemsCount; i++) {
			items[i] = sf::Text("COM" + std::to_string(portsFound[i]), getFont(), 20);
			items[i].setFillColor(sf::Color::Black);
			items[i].move(pos + sf::Vector2f(2, 2) + sf::Vector2f(0, 35));
		}


	} else if (event.type == Event::EventType::SFML_EVENT &&
				event.payload.sfmlEvent.type == sf::Event::MouseButtonReleased) {

		int y = event.getEventCoordinates().y - pos.y;
		
		if (y >= 0 && y <= ITEM_HEIGHT) {

			opened = !opened;

		} else {

			if (!items) return;
			
			selectedItem = (y - ITEM_HEIGHT) / ITEM_HEIGHT;
			opened = false;
			printf("%i\n", selectedItem);

		}

		updateMenu();
		updateVisibleText();

	}
}

void UI::PortComboBox::updateMenu() {
	if (opened) {

		if (items) {

			size = sf::Vector2f(100, ITEM_HEIGHT + ITEM_HEIGHT * itemsCount);
			
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

		visibleText = sf::Text("---", getFont(), 20);

	} else {

		if (!items) return;

		visibleText = sf::Text(items[selectedItem].getString(), getFont(), 20);

	}

	visibleText.setFillColor(sf::Color::Black);
	visibleText.move(pos + sf::Vector2f(2, 2));
}
