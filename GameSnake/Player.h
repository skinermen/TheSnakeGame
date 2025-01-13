#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace SnakeGame
{
	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down,
		StartPosition
	};

	struct SPlayer
	{
		Position2D position;
		float lastUpdateTime = 0.0f; // Время последнего обновления
		float movementInterval = INITIAL_SPEED; // Интервал между перемещениями (в секундах)
		PlayerDirection direction = PlayerDirection::StartPosition;
		sf::Sprite spriteHead;
		sf::Sprite spriteBody;
		int snakeLength;
		// std::queue<PlayerDirection> directionQueue; // Очередь направлений
	};

	struct SGame;

	void InitPlayer(SPlayer& player, SGame& game);
	void DrawPlayer(SPlayer& player, SGame& game, sf::RenderWindow& window);
	void GrowSnake(SGame& game);
	void HandleInput(SPlayer& player);
	void MovePlayer(SGame& game, float currentTime);
	void FindPlayerCollision(SGame& game);
}