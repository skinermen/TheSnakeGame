#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace SnakeGame
{
	struct SApple
	{
		Position2D position;
		sf::Sprite sprite;
	};

	struct SGame;

	void InitApple(SApple& apple, const SGame& game);
	void AddApple(SGame& game);
	void DrawApple(SApple& apple, const SGame& game, sf::RenderWindow& window);
}
