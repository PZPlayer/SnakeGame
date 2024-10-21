#include "Panel.h"
#include "Game.h"

namespace SnakeGame
{
	void InitPanel(Panel& panel, Game& game)
	{
		panel.shape.setOrigin(panel.shape.getLocalBounds().width * 0.5f, panel.shape.getLocalBounds().height * 0.5f);
		panel.shape.setSize(sf::Vector2f((float)panel.size.x, (float)panel.size.y));
		panel.shape.setPosition(sf::Vector2f(panel.pos.x, panel.pos.y));
		panel.shape.setFillColor(panel.color);
	}

	void DrawPanel(Panel& panel, sf::RenderWindow& window)
	{
		window.draw(panel.shape);
	}
}
