#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <functional>
#include "Constans.h"
#include "Player.h"
#include "TextConfg.h"
#include "Orange.h"
#include "Math.h"
#include "Panel.h"
#include "Button.h"

namespace SnakeGame {
	enum class PlayerDirection
	{
		right = 0,
		left = 1,
		up = 2,
		down = 3
	};

	enum class GameState
	{
		Menu = 0,
		Game = 1,
		Settings = 2
	};

	enum class PlayerState
	{
		Idle = 0,
		Dead = 1,
		Paused = 2
	};

	enum class MenuState
	{
		Menu = 0,
		Settings = 1,
		Difficulty = 2
	};

	enum class Difficulty
	{
		Easy = 0,
		EasyPlus = 1,
		Normal = 2,
		NormalPlus = 3,
		Hard = 4
	};

	struct Enemy {
		int Score = rand() % 77;
		std::string Name = Names[rand() % 10];
	};

	struct Game {
		PlayerDirection direction = PlayerDirection::right;
		GameState gameState = GameState::Menu;
		PlayerState playerState = PlayerState::Idle;
		MenuState menuState = MenuState::Menu;
		Difficulty gameDifficulty = Difficulty::Normal;

		Panel deathPanels[4];
		Panel pausePanels[2];

		Button deathButtons[2];
		Button pauseButtons[2];
		Button menuButtons[4];
		Button menuDifficultyButtons[5];

		float dealyDifficulty[5] = {0.2f, 0.1f, 0.05f, 0.025f, 0.015f};

		float delay = 0.2f;
		float clickDelay = 0.1f;

		sf::Vector2i mousePos;
		bool isMouseClicked = false;
		bool ifDead = false;
		bool ifPaused = false;

		Enemy enemies[3];

		int bestScore = 0;

		bool ifGoing = true;

		Player player;
		Orange orange;
		Text pointsText;
		Text menuText;
		Text menuDifficultyText;
		Text pauseText;
		Text DeathText[2];

		sf::Font font;

		int pointsDifficulty[5] = { 2, 4, 6, 8, 10 };

		int orangeCount = 0;
		int pointAdder = 2;

		sf::Clock moveTimer;
		sf::Clock clickTimer;
		sf::Clock saveTimer;
	};

	void Start(Game& game);
	void Menu(Game& game);
	void Restart(Button& , Game& game);
	void StartMenu(Game& game);
	void Update(Game& game, float deltaTime, sf::RenderWindow& window);
	void GameOver(sf::RenderWindow& window, Game& game);
	void Draw(Game& game, sf::RenderWindow& window);
}