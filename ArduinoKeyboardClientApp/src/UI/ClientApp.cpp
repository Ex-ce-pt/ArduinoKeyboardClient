#include "ClientApp.h"

#include <iostream>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "elements/UIElement.h"
#include "elements/ConnectButton.h"
#include "elements/DisconnectButton.h"
#include "elements/ScanButton.h"
#include "elements/PortComboBox.h"
#include "elements/StatusLabel.h"
#include "elements/SettingsPanel.h"

App::App::App() {
    port.onMessageReceived([=](std::string msg) {
        UI::Event e {
            UI::Event::EventType::COM_PORT_MESSAGE,
            { msg }
        };
        invokeEvent(e);
    });

    return;
    Sleep(3000);

    INPUT i[2] = { 0 };

    i[0].type = INPUT_KEYBOARD;
    i[0].ki.wVk = 'S';
    i[0].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
    
    i[1].type = INPUT_KEYBOARD;
    i[1].ki.wVk = 'S';
    i[1].ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;

    SendInput(1, i, sizeof(INPUT));
    SendInput(1, i+1, sizeof(INPUT));
}

void App::App::buildUI() {
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(600, 400), "Arduino COM Keyboard", sf::Style::Close);

    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(600, 400));
    background.setFillColor(sf::Color(200, 200, 200));

    elements.push_back(std::make_shared<UI::ConnectButton>(this));
    elements.push_back(std::make_shared<UI::DisconnectButton>(this));
    elements.push_back(std::make_shared<UI::ScanButton>(this));
    elements.push_back(std::make_shared<UI::PortComboBox>(this));
    elements.push_back(std::make_shared<UI::StatusLabel>(this));
    elements.push_back(std::make_shared<UI::SettingsPanel>(this));
    
    std::sort(elements.begin(), elements.end(), UI::compareElementsByLayer);
}

void App::App::startLoop() {

    while (window->isOpen()) {

        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                {
                    window->close();
                }
                break;

            case sf::Event::MouseButtonReleased:
            case sf::Event::MouseWheelScrolled:
                {
                    UI::Event e {
                        UI::Event::EventType::POSITIONED_SFML_EVENT,
                        { event }
                    };

                    invokeEvent(e);
                }
                break;

            case sf::Event::KeyPressed:
                {
                    UI::Event e {
                        UI::Event::EventType::SFML_EVENT,
                        { event }
                    };
                    
                    invokeEvent(e);
                }
                break;
            }
        }

        window->clear();

        render();

        window->display();
    }

}

void App::App::invokeEvent(const UI::Event& event) {
    if (event.type == UI::Event::EventType::POSITIONED_SFML_EVENT) {

        const sf::Vector2f pos = event.getEventCoordinates();
        for (const auto& i : elements) {
            if (i->contains(pos)) {
                i->onEvent(event);
                return;
            }
        }

    } else {

        for (const auto& i : elements) {
            i->onEvent(event);
        }

    }
}

void App::App::render() {
    window->draw(background);

    for (const auto& i : elements) {
        i->render(window);
    }

}

void App::App::setPortID(ULONG portID) {
    port.setPortID(portID);
}

void App::App::invokeCOMPortScan() {
    UI::Event event {
        UI::Event::EventType::COM_PORT_SCAN_STATUS,
        { COMPort::scanForPorts() }
    };
    invokeEvent(event);
}

void App::App::invokeConnectToPort() {
    if (port.getPortID() == NULL) return;

    UI::Event event {
        UI::Event::EventType::CONNECT_TO_PORT,
        { 0 }
    };
    invokeEvent(event);

    port.open();
}

void App::App::invokeDisconnectFromPort() {
    if (port.getPortID() == NULL) return;

    UI::Event event {
        UI::Event::EventType::DISCONNECT_FROM_PORT,
        { 0 }
    };
    invokeEvent(event);

    port.close();
}
