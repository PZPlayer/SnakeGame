#include "Orange.h"
#include "Game.h"

namespace SnakeGame {
	void InitOrange(Orange& orange){
		orange.shape.setFillColor(sf::Color::Color(255, 165, 0));
		orange.shape.setSize({ cellSize, cellSize });
		SetRandomPos(orange);
	}

	void SetRandomPos(Orange& orange) {
		orange.position = GetRandomPosition();
		orange.shape.setPosition((float)orange.position.x * cellSize, (float)orange.position.y * cellSize);
	}

	void DrawOrange(sf::RenderWindow& window, Orange& orange) {
		window.draw(orange.shape);
	}
}