#include "Game.h"
#include "cassert"

namespace SnakeGame {

	void Start(Game& game) {
		game.player.snakeHead = { numRows / 2, numCols / 2 };
		InitOrange(game.orange);
		game.pointsText.position = {screenX / 2, 50};
		assert(game.font.loadFromFile("Resources/Fonts/Roboto-Bold.ttf"));
		game.pointsText.font = game.font;
		InitText(game.pointsText);
        #pragma region BodyCreate
		InitPlayer(game.player);
#pragma endregion
	}

	void StartMenu(Game& game) {

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
			case PlayerDirection::right:
				game.player.snakeHead.x++;
				break;
			case PlayerDirection::left:
				game.player.snakeHead.x--;
				break;
			case PlayerDirection::up:
				game.player.snakeHead.y--;
				break;
			case PlayerDirection::down:
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
				GameOver(window, game);
			}
		}
#pragma endregion
		if (ifTouchObj(game.player.snakeHead, game.orange.position, 1, 1)) {
			bool placed = false;
			SetRandomPos(game.orange);
			while (!placed)
			{
				for (int i = 0; i <= game.player.snakeBody.size() - 1; ++i) {
					if (game.player.snakeBody[i] == game.orange.position) {
						SetRandomPos(game.orange);
					}
					else
					{
						placed = true;
					}
				}
			}
			Eat(game.player, game);
			game.orangeCount += game.pointAdder;
			placed = false;
		}

		game.pointsText.strText = std::to_string(game.orangeCount);
	}

	bool operator<(const Enemy& left, const Enemy& right) {
		return left.Score > right.Score;
	}

	void GameOver(sf::RenderWindow& window, Game& game) {
		if (game.bestScore == 0) game.enemies[2] = { game.bestScore, "<YOU>" };
		for (size_t i = 0; i < sizeof(game.enemies) / sizeof(game.enemies[0]); ++i) {
			if (game.enemies[i].Name == "<YOU>") {
				game.enemies[i] = { game.bestScore, "<YOU>" };
			}
		}

		std::sort(std::begin(game.enemies), std::end(game.enemies));

		game.deathPanels[0].pos = {screenX / 2, screenY / 2};
		game.deathPanels[0].size = {300, 400};

		game.deathPanels[1].pos = { screenX / 2, screenY / 2 };
		game.deathPanels[1].size = { 270, 370 };
		game.deathPanels[1].color = sf::Color::Black;

		game.DeathText[0].position = { screenX / 2, screenY / 2 - 160 };
		game.DeathText[0].font = game.font;
		game.DeathText[0].textSize = 20;
		game.DeathText[0].strText = "Game Over";

		game.DeathText[1].font = game.font;
		game.DeathText[1].textSize = 14;
		if (game.playerState != PlayerState::Dead) {
			game.DeathText[1].strText = "";
			for (int i = 0; i < sizeof(game.enemies) / sizeof(game.enemies[0]); i++) {
				game.DeathText[1].strText = game.DeathText[1].strText + std::to_string(i + 1) + ".  |" + game.enemies[i].Name + "|  SCORE:" + std::to_string(game.enemies[i].Score) + "\n ";
			}
		}
		game.DeathText[1].textColor = sf::Color::Green;
		game.DeathText[1].position = { screenX / 2 , screenY / 2 - 100};
		
		for (int i = 0; i < sizeof(game.deathPanels) / sizeof(game.deathPanels[0]); ++i) InitPanel(game.deathPanels[i], game);
		for (int i = 0; i < sizeof(game.DeathText) / sizeof(game.DeathText[0]); ++i) InitText(game.DeathText[i]);

		game.playerState = PlayerState::Dead;
	}

	void Draw(Game& game, sf::RenderWindow& window) {
		for (int i = 0; i < sizeof(game.deathPanels) / sizeof(game.deathPanels[0]); ++i) DrawPanel(game.deathPanels[i], window);
		for (int i = 0; i < sizeof(game.DeathText) / sizeof(game.DeathText[0]); ++i) DrawText(window, game.DeathText[i]);
		DrawOrange(window, game.orange);
		DrawText(window, game.pointsText);
        #pragma region BodyDraw
		DrawPlayer(window, game.player);
#pragma endregion
	}
}