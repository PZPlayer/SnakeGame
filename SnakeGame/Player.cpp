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

	void Eat(Player& player, Game& game) {
		player.bodyLenght++;

		sf::Vector2i lastPartCoords = player.snakeBody.back();

		sf::Vector2i newPartCoords = lastPartCoords;
		if (game.direction == PlayerDirection::right) {
			newPartCoords.x -= 1;
		}
		else if (game.direction == PlayerDirection::left) {
			newPartCoords.x += 1;
		}
		else if (game.direction == PlayerDirection::up) {
			newPartCoords.y += 1;
		}
		else if (game.direction == PlayerDirection::down) {
			newPartCoords.y -= 1;
		}
		player.snakeBody.push_back(newPartCoords);

		sf::RectangleShape newPart;
		newPart.setSize({ cellSize, cellSize });
		newPart.setFillColor(sf::Color(240 - static_cast<int>(player.snakeBody.size() - 1) * 5, 240 - static_cast<int>(player.snakeBody.size() - 1) * 5, 240 - static_cast<int>(player.snakeBody.size() - 1) * 5));
		newPart.setPosition(newPartCoords.x * cellSize, newPartCoords.y * cellSize);
		player.snakeParts.push_back(newPart);

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