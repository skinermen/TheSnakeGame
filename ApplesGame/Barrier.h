#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct SBarrier
	{
		Position2D position;
		sf::Sprite sprite;
	};

	struct SGame;

	void InitBarrier(SBarrier& barrier, const SGame& game);
	void DrawBarrier(SBarrier& barrier, sf::RenderWindow& window);
}