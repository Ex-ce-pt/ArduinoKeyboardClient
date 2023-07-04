#pragma once

#include "UIElement.h"

namespace UI {

	class ConnectButton : public UIElement {
	private:
		sf::RectangleShape bg;
		sf::Text text;
		bool active;
		sf::RectangleShape inactiveShade;

	public:
		ConnectButton(App::App* app);

		void render(std::shared_ptr<sf::RenderWindow> window) override;
		void onEvent(const Event& event) override;
	};

}
