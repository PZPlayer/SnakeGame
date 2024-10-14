#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

namespace SnakeGame {
	struct Player
	{
		int bodyLenght = 3;
		sf::Vector2i snakeHead;
		std::vector<sf::Vector2i> snakeBody;
		std::vector<sf::RectangleShape> snakeParts;
	};

	struct Game;

	void InitPlayer(Player& player);
	void DrawPlayer(sf::RenderWindow& window, Player& player);
}