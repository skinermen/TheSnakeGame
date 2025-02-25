#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace SnakeGame
{
	struct SWall
	{
		Position2D position;
		sf::Sprite sprite;
	};

	struct SGame;

	void InitWall(SWall& wall, const SGame& game);
	void AddWall(SGame& game);
	void DrawWall(SWall& wall, const SGame& game, sf::RenderWindow& window);
}