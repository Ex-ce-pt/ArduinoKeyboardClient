#include "SettingsPanel.h"

#include "../Globals.h"

int UI::SettingsPanel::getRowIndexByY(int y) {
	const int c = BINDING_HEIGHT + BINDING_MARGIN;
	const int row = (y - BINDING_MARGIN) / c;
	return std::min(std::max(row, 0), BINDINGS_COUNT - 1);
}

UI::SettingsPanel::SettingsPanel(App::App* app)
	: UIElement(app), scroll(0), active(true)
{
	pos = sf::Vector2f(10, 100);
	size = sf::Vector2f(600 - 10 * 2, 400 - 10 - pos.y);

	fullTexture = std::make_shared<sf::RenderTexture>();
	fullTexture->create(size.x, ACTUAL_HEIGHT);
	fullTexture->clear();

	bg.setPosition(pos);
	bg.setSize(size);
	bg.setOutlineThickness(2);
	bg.setOutlineColor(sf::Color::Black);

	display.setPosition(pos);

	scrollbar.setFillColor(sf::Color::Black);

	indices.reserve(BINDINGS_COUNT);
	bindings.reserve(BINDINGS_COUNT);
	bindingRecorders.reserve(BINDINGS_COUNT);
	bindingClearButtons.reserve(BINDINGS_COUNT);
	for (size_t i = 0; i < BINDINGS_COUNT; i++) {
		const int currentY = BINDING_MARGIN + (BINDING_HEIGHT + BINDING_MARGIN) * i;

		// indices
		indices.emplace_back(std::to_string(i + 1) + "    ->", Global::getFont(), Global::getTextSize());
		indices[i].setFillColor(sf::Color::Black);
		indices[i].move(10, currentY);

		// binding recorders
		bindingRecorders.emplace_back(
			sf::Vector2f(150, currentY),
			sf::Vector2f(150, BINDING_HEIGHT)
		);

		// binding clear buttons
		bindingClearButtons.emplace_back(
			sf::Vector2f(350, currentY),
			sf::Vector2f(100, BINDING_HEIGHT)
		);
	}

	inactiveShade.setPosition(pos);
	inactiveShade.setSize(size);
	inactiveShade.setFillColor(sf::Color(0, 0, 0, 35));

}

void UI::SettingsPanel::render(std::shared_ptr<sf::RenderTarget> target) {
	target->draw(bg);

	fullTexture->clear(sf::Color::White);	
	
	for (size_t i = 0; i < BINDINGS_COUNT; i++) {
		fullTexture->draw(indices[i]);
		bindingRecorders[i].render(fullTexture);
		bindingClearButtons[i].render(fullTexture);
	}

	fullTexture->display();
	display.setTexture(fullTexture->getTexture());
	sf::IntRect view(0, scroll, size.x, size.y);
	display.setTextureRect(view);

	target->draw(display);

	updateScrollbar();
	target->draw(scrollbar);

	if (active) return;
	target->draw(inactiveShade);
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

	} else if (event.type == Event::EventType::CONNECT_TO_PORT) {

		active = false;

	} else if (event.type == Event::EventType::DISCONNECT_FROM_PORT) {

		active = true;

	}

	if (event.type == Event::EventType::SFML_EVENT && event.payload.sfmlEvent.type == sf::Event::MouseButtonReleased) {
		const int y = event.payload.sfmlEvent.mouseButton.y - pos.y + scroll;
	}
}

void UI::SettingsPanel::updateScrollbar() {
	const float sizeToActualHeight = size.y / ACTUAL_HEIGHT;
	const float scrollToActualHeight = (float) scroll / ACTUAL_HEIGHT;

	scrollbar.setPosition(pos + sf::Vector2f(size.x - 2 - SCROLLBAR_WIDTH, size.y * scrollToActualHeight));
	scrollbar.setSize(sf::Vector2f(SCROLLBAR_WIDTH, size.y * sizeToActualHeight));
}
