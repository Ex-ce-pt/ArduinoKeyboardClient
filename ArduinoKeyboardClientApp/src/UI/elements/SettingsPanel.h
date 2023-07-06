#pragma once

#include "UIElement.h"

namespace UI {

	class SettingsPanel : public UIElement {
	private:
		const int SCROLLBAR_WIDTH = 10;
		const int SCROLL_SPEED = 15;
		const int BINDINGS_COUNT = 32;
		const int BINDING_HEIGHT = 35;
		const int BINDING_MARGIN = 5;
		const int ACTUAL_HEIGHT = BINDING_MARGIN + (BINDING_HEIGHT + BINDING_MARGIN) * BINDINGS_COUNT;

		sf::RenderTexture fullTexture;
		sf::RectangleShape bg;
		sf::Sprite display;
		int scroll;
		sf::RectangleShape scrollbar;
		std::unique_ptr<sf::Text[]> indices;
		bool active;
		sf::RectangleShape inactiveShade;

		void updateScrollbar();

	public:
		SettingsPanel(App::App* app);

		void render(std::shared_ptr<sf::RenderWindow> window) override;
		void onEvent(const Event& event) override;
	};

}
