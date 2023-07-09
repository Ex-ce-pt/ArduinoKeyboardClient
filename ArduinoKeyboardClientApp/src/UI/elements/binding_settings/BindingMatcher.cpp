#include "BindingMatcher.h"

#include "../../Globals.h"

#define IS_WINDOWS_KEY_DOWN(k) (GetKeyState(k) & 0x8000)

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
	: UIElement(nullptr), selected(false), sampleEventDefined(false), listenerThreadRunning(false)
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

/// <summary>
/// The compiler throws an errore for some reason.
/// Apparently the vector class is somehow using this constructor and std::atomic_bool doesn't have a copy constructor itself.
/// </summary>
UI::BindingSettings::BindingMatcher::BindingMatcher(const BindingMatcher& other)
	: UIElement(nullptr), selected(other.selected), sampleEventDefined(other.sampleEventDefined), listenerThreadRunning((bool) other.listenerThreadRunning),
	bg(other.bg), text(other.text), sampleEvent(other.sampleEvent)
{ }

UI::BindingSettings::BindingMatcher::~BindingMatcher() {
	stopListening();
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
	sampleEventDefined = true;
	text.setString(sfmlKeyEventToString(e));
}

void UI::BindingSettings::BindingMatcher::clearSampleEvent() {
	sampleEventDefined = false;
	text.setString("");
}

bool UI::BindingSettings::BindingMatcher::getSelected() const {
	return selected;
}

bool UI::BindingSettings::BindingMatcher::matchesSampleEvent(const sf::Event::KeyEvent& e) const {
	return (sampleEvent.control == e.control &&
			sampleEvent.alt == e.alt &&
			sampleEvent.shift == e.shift &&
			sampleEvent.code == e.code) && sampleEventDefined;
}

void UI::BindingSettings::BindingMatcher::startListening() {
	listenerThreadRunning = true;
	listenerThread = std::make_unique<std::thread>([=]() {
		if (!sampleEventDefined) return;

		const int keycode = Global::sfmlKeycodeToWindowsKeycode(sampleEvent.code);
		const auto delay = std::chrono::milliseconds(10);

		while (listenerThreadRunning) {
			if (IS_WINDOWS_KEY_DOWN(keycode)) {
				printf("key %i\n", keycode);
			}
			//std::this_thread::sleep_for(delay);
		}
	});
}

void UI::BindingSettings::BindingMatcher::stopListening() {
	listenerThreadRunning = false;
	if (listenerThread) listenerThread->join();
	listenerThread.reset();
}
