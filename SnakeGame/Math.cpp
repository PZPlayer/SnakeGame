#include "Math.h"
#include "Game.h"

sf::Vector2i SnakeGame::GetRandomPosition()
{
	return sf::Vector2i(rand() / (float)RAND_MAX * numCols, rand() / (float)RAND_MAX * numRows);
}
