#include "Math.h"
#include "Game.h"

sf::Vector2i SnakeGame::GetRandomPosition()
{
	return sf::Vector2i((int)(rand() / (float)RAND_MAX * (float)numCols), (int)(rand() / (float)RAND_MAX * (float)numRows));
}

bool SnakeGame::ifTouchObj(sf::Vector2i pos1, sf::Vector2i pos2, float size1, float size2)
{
	float distance = sqrt(float((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y)));
	if (distance < size1 || distance < size2)
	{
		return true;
	}
	return false;
}

void SnakeGame::SetTextOrigin(sf::Text text, float x, float y)
{
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(x * textRect.width, y * textRect.height);
}

void SnakeGame::SetRectangleOrigin(sf::RectangleShape shape, float x, float y)
{
	sf::FloatRect shapeRect = shape.getLocalBounds();
	shape.setOrigin(x * shapeRect.width, y * shapeRect.height);
}