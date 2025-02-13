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
		float lastUpdateTime = 0.0f; // Время последнего обновления
		float movementInterval = INITIAL_SPEED_HARD; // Интервал между перемещениями (в секундах)
		SnakeDirection direction;
		sf::Sprite spriteHead;
		sf::Sprite spriteBody;
		int snakeLength;
		std::queue<SnakeDirection> directionQueue; // Очередь направлений
	};

	struct SGame;

	void InitSnake(SSnake& snake, const SGame& game);
	void AddSnake(SGame& game);
	void DrawSnake(SSnake& snake, const SGame& game, sf::RenderWindow& window);
	void GrowSnake(SGame& game);
	void HandleInput(SSnake& player);
	void MoveSnake(SGame& game, float currentTime);
}