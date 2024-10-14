#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

namespace SnakeGame {
	struct Orange {
		sf::Vector2i position;
		sf::RectangleShape shape;
	};
}