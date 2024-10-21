#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

namespace SnakeGame {
	sf::Vector2i GetRandomPosition();

	bool ifTouchObj(sf::Vector2i pos1, sf::Vector2i pos2, float size1, float size2);

	struct Game;

	void SetTextOrigin(sf::Text text, float x, float y);
	void SetRectangleOrigin(sf::RectangleShape shape, float x, float y);
}