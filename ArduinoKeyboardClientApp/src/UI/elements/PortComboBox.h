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
		std::vector<ULONG> portIDs;
		std::unique_ptr<sf::Text[]> items;
		bool active;
		sf::RectangleShape inactiveShade;

		void updateMenu();
		void updateVisibleText();

	public:
		PortComboBox(App::App* app);

		void render(std::shared_ptr<sf::RenderWindow> window) override;
		void onEvent(const Event& event) override;
	};

}
