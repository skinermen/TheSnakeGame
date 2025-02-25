#pragma once
#include <string>

namespace SnakeGame
{
#define FIELD_CELL_TYPE_NONE 0
#define FIELD_CELL_TYPE_APPLE (-1)
#define FIELD_CELL_TYPE_WALL (-2)
	constexpr int FIELD_SIZE_X = 25;
	constexpr int FIELD_SIZE_Y = 20;
	constexpr int CELL_SIZE = 32;
	
	const std::string RESOURCES_PATH = "Resources/";
	const std::string LEADERBOARD_FILENAME = "leaderboard.txt";
	const std::string DEFAULT_NAME = "XYZ";
	
	// Size
	constexpr int LEADERBOARD_HEIGHT = 58;
	constexpr int SIZE_LEADERBOARD = 10;
	constexpr int SIZE_MINI_LEADERBOARD = 5;
	constexpr int BORDER_SIZE = 10;
	constexpr int SCREEN_WIDTH = FIELD_SIZE_X * CELL_SIZE + BORDER_SIZE * 2;
	constexpr int SCREEN_HEIGHT = FIELD_SIZE_Y * CELL_SIZE + LEADERBOARD_HEIGHT + BORDER_SIZE * 2;
	constexpr int SNAKE_SEGMENT_SIZE = CELL_SIZE;
	constexpr int FOOD_SIZE = CELL_SIZE;
	constexpr int WALL_SIZE = CELL_SIZE;

	// Variable difficulty
	constexpr int SCORES_PER_APPLE_EASY = 2;
	constexpr int SCORES_PER_APPLE_HARDER_EASY = 4;
	constexpr int SCORES_PER_APPLE_MEDIUM = 6;
	constexpr int SCORES_PER_APPLE_EASIER_HARD = 8;
	constexpr int SCORES_PER_APPLE_HARD = 10;
	
	constexpr float INITIAL_SPEED_EASY = 0.5f;
	constexpr float INITIAL_SPEED_HARDER_EASY = 0.4f;
	constexpr float INITIAL_SPEED_MEDIUM = 0.3f;
	constexpr float INITIAL_SPEED_EASIER_HARD = 0.2f;
	constexpr float INITIAL_SPEED_HARD = 0.1f;
	
	// Other
	constexpr float PAUSE_LENGTH = 1.f;
}