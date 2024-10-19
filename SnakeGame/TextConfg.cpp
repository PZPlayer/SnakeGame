#include "TextConfg.h"
#include "Game.h"

namespace SnakeGame {
	void InitText(Text text) {
		text.text.setFont(text.font);
		text.text.setFillColor(text.textColor);
		text.text.setCharacterSize(text.textSize);
		text.text.setPosition((float)text.position.x - 15, (float)text.position.y);
		SetTextOrigin(text.text, 0.5f, 0.5f);
		text.text.setString(text.strText);
	}

	void DrawText(sf::RenderWindow& window, Text& text) {
		text.text.setFont(text.font);
		text.text.setString(text.strText);
		text.text.setCharacterSize(text.textSize);
		text.text.setPosition((float)text.position.x - 25, (float)text.position.y);
		text.text.setFillColor(text.textColor);
		SetTextOrigin(text.text, 0.5f, 0.5f);
		window.draw(text.text);
	}
}