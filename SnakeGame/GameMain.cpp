#include <SFML/Graphics.hpp>
#include <cstdlib>

#include <vector>

enum PlayerDirection
{
	right = 0,
	left = 1,
	up = 2,
	down = 3
};

int main() {
	const int numRows = 32;
	const int numCols = 32;
	const int cellSize = 800 / 32;

	sf::RenderWindow window;
	PlayerDirection direction = PlayerDirection::right;

	window.create(sf::VideoMode(800, 800), "SnakeGame");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	float delay = 0.2f;

	sf::Clock moveTimer;

	int bodyLenght = 3;
	int x = numCols / 2;
	int y = numRows / 2;

	std::vector<sf::Vector2i> snakeBody;

	for (int i = 0; i < bodyLenght; ++i) {
		snakeBody.push_back(sf::Vector2i(x, y));
	}

	std::vector<sf::RectangleShape> snakeParts;
	for (int i = 0; i < snakeBody.size(); ++i) {
		sf::RectangleShape part;
		part.setSize({ cellSize, cellSize });
		part.setFillColor(sf::Color::Color(240 - i * 5, 240 - i * 5, 240 - i * 5));
		part.setPosition(snakeBody[i].x * cellSize, snakeBody[i].y * cellSize);
		snakeParts.push_back(part);
	}

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		sf::sleep(sf::milliseconds(16));

		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			direction = PlayerDirection::right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			direction = PlayerDirection::left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			direction = PlayerDirection::up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			direction = PlayerDirection::down;
		}

		if (moveTimer.getElapsedTime().asSeconds() >= delay)
		{
			switch (direction)
			{
			case right:
				x++;
				break;
			case left:
				x--;
				break;
			case up:
				y--;
				break;
			case down:
				y++;
				break;
			default:
				break;
			}

			x = std::max(0, std::min(x, numCols - 1));
			y = std::max(0, std::min(y, numRows - 1));

			snakeBody.insert(snakeBody.begin(), sf::Vector2i(x, y));

			snakeBody.erase(snakeBody.end() - 1);

			snakeParts[0].setPosition(x * cellSize, y * cellSize);

			moveTimer.restart();
		}

		for (int i = 1; i < snakeBody.size(); ++i) {
			snakeParts[i].setPosition(snakeBody[i].x * cellSize, snakeBody[i].y * cellSize);
		}

		window.clear();

		for (const auto& part : snakeParts) {
			window.draw(part);
		}

		window.display();
	}
}