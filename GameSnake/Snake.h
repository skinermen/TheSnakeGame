#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace SnakeGame
{
	enum class SnakeDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct SSnake
	{
		Position2D position;
		float lastUpdateTime = 0.0f; // The time of the last update
		float movementInterval = INITIAL_SPEED_EASY; // Interval between movements (in seconds)
		SnakeDirection direction;
		sf::Sprite spriteHead;
		sf::Sprite spriteBody;
		int snakeLength;
		std::queue<SnakeDirection> directionQueue; // The line of directions
	};

	struct SGame;

	void InitSnake(SSnake& snake, const SGame& game);
	void AddSnake(SGame& game);
	void DrawSnake(SSnake& snake, const SGame& game, sf::RenderWindow& window);
	void GrowSnake(SGame& game);
	void HandleInput(SSnake& player);
	void MoveSnake(SGame& game, float currentTime);
}