#pragma once

#include "UIElement.h"

#include "binding_settings/BindingRecorder.h"
#include "binding_settings/BindingClearButton.h"

namespace UI {

	class SettingsPanel : public UIElement {
	private:
		static const int SCROLLBAR_WIDTH = 10;
		static const int SCROLL_SPEED = 15;
		static const int BINDINGS_COUNT = 32;
		static const int BINDING_HEIGHT = 35;
		static const int BINDING_MARGIN = 5;
		static const int ACTUAL_HEIGHT = BINDING_MARGIN + (BINDING_HEIGHT + BINDING_MARGIN) * BINDINGS_COUNT;

		sf::RenderTexture fullTexture;
		sf::RectangleShape bg;
		sf::Sprite display;

		int scroll;
		sf::RectangleShape scrollbar;
		
		std::unique_ptr<sf::Text[]> indices;
		std::unique_ptr<std::string[]> bindings;
		std::unique_ptr<BindingSettings::BindingRecorder[]> bindingRecorders;
		std::unique_ptr<BindingSettings::BindingClearButton[]> bindingClearButtons;
		
		bool active;
		sf::RectangleShape inactiveShade;

		void updateScrollbar();

	public:
		SettingsPanel(App::App* app);

		void render(std::shared_ptr<sf::RenderWindow> window) override;
		void onEvent(const Event& event) override;
	};

}
