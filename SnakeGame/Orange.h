#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

namespace SnakeGame {
	struct Orange {
		sf::Vector2i position;
		sf::RectangleShape shape;
	};

	struct Game;

	void InitOrange(Orange& orange);
	void SetRandomPos(Orange& orange);
	void DrawOrange(sf::RenderWindow& window, Orange& orange);
}