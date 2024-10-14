#include "Game.h"

namespace SnakeGame {

	void Start(Game& game) {
		game.player.snakeHead = { numRows / 2, numCols / 2 };
		game.orange.shape.setFillColor(sf::Color::Color(255, 165, 0));
		game.orange.shape.setSize({ cellSize, cellSize });
		game.orange.position = GetRandomPosition();
		game.orange.shape.setPosition((float)game.orange.position.x * cellSize, (float)game.orange.position.y * cellSize);
        #pragma region BodyCreate
		InitPlayer(game.player);
#pragma endregion
	}

	void Update(Game& game, float deltaTime, sf::RenderWindow& window) {
        #pragma region KeyCheck
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			game.direction = PlayerDirection::right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			game.direction = PlayerDirection::left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			game.direction = PlayerDirection::up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			game.direction = PlayerDirection::down;
		}

    #pragma endregion
        #pragma region Movement
		if (game.moveTimer.getElapsedTime().asSeconds() >= game.delay)
		{
			sf::Vector2i lastHeadPos = game.player.snakeHead;
			switch (game.direction)
			{
			case right:
				game.player.snakeHead.x++;
				break;
			case left:
				game.player.snakeHead.x--;
				break;
			case up:
				game.player.snakeHead.y--;
				break;
			case down:
				game.player.snakeHead.y++;
				break;
			default:
				break;
			}

			game.player.snakeBody.insert(game.player.snakeBody.begin(), lastHeadPos);

			game.player.snakeBody.erase(game.player.snakeBody.end() - 1);

			game.player.snakeHead.x = std::max(0, std::min(game.player.snakeHead.x, numCols - 1));
			game.player.snakeHead.y = std::max(0, std::min(game.player.snakeHead.y, numRows - 1));


			game.player.snakeParts[0].setPosition(float(lastHeadPos.x * cellSize), float(lastHeadPos.y * cellSize));

			game.moveTimer.restart();
		}
#pragma endregion
        #pragma region CheckIfDeath
		for (int i = 0; i < game.player.snakeBody.size(); ++i) {
			if (game.player.snakeBody[i].x == game.player.snakeHead.x && game.player.snakeBody[i].y == game.player.snakeHead.y) {
				GameOver(window);
			}
		}
#pragma endregion
	}

	void GameOver(sf::RenderWindow& window) {
		window.close();
	}

	void Draw(Game& game, sf::RenderWindow& window) {
		window.draw(game.orange.shape);
        #pragma region BodyDraw
		DrawPlayer(window, game.player);
#pragma endregion
	}
}