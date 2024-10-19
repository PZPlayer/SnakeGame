#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include "Constans.h"
#include "Player.h"
#include "TextConfg.h"
#include "Orange.h"
#include "Math.h"

namespace SnakeGame {
	enum PlayerDirection
	{
		right = 0,
		left = 1,
		up = 2,
		down = 3
	};

	struct Game {
		PlayerDirection direction = PlayerDirection::right;

		float delay = 0.2f;

		Player player;
		Orange orange;
		Text pointsText;

		sf::Font font;

		int orangeCount = 0;
		int pointAdder = 1;

		sf::Clock moveTimer;
	};

	void Start(Game& game);
	void Update(Game& game, float deltaTime, sf::RenderWindow& window);
	void GameOver(sf::RenderWindow& window);
	void Draw(Game& game, sf::RenderWindow& window);
}