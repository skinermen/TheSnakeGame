#pragma once
#include <string>

namespace SnakeGame
{
#define FIELD_CELL_TYPE_NONE 0
#define FIELD_CELL_TYPE_APPLE -1
#define FIELD_CELL_TYPE_WALL -2
	const int FIELD_SIZE_X = 35;
	const int FIELD_SIZE_Y = 25;
	const int CELL_SIZE = 32;
	
	const std::string RESOURCES_PATH = "Resources/";
	
	// Size
	constexpr int SCOREBAR_HEIGHT = 58;
	constexpr int SCREEN_WIDTH = FIELD_SIZE_X * CELL_SIZE;
	constexpr int SCREEN_HEIGHT = FIELD_SIZE_Y * CELL_SIZE + SCOREBAR_HEIGHT;
	constexpr float SNAKE_SEGMENT_SIZE = CELL_SIZE;
	constexpr float FOOD_SIZE = CELL_SIZE;
	constexpr float WALL_SIZE = CELL_SIZE;
	constexpr int SIZE_LEADERBOARD = 10;

	// Variable complexity
	constexpr int SCORES_PER_APPLE_EASY = 2;
	constexpr int SCORES_PER_APPLE_HARDER_THAN_EASY = 4;
	constexpr int SCORES_PER_APPLE_MEDIUM = 6;
	constexpr int SCORES_PER_APPLE_EASIER_THAN_HEAVY = 8;
	constexpr int SCORES_PER_APPLE_HARD = 10;
	
	constexpr float INITIAL_SPEED_EASY = 0.5f;
	constexpr float INITIAL_SPEED_HARDER_THAN_EASY = 0.4f;
	constexpr float INITIAL_SPEED_MEDIUM = 0.3f;
	constexpr float INITIAL_SPEED_EASIER_THAN_HEAVY = 0.2f;
	constexpr float INITIAL_SPEED_HARD = 0.1f;
	

	// Other
	constexpr float ACCELERATION = 20.f; // Pixels per seconds
	constexpr float PAUSE_LENGTH = 0.f;
	constexpr int MASK_INFINIT_FOODS = 0x01;
	constexpr int MASK_WITH_ACCELERATION = 0x20;
}