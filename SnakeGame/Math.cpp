#include "Math.h"
#include "Game.h"

sf::Vector2i SnakeGame::GetRandomPosition()
{
	return sf::Vector2i(rand() / (float)RAND_MAX * numCols, rand() / (float)RAND_MAX * numRows);
}

bool SnakeGame::ifTouchObj(sf::Vector2i pos1, sf::Vector2i pos2, float size1, float size2)
{
	float distance = sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
	if (distance < size1 || distance < size2)
	{
		return true;
	}
	return false;
}
