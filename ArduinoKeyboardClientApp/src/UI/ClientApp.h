#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "elements/UIElement.h"
#include "Event.h"
#include "../COM/COMPort.h"

namespace App {

	class App {
	private:
		std::shared_ptr<sf::RenderWindow> window;
		sf::RectangleShape background;
		std::vector<std::shared_ptr<UI::UIElement>> elements;
		COMPort::COMPort port;

		void invokeEvent(const UI::Event& event);
		void render();

	public:
		App();

		void buildUI();
		void startLoop();

		void setPortID(ULONG portID);
		void invokeCOMPortScan();
		void invokeConnectToPort();
		void invokeDisconnectFromPort();
	};

}
