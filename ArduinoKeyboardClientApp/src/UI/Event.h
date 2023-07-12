#pragma once

#include <SFML/Window/Event.hpp>
#include "../COM/COMPort.h"

namespace UI {
	
	struct Event {

		enum class EventType {
			SFML_EVENT,
			POSITIONED_SFML_EVENT,
			COM_PORT_SCAN_STATUS,
			CONNECT_TO_PORT,
			DISCONNECT_FROM_PORT,
			COM_PORT_MESSAGE
		};

		union EventPayload {
			int empty;
			sf::Event sfmlEvent;
			COMPort::PortScanStatus COMPortScanStatus;
			std::string COMMsg;

			EventPayload(int _0) : empty(_0) { }
			EventPayload(sf::Event _1) : sfmlEvent(_1) { }
			EventPayload(COMPort::PortScanStatus _2) : COMPortScanStatus(_2) { }
			EventPayload(const std::string& _3) : COMMsg(_3) { }
			~EventPayload() { }
		};

		EventType type;
		EventPayload payload;

		sf::Vector2f getEventCoordinates() const;
	};


}