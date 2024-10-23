#include "Button.h"
#include "Game.h"

namespace SnakeGame {
	void InitButton(Button& button, Game& game) {
		button.shape.setPosition(button.pos);
		if (button.ifFirstTime) {
			button.ifFirstTime = false;
			button.shape.setFillColor(button.baseColor);
		}
		button.shape.setSize(button.size);
		button.buttonText.setFont(game.font);
		button.buttonText.setCharacterSize(button.textSize);
		button.buttonText.setString(button.text);
		button.buttonText.setPosition(button.pos);
		button.buttonText.setFillColor(button.baseTextColor);
		button.buttonText.setOrigin(button.buttonText.getLocalBounds().width * 0.5f, button.buttonText.getLocalBounds().height * 0.5f);
		button.shape.setOrigin(button.shape.getLocalBounds().width * 0.5f, button.shape.getLocalBounds().height * 0.5f);
	}

	void IfPoint(Button& button, Game& game, sf::Vector2f mousePos, bool isMouseClicked, std::function<void(Button&, Game&)> callback) {
		if (button.shape.getGlobalBounds().contains(mousePos)) {
			button.shape.setFillColor(button.higlightedColor);

			if (isMouseClicked) {
				button.shape.setFillColor(button.pressedColor);
				callback(button, game);
			}
		}
		else {
			button.shape.setFillColor(button.baseColor);
		}
	}


	void DrawButton(sf::RenderWindow& window, Button& button) {
		window.draw(button.shape);
		window.draw(button.buttonText);
	}
}