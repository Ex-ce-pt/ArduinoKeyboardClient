#pragma once

#include "../UIElement.h"

#include <optional>

namespace UI::BindingSettings {
	
	class BindingMatcher : public UIElement {
	private:
		sf::RectangleShape bg;
		sf::Text text;
		bool selected;
		std::optional<sf::Event::KeyEvent> sampleEvent;

	public:
		BindingMatcher(const sf::Vector2f& pos, const sf::Vector2f& size);

		void render(std::shared_ptr<sf::RenderTarget> target) override;
		void onEvent(const Event& event) override;

		void setSelected(bool flag);
		void setSampleEvent(const sf::Event::KeyEvent& e);
		void clearSampleEvent();

		bool getSelected() const;
		const std::optional<sf::Event::KeyEvent>& getSampleEvent() const;
	};

}
