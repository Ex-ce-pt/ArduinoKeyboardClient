#include "BindingMatcher.h"

#include "../../Globals.h"

static std::string sfmlKeyEventToString(const sf::Event::KeyEvent& event) {
	std::stringstream ss;

	if (event.control &&
		event.code != sf::Keyboard::LControl &&
		event.code != sf::Keyboard::RControl) {

		ss << "ctrl+";

	}

	if (event.alt &&
		event.code != sf::Keyboard::LAlt &&
		event.code != sf::Keyboard::RAlt) {

		ss << "alt+";

	}

	if (event.shift &&
		event.code != sf::Keyboard::LShift &&
		event.code != sf::Keyboard::RShift) {

		ss << "shift+";

	}

	ss << Global::sfmlKeycodeToCString(event.code);

	std::string res;
	ss >> res;
	return res;
}

UI::BindingSettings::BindingMatcher::BindingMatcher(const sf::Vector2f& pos, const sf::Vector2f& size)
	: UIElement(nullptr), selected(false)
{
	this->pos = pos;
	this->size = size;

	bg.setPosition(pos);
	bg.setSize(size);
	bg.setOutlineThickness(2);

	setSelected(false);

	text = sf::Text("", Global::getFont(), Global::getTextSize());
	text.setFillColor(sf::Color::Black);
	text.move(pos + sf::Vector2f(5, 5));
}

void UI::BindingSettings::BindingMatcher::render(std::shared_ptr<sf::RenderTarget> target) {
	target->draw(bg);
	target->draw(text);
}

void UI::BindingSettings::BindingMatcher::onEvent(const Event& event) { }

void UI::BindingSettings::BindingMatcher::setSelected(bool flag) {
	selected = flag;
	bg.setOutlineColor(flag ? sf::Color(200, 200, 200) : sf::Color::Black);
}

void UI::BindingSettings::BindingMatcher::setSampleEvent(const sf::Event::KeyEvent& e) {
	sampleEvent = e;
	text.setString(sfmlKeyEventToString(e));
}

void UI::BindingSettings::BindingMatcher::clearSampleEvent() {
	sampleEvent.reset();
	text.setString("");
}

bool UI::BindingSettings::BindingMatcher::getSelected() const {
	return selected;
}

const std::optional<sf::Event::KeyEvent>& UI::BindingSettings::BindingMatcher::getSampleEvent() const {
	return sampleEvent;
}
