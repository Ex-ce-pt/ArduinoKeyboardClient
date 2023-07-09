#pragma once

#include "../UIElement.h"

namespace UI::BindingSettings {
	

	/// <summary>
	/// Doesn't do anything by itself, is designed to be a renderer and a collision mechanism.
	/// Parent handles everything event-related.
	/// </summary>
	class BindingMatcher : public UIElement {
	private:
		sf::RectangleShape bg;
		sf::Text text;
		bool selected;
		sf::Event::KeyEvent sampleEvent;
		bool sampleEventDefined;

	public:
		BindingMatcher(const sf::Vector2f& pos, const sf::Vector2f& size);

		void render(std::shared_ptr<sf::RenderTarget> target) override;
		void onEvent(const Event& event) override;

		void setSelected(bool flag);
		void setSampleEvent(const sf::Event::KeyEvent& e);
		void clearSampleEvent();

		bool getSelected() const;
		bool matchesSampleEvent(const sf::Event::KeyEvent& e) const;
	};

}
