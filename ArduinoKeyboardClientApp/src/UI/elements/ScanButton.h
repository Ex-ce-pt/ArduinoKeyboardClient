#pragma once

#include "UIElement.h"

namespace UI {

	class ScanButton : public UIElement {
	private:
		sf::RectangleShape bg;
		sf::Text text;
		bool active;
		sf::RectangleShape inactiveShade;

	public:
		ScanButton(App::App* app);

		void render(std::shared_ptr<sf::RenderTarget> target) override;
		void onEvent(const Event& event) override;
	};

}
