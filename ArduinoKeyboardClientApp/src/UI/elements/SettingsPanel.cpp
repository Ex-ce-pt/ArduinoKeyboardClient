#include "SettingsPanel.h"

#include "../Globals.h"

UI::SettingsPanel::SettingsPanel(App::App* app)
	: UIElement(app), scroll(0)
{
	pos = sf::Vector2f(10, 100);
	size = sf::Vector2f(600 - 10 * 2, 400 - 10 - pos.y);

	fullTexture.create(size.x, ACTUAL_HEIGHT);
	fullTexture.clear();

	bg.setPosition(pos);
	bg.setSize(size);
	bg.setOutlineThickness(2);
	bg.setOutlineColor(sf::Color::Black);

	display.setPosition(pos);

	scrollbar.setFillColor(sf::Color::Black);

	indices = std::make_unique<sf::Text[]>(BINDINGS_COUNT);
	for (size_t i = 0; i < BINDINGS_COUNT; i++) {
		indices[i] = sf::Text(std::to_string(i + 1), Global::getFont(), Global::getTextSize());
		indices[i].setFillColor(sf::Color::Black);
		indices[i].move(10, BINDING_MARGIN + BINDING_HEIGHT * i + BINDING_MARGIN * i);
	}
}

void UI::SettingsPanel::render(std::shared_ptr<sf::RenderWindow> window) {
	window->draw(bg);

	fullTexture.clear(sf::Color::White);	
	
	for (size_t i = 0; i < BINDINGS_COUNT; i++) {
		fullTexture.draw(indices[i]);
	}
	

	fullTexture.display();
	display.setTexture(fullTexture.getTexture());
	sf::IntRect view(0, scroll, size.x, size.y);
	display.setTextureRect(view);

	window->draw(display);

	updateScrollbar();
	window->draw(scrollbar);
}

void UI::SettingsPanel::onEvent(const Event& event) {
	if (event.type == Event::EventType::SFML_EVENT &&
		event.payload.sfmlEvent.type == sf::Event::MouseWheelScrolled) {

		scroll = std::max(
			std::min(
				scroll + event.payload.sfmlEvent.mouseWheelScroll.delta * -SCROLL_SPEED,
				ACTUAL_HEIGHT - size.y
			),
			0.0f
		);
	}
}

void UI::SettingsPanel::updateScrollbar() {
	const float sizeToActualHeight = size.y / ACTUAL_HEIGHT;
	const float scrollToActualHeight = (float) scroll / ACTUAL_HEIGHT;

	scrollbar.setPosition(pos + sf::Vector2f(size.x - 2 - SCROLLBAR_WIDTH, size.y * scrollToActualHeight));
	scrollbar.setSize(sf::Vector2f(SCROLLBAR_WIDTH, size.y * sizeToActualHeight));
}
