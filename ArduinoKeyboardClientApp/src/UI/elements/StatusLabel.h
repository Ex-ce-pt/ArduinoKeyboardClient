#pragma once

#include "UIElement.h"

namespace UI {

	class StatusLabel : public UIElement {
	private:
		sf::Text text;

	public:
		StatusLabel(App::App* app);

		void render(std::shared_ptr<sf::RenderWindow> window) override;
		void onEvent(const Event& event) override;

		void clear();
	};

}
