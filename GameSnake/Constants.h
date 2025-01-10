#pragma once
#include <string>

namespace SnakeGame
{
#define FIELD_CELL_TYPE_NONE 0
#define FIELD_CELL_TYPE_APPLE -1
#define FIELD_CELL_TYPE_PLAYER 2
	const int FIELD_SIZE_X = 35;
	const int FIELD_SIZE_Y = 25;
	const int CELL_SIZE = 32;
	
	const std::string RESOURCES_PATH = "Resources/";
	
	// Size
	constexpr int SCREEN_WIDTH = FIELD_SIZE_X * CELL_SIZE;
	constexpr int SCREEN_HEIGHT = FIELD_SIZE_Y * CELL_SIZE;
	constexpr float PLAYER_SIZE = CELL_SIZE;
	constexpr float FOOD_SIZE = CELL_SIZE;
	constexpr float BARRIER_SIZE = CELL_SIZE;
	constexpr int SIZE_LEADERBOARD = 10;

	// Num
	constexpr int NUM_FOOD = 1;
	constexpr int NUM_BARRIERS = 10;

	// Other
	constexpr float INITIAL_SPEED = 0.1f; // Интервал между перемещениями (в секундах)
	constexpr float ACCELERATION = 20.f; // Pixels per seconds
	constexpr float PAUSE_LENGTH = 0.f;
	constexpr int MASK_INFINIT_FOODS = 0x01;
	constexpr int MASK_WITH_ACCELERATION = 0x20;
}