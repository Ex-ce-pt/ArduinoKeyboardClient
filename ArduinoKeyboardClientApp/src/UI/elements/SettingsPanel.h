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

		std::shared_ptr<sf::RenderTexture> fullTexture;
		sf::RectangleShape bg;
		sf::Sprite display;

		int scroll;
		sf::RectangleShape scrollbar;
		
		std::vector<sf::Text> indices;
		std::vector<std::string> bindings;
		std::vector<BindingSettings::BindingRecorder> bindingRecorders;
		std::vector<BindingSettings::BindingClearButton> bindingClearButtons;
		
		bool active;
		sf::RectangleShape inactiveShade;

		void updateScrollbar();
		
		static int getRowIndexByY(int y);

	public:
		SettingsPanel(App::App* app);

		void render(std::shared_ptr<sf::RenderTarget> target) override;
		void onEvent(const Event& event) override;
	};

}
