#pragma once

#include <SFML/Graphics.hpp>

#include "../Event.h"

namespace App { class App; }

namespace UI {

	class UIElement {
	protected:
		App::App* app;
		sf::Vector2f pos;
		sf::Vector2f size;
		int layer;

	public:
		UIElement(App::App* app);

		virtual void render(std::shared_ptr<sf::RenderWindow> window) = 0;
		virtual void onEvent(const Event& event);

		bool intersects(const sf::Vector2f& point) const;

		const sf::Vector2f& getPos() const;
		const sf::Vector2f& getSize() const;
		int getLayer() const;
	};

	bool compareElementsByLayer(std::shared_ptr<UIElement> first, std::shared_ptr<UIElement> second);

	void initFont();
	void deleteFont();
	const sf::Font& getFont();

}