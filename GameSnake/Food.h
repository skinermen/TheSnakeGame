#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace SnakeGame
{
	struct SFood
	{
		Position2D position;
		sf::Sprite sprite;
	};

	struct SGame;

	void InitFood(SFood& food, const SGame& game);
	void AddApple(SGame& game);
	void DrawFood(SFood& food, SGame& game, sf::RenderWindow& window);
}
