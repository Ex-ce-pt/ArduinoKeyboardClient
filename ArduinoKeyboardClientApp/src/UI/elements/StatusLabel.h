#pragma once

#include "UIElement.h"

namespace UI {

	class StatusLabel : public UIElement {
	private:
		sf::Text text;

	public:
		StatusLabel(App::App* app);

		void render(std::shared_ptr<sf::RenderTarget> target) override;
		void onEvent(const Event& event) override;

		void clear();
	};

}
