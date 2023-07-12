#include "SettingsPanel.h"

#include "../Globals.h"

#include <array>

UI::SettingsPanel::SettingsPanel(App::App* app)
	: UIElement(app), scroll(0), currentSelectedBindingMatcher(NO_MATCHER), active(true)
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
	bindingMatchers.reserve(BINDINGS_COUNT);
	bindingClearButtons.reserve(BINDINGS_COUNT);
	for (size_t i = 0; i < BINDINGS_COUNT; i++) {
		const int currentY = BINDING_MARGIN + (BINDING_HEIGHT + BINDING_MARGIN) * i;

		// indices
		indices.emplace_back(std::to_string(i + 1) + "    ->", Global::getFont(), Global::getTextSize());
		indices[i].setFillColor(sf::Color::Black);
		indices[i].move(10, currentY);

		// binding recorders
		bindingMatchers.emplace_back(
			sf::Vector2f(150, currentY),
			sf::Vector2f(200, BINDING_HEIGHT)
		);

		// binding clear buttons
		bindingClearButtons.emplace_back(
			sf::Vector2f(400, currentY),
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
		bindingMatchers[i].render(fullTexture);
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
	if (event.type == Event::EventType::POSITIONED_SFML_EVENT &&
		event.payload.sfmlEvent.type == sf::Event::MouseWheelScrolled &&
		active) {

		scroll = std::max(
			std::min(
				scroll + event.payload.sfmlEvent.mouseWheelScroll.delta * -SCROLL_SPEED,
				ACTUAL_HEIGHT - size.y
			),
			0.0f
		);

	} else if (event.type == Event::EventType::POSITIONED_SFML_EVENT &&
				event.payload.sfmlEvent.type == sf::Event::MouseButtonReleased &&
				active) {

		const sf::Vector2f point = sf::Vector2f(
			event.payload.sfmlEvent.mouseButton.x - pos.x,
			event.payload.sfmlEvent.mouseButton.y - pos.y + scroll
		);

		for (size_t i = 0; i < bindingMatchers.size(); i++) {
			if (bindingMatchers[i].contains(point)) {
				if (bindingMatchers[i].getSelected()) {
					bindingMatchers[i].setSelected(false);
					currentSelectedBindingMatcher = NO_MATCHER;
				} else {
					bindingMatchers[i].setSelected(true);
					currentSelectedBindingMatcher = i;
				}
				continue;
			}

			bindingMatchers[i].setSelected(false);
		}

		for (size_t i = 0; i < bindingClearButtons.size(); i++) {
			if (bindingClearButtons[i].contains(point)) {
				bindingMatchers[i].clearSampleEvent();
				break;
			}
		}

	} else if (event.type == Event::EventType::SFML_EVENT &&
				event.payload.sfmlEvent.type == sf::Event::KeyPressed &&
				currentSelectedBindingMatcher != NO_MATCHER &&
				active) {

		bindingMatchers[currentSelectedBindingMatcher].setSampleEvent(event.payload.sfmlEvent.key);
	
	} else if (event.type == Event::EventType::CONNECT_TO_PORT) {

		active = false;

	} else if (event.type == Event::EventType::DISCONNECT_FROM_PORT) {

		active = true;

	} else if (event.type == Event::EventType::COM_PORT_MESSAGE &&
				!active) {

		int index;

		try {
			index = std::stoi(event.payload.COMMsg);
		} catch (std::invalid_argument e) {
			fprintf(stderr, "Couldn't parse the input: %s\n", event.payload.COMMsg.data());
			return;
		}

		if (index < 0 || index >= bindingMatchers.size()) {
			fprintf(stderr, "Input out of range [0-31]: %i\n", index);
			return;
		}

		const auto& sample = bindingMatchers[index].getSampleEvent();

		if (!sample.has_value()) return;

		auto inputs = Global::convertSFMLEventToWindowsEvent(*sample);
		
		SendInput(inputs.size(), inputs.data(), sizeof(INPUT));

	}
	
}

void UI::SettingsPanel::updateScrollbar() {
	const float sizeToActualHeight = size.y / ACTUAL_HEIGHT;
	const float scrollToActualHeight = (float) scroll / ACTUAL_HEIGHT;

	scrollbar.setPosition(pos + sf::Vector2f(size.x - 2 - SCROLLBAR_WIDTH, size.y * scrollToActualHeight));
	scrollbar.setSize(sf::Vector2f(SCROLLBAR_WIDTH, size.y * sizeToActualHeight));
}
