#pragma once

#include "UIElement.h"

namespace UI {

	class PortComboBox : public UIElement {
	public:
		const int NONE = -1;

	private:
		const int ITEM_HEIGHT = 35;

		sf::RectangleShape bg;
		sf::Text visibleText;
		int selectedItem;
		bool opened;
		std::unique_ptr<sf::Text[]> items;
		size_t itemsCount;
		bool active;
		sf::RectangleShape inactiveShade;

		void updateMenu();
		void updateVisibleText();

	public:
		PortComboBox(App::App* app);

		void render(std::shared_ptr<sf::RenderWindow> window) const override;
		void onEvent(const Event& event) override;
	};

}
