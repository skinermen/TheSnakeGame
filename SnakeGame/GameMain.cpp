#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

using namespace SnakeGame;

int main()
{
	// Init random number generator
	int seed = static_cast<int>(time(nullptr));
	srand(seed);
	
	// Init Window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake Game");

	// Game initialization
	SGame game;
	InitGame(game,window);

	// Init game clocks
	// ReSharper disable once CppTooWideScope
	sf::Clock gameClock;

	// Main loop
	while (window.isOpen())
	{
		// Reduce framerate to not spam CPU and GPU
		sleep(sf::milliseconds(16));

		// Read events for close window
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
		}

		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();

		//Update game state
		UpdateGame(game, currentTime, window, event);

		// Draw game
		window.clear();
		DrawGame(game, window);

		window.display();
	}
		
	return 0;
}