#include "Event.h"

sf::Vector2f UI::Event::getEventCoordinates() const {
    if (type != EventType::SFML_EVENT) {
        fprintf(stderr, "Can't get coordinates of an event of a type other than SFML.\n");
        abort();
    }

    switch (payload.sfmlEvent.type) {
    case sf::Event::MouseButtonPressed:
    case sf::Event::MouseButtonReleased:
        return sf::Vector2f(payload.sfmlEvent.mouseButton.x, payload.sfmlEvent.mouseButton.y);

    case sf::Event::MouseWheelScrolled:
        return sf::Vector2f(payload.sfmlEvent.mouseWheelScroll.x, payload.sfmlEvent.mouseWheelScroll.y);

    default:
        {
            fprintf(stderr, "Undefined event.\n");
            abort();
        }
    }
}