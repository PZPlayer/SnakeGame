#include "TextConfg.h"
#include "Game.h"

namespace SnakeGame {
	void InitText(Text& text) {
		text.text.setFont(text.font);
		text.text.setFillColor(text.textColor);
		text.text.setCharacterSize(text.textSize);
		text.text.setPosition((float)text.position.x, (float)text.position.y);
		text.text.setOrigin(text.text.getLocalBounds().width * 0.5f, text.text.getLocalBounds().height * 0.5f);
		text.text.setString(text.strText);
	}

	void DrawText(sf::RenderWindow& window, Text& text) {
		text.text.setFont(text.font);
		text.text.setString(text.strText);
		text.text.setCharacterSize(text.textSize);
		text.text.setPosition((float)text.position.x, (float)text.position.y);
		text.text.setFillColor(text.textColor);
		text.text.setOrigin(text.text.getLocalBounds().width * 0.5f, text.text.getLocalBounds().height * 0.5f);
		window.draw(text.text);
	}
}