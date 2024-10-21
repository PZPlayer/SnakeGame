#pragma once
#include "Math.h"
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	struct Panel
	{
		sf::Vector2f pos;
		sf::Vector2i size;
		sf::Color color = sf::Color::White;
		sf::RectangleShape shape;
	};

	struct Game;

	void InitPanel(Panel& panel, Game& game);
	void DrawPanel(Panel& panel, sf::RenderWindow& window);
}