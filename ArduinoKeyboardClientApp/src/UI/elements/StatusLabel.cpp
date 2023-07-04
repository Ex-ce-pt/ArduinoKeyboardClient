#include "StatusLabel.h"

static void clearLabelAfter(UI::StatusLabel* self, int delay) {
	std::this_thread::sleep_for(std::chrono::microseconds(delay));
	self->clear();
}

UI::StatusLabel::StatusLabel(App::App* app)
	: UIElement(app)
{
	pos = sf::Vector2f(440, 10);
	size = sf::Vector2f(100, 35);
	
	text = sf::Text("", getFont(), 20);
	text.setFillColor(sf::Color::Black);
	text.move(pos + sf::Vector2f(2, 2));
}

void UI::StatusLabel::render(std::shared_ptr<sf::RenderWindow> window) const {
	window->draw(text);
}

void UI::StatusLabel::onEvent(const Event& event) {
	if (event.type == Event::EventType::COM_PORT_SCAN_STATUS) {
		if (!((std::string) text.getString()).compare("No ports found")) {
			text.setString("Test");
			text.setFillColor(sf::Color::Red);
			return;
		}

		if (event.payload.COMPortScanStatus.portIDs.size() == 0) {
			text.setString("No ports found");
			text.setFillColor(sf::Color::Red);

		}
	}
}

void UI::StatusLabel::clear() {
	text.setString("");
}
