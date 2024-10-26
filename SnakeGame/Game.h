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

	struct Enemy {
		int Score = rand() % 77;
		std::string Name = Names[rand() % 10];
	};

	struct Game {
		PlayerDirection direction = PlayerDirection::right;
		GameState gameState = GameState::Menu;
		PlayerState playerState = PlayerState::Idle;

		Panel deathPanels[4];
		Panel pausePanels[2];

		Button deathButtons[2];
		Button pauseButtons[2];

		float delay = 0.2f;

		sf::Vector2i mousePos;
		bool isMouseClicked = false;
		bool ifDead = false;
		bool ifPaused = false;

		Enemy enemies[3];

		int bestScore = 0;

		Player player;
		Orange orange;
		Text pointsText;
		Text menuText;
		Text pauseText;
		Text DeathText[2];

		sf::Font font;

		int orangeCount = 0;
		int pointAdder = 1;

		sf::Clock moveTimer;
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