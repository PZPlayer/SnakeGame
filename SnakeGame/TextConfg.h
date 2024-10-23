#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include "cassert"

namespace SnakeGame {
	struct Text
	{
		sf::Text text;
		sf::Color textColor = sf::Color::White;
		int textSize = 30;
		sf::Font font;
		sf::Vector2i position = {0, 0};
		std::string strText = "Text";
	};

	struct Game;

	void InitText(Text& text);
	void DrawText(sf::RenderWindow& window, Text& text);
}