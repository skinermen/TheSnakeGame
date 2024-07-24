﻿#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

using namespace ApplesGame;

int main()
{
	// Init random number generator
	int seed = (int)time(nullptr);
	srand(seed);

	// Init Window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Adventures of a hedgehog");

	// Game initialization
	SGame game;
	InitGame(game, window);

	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main loop
	while (window.isOpen())
	{
		// Reduce framerate to not spam CPU and GPU
		sf::sleep(sf::milliseconds(16));

		// Read events for close window
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}

			HandleInput(event, window, game);
		}

		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//Update game state
		UpdateGame(game, deltaTime, window, event);

		// Draw game
		window.clear();
		DrawGame(game, window);

		window.display();
	}

	// Deinitialization
	//DeinitializeGame(game);
		
	return 0;
}