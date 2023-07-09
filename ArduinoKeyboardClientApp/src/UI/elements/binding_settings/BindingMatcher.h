#pragma once

#include "../UIElement.h"

namespace UI::BindingSettings {
	
	class BindingMatcher : public UIElement {
	private:
		sf::RectangleShape bg;
		sf::Text text;
		bool selected;
		sf::Event::KeyEvent sampleEvent;
		bool sampleEventDefined;
		std::unique_ptr<std::thread> listenerThread;
		std::atomic_bool listenerThreadRunning;

	public:
		BindingMatcher(const sf::Vector2f& pos, const sf::Vector2f& size);
		BindingMatcher(const BindingMatcher& other);
		~BindingMatcher();

		void render(std::shared_ptr<sf::RenderTarget> target) override;
		void onEvent(const Event& event) override;

		void setSelected(bool flag);
		void setSampleEvent(const sf::Event::KeyEvent& e);
		void clearSampleEvent();

		bool getSelected() const;
		bool matchesSampleEvent(const sf::Event::KeyEvent& e) const;

		void startListening();
		void stopListening();
	};

}
