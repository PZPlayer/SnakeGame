#include "Game.h"
#include "cassert"

namespace SnakeGame {

	void Start(Game& game) {
		if (game.bestScore == 0) game.enemies[2] = { game.bestScore, "<YOU>" };
		game.ifDead = false;
		game.orangeCount = 0;
		game.saveTimer.restart();
		game.direction = PlayerDirection::right;
		game.player.snakeHead = { numRows / 2, numCols / 2 };
		game.player.bodyLenght = 3;
		game.player.snakeBody.clear();
		game.player.snakeParts.clear();
		InitOrange(game.orange);
		game.pointsText.position = {screenX / 2, 50};
		assert(game.font.loadFromFile("Resources/Fonts/Roboto-Bold.ttf"));
		game.pointsText.font = game.font;
		InitText(game.pointsText);
        #pragma region BodyCreate
		InitPlayer(game.player);
#pragma endregion
        #pragma region PauseMenuInit
		game.pausePanels[0].pos = { screenX / 2, screenY / 2 };
		game.pausePanels[0].size = { 300, 400 };

		game.pausePanels[1].pos = { screenX / 2, screenY / 2 };
		game.pausePanels[1].size = { 270, 370 };
		game.pausePanels[1].color = sf::Color::Black;

		game.pauseText.position = { screenX / 2, screenY / 2 - 160 };
		game.pauseText.font = game.font;
		game.pauseText.textSize = 20;
		game.pauseText.strText = "Paused";

		game.pauseButtons[0].pos = { screenX / 2, screenY / 2 };
		game.pauseButtons[0].size = { 150, 75 };
		game.pauseButtons[0].textSize = 30;
		game.pauseButtons[0].text = "Continue";

		game.pauseButtons[1].pos = { screenX / 2, screenY / 2 + 90 };
		game.pauseButtons[1].size = { 150, 75 };
		game.pauseButtons[1].textSize = 30;
		game.pauseButtons[1].text = "Menu";

		for (int i = 0; i < sizeof(game.pausePanels) / sizeof(game.pausePanels[0]); ++i) InitPanel(game.pausePanels[i], game);
		for (int i = 0; i < sizeof(game.pauseButtons) / sizeof(game.pauseButtons[0]); ++i) InitButton(game.pauseButtons[i], game);
		InitText(game.pauseText);
#pragma endregion

	}

	void Menu(Game& game) {
		game.menuText.strText = "Snake Game";
		game.menuText.textSize = 50;
		game.menuText.position = {screenX / 2, screenY / 4};
		InitText(game.menuText);
	}

	void Restart(Button& button, Game& game) {
		if (game.ifDead) {
			Start(game);
			game.DeathText[1].strText = "";
		}
	}

	void Continue(Button& button, Game& game) {
		if (!game.ifDead) {
			game.ifPaused = false;
		}
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			game.ifPaused = !game.ifPaused;
		}
		game.mousePos = sf::Mouse::getPosition(window);
		game.isMouseClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    #pragma endregion
        #pragma region Movement
		if (game.moveTimer.getElapsedTime().asSeconds() >= game.delay && !game.ifDead && !game.ifPaused)
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
			if (game.player.snakeBody[i].x == game.player.snakeHead.x && game.player.snakeBody[i].y == game.player.snakeHead.y && game.saveTimer.getElapsedTime().asSeconds() >= 1 && !game.ifDead) {
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
		if (game.orangeCount > game.bestScore) game.bestScore = game.orangeCount;

		game.ifDead = true;
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
		
		for (int i = 0; i < sizeof(game.enemies) / sizeof(game.enemies[0]); i++) {
			game.DeathText[1].strText = game.DeathText[1].strText + std::to_string(i + 1) + ".  |" + game.enemies[i].Name + "|  SCORE:" + std::to_string(game.enemies[i].Score) + "\n ";
		}
		
		game.DeathText[1].textColor = sf::Color::Green;
		game.DeathText[1].position = { screenX / 2 , screenY / 2 - 100};

		game.deathButtons[0].pos = { screenX / 2, screenY / 2};
		game.deathButtons[0].size = { 150, 75 };
		game.deathButtons[0].textSize = 30;
		game.deathButtons[0].text = "Try Again";

		game.deathButtons[1].pos = { screenX / 2, screenY / 2 + 90};
		game.deathButtons[1].size = { 150, 75 };
		game.deathButtons[1].textSize = 30;
		game.deathButtons[1].text = "Menu";
		
		for (int i = 0; i < sizeof(game.deathButtons) / sizeof(game.deathButtons[0]); ++i) InitButton(game.deathButtons[i], game);
		for (int i = 0; i < sizeof(game.deathPanels) / sizeof(game.deathPanels[0]); ++i) InitPanel(game.deathPanels[i], game);
		for (int i = 0; i < sizeof(game.DeathText) / sizeof(game.DeathText[0]); ++i) InitText(game.DeathText[i]);

		game.playerState = PlayerState::Dead;
	}

	void Draw(Game& game, sf::RenderWindow& window) {
		DrawOrange(window, game.orange);
		DrawText(window, game.pointsText);
        #pragma region BodyDraw
		DrawPlayer(window, game.player);
#pragma endregion

		if (game.gameState == GameState::Menu) {
			DrawText(window, game.menuText);
		}

		if (game.ifDead) {
			for (int i = 0; i < sizeof(game.deathPanels) / sizeof(game.deathPanels[0]); ++i) DrawPanel(game.deathPanels[i], window);
			for (int i = 0; i < sizeof(game.DeathText) / sizeof(game.DeathText[0]); ++i) DrawText(window, game.DeathText[i]);
			for (int i = 0; i < sizeof(game.deathButtons) / sizeof(game.deathButtons[0]); ++i) DrawButton(window, game.deathButtons[i]);
		}

		if (game.ifPaused) {
			for (int i = 0; i < sizeof(game.pausePanels) / sizeof(game.pausePanels[0]); ++i) DrawPanel(game.pausePanels[i], window);
			for (int i = 0; i < sizeof(game.pauseButtons) / sizeof(game.pauseButtons[0]); ++i) DrawButton(window, game.pauseButtons[i]);
			DrawText(window, game.pauseText);
		}

        #pragma region ButtonCheck
		IfPoint(game.deathButtons[0], game, { (float)game.mousePos.x, (float)game.mousePos.y }, game.isMouseClicked, [=](Button& button, Game& game) {
			Restart(game.deathButtons[0], game);
			});
		IfPoint(game.pauseButtons[0], game, { (float)game.mousePos.x, (float)game.mousePos.y }, game.isMouseClicked, [=](Button& button, Game& game) {
			Continue(game.pauseButtons[0], game);
			});

#pragma endregion

		

	}
}