#include "Player.h"
#include "Game.h"

namespace SnakeGame {
	void InitPlayer(Player& player) {
		for (int i = 0; i < player.bodyLenght; ++i) {
			player.snakeBody.push_back(sf::Vector2i(player.snakeHead.x - i - 1, player.snakeHead.y));
		}

		for (int i = 0; i < player.snakeBody.size(); ++i) {
			sf::RectangleShape part;
			part.setSize({ cellSize, cellSize });
			part.setFillColor(sf::Color::Color(240 - i * 5, 240 - i * 5, 240 - i * 5));
			part.setPosition(player.snakeBody[i].x * cellSize, player.snakeBody[i].y * cellSize);
			player.snakeParts.push_back(part);
		}
	}

	void DrawPlayer(sf::RenderWindow& window, Player& player) {
		for (int i = 1; i < player.snakeBody.size(); ++i) {
			player.snakeParts[i].setPosition(player.snakeBody[i].x * cellSize, player.snakeBody[i].y * cellSize);
		}
		for (const auto& part : player.snakeParts) {
			window.draw(part);
		}
	}
}