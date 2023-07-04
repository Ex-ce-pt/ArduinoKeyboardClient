#pragma once

#include "UIElement.h"

namespace UI {

	class SettingsPanel : public UIElement {
	private:
		const int BINDINGS_COUNT = 32;
		const int SCROLLBAR_WIDTH = 10;
		const int BINDING_HEIGHT = 35;
		const int BINDING_MARGIN = 5;
		const int ACTUAL_HEIGHT = (BINDING_HEIGHT + BINDING_MARGIN * 2) * BINDINGS_COUNT;

		sf::RenderTexture fullTexture;
		sf::RectangleShape bg;
		sf::Sprite display;
		int scroll;
		sf::RectangleShape scrollbar;

		void updateScrollbar();

	public:
		SettingsPanel(App::App* app);

		void render(std::shared_ptr<sf::RenderWindow> window) override;
		void onEvent(const Event& event) override;
	};

}
