#include "SettingsPanel.h"

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
}

void UI::SettingsPanel::render(std::shared_ptr<sf::RenderWindow> window) {
	window->draw(bg);

	fullTexture.clear();

	for (int i = 0; i < ACTUAL_HEIGHT; i += 10) {
		float c = (float) i / ACTUAL_HEIGHT * 255;
		sf::RectangleShape rect;
		rect.setPosition(0, i);
		rect.setSize(sf::Vector2f(size.x, 10));
		rect.setFillColor(sf::Color(c, 0, 0));
		fullTexture.draw(rect);
	}

	// ...


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

		scroll = std::max(std::min(scroll + event.payload.sfmlEvent.mouseWheelScroll.delta * -10, ACTUAL_HEIGHT - size.y), 0.0f);
	}
}

void UI::SettingsPanel::updateScrollbar() {
	const float sizeToActualHeight = size.y / ACTUAL_HEIGHT;
	const float scrollToActualHeight = (float) scroll / ACTUAL_HEIGHT;

	scrollbar.setPosition(pos + sf::Vector2f(size.x - 2 - SCROLLBAR_WIDTH, size.y * scrollToActualHeight));
	scrollbar.setSize(sf::Vector2f(SCROLLBAR_WIDTH, size.y * sizeToActualHeight));
}
