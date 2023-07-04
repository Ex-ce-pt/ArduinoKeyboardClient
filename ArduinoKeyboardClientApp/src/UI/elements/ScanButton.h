#pragma once

#include "UIElement.h"

namespace UI {

	class ScanButton : public UIElement {
	private:
		sf::RectangleShape bg;
		sf::Text text;

	public:
		ScanButton(App::App* app);

		void render(std::shared_ptr<sf::RenderWindow> window) const override;
		void onEvent(const Event& event) override;
	};

}
