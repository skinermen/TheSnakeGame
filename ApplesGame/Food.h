#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct SFood
	{
		Position2D position;
		sf::Sprite sprite;
	};

	struct SGame;

	void InitFood(SFood& food, const SGame& game);
	void DrawFood(SFood& food, sf::RenderWindow& window);
}
