#include "Game.h"

int main() {
	using namespace SnakeGame;

	sf::RenderWindow window;
	window.create(sf::VideoMode(screenX, screenY), "SnakeGame");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	int seed = (int)time(nullptr);
	srand(seed);

	PlayerDirection direction = PlayerDirection::right;

	Game game;
	game.gameState == GameState::Game ? Start(game): Start(game);

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
		Update(game, deltaTime, window);

		window.clear();
		Draw(game, window);

		window.display();
	}

	return 0;
}
