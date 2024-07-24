#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
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
		float speed = INITIAL_SPEED;
		PlayerDirection direction = PlayerDirection::StartPosition;
		sf::Sprite sprite;
	};

	struct SGame;

	void InitPlayer(SPlayer& player, const SGame& game);
	void DrawPlayer(SPlayer& player, SGame& game, sf::RenderWindow& window);
	void MovePlayer(SGame& game, float deltaTime);
	void FindPlayerCollision(SGame& game);
}