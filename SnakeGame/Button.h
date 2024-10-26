#pragma once
#include "Math.h"
#include <functional>
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	struct Button
	{
		sf::Text buttonText;
		sf::Vector2f pos;
		sf::Vector2f size;
		std::string text;
		int textSize = 16;
		sf::Color baseColor = sf::Color::Color(225, 225, 225);
		sf::Color baseTextColor = sf::Color::Black;
		sf::Color higlightedColor = sf::Color::White;
		sf::Color pressedColor = sf::Color::Green;
		sf::RectangleShape shape;
		bool ifFirstTime = true;
	};

	struct Game;

	void InitButton(Button& button, Game& game);
	void IfPoint(Button& button, Game& game, sf::Vector2f mousePos, bool isMouseClicked, std::function<void(Button&, Game&)> callback);
	void DrawButton(sf::RenderWindow& window, Button& button);
}