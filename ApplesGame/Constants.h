#pragma once
#include <string>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";
	
	// Size
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;
	constexpr int GAME_ZONE_WIDTH = 800;
	constexpr int GAME_ZONE_HEIGHT = 600;
	constexpr float PLAYER_SIZE = 40.f;
	constexpr float FOOD_SIZE = 30.f;
	constexpr float BARRIER_SIZE = 30.f;
	constexpr int SIZE_LEADERBOARD = 10;

	// Num
	constexpr int NUM_FOOD_MIN = 20;
	constexpr int NUM_FOOD_MAX = 30;
	constexpr int NUM_BARRIERS = 10;

	// Other
	constexpr float INITIAL_SPEED = 100.f; // Pixels per frame
	constexpr float ACCELERATION = 20.f; // Pixels per seconds
	constexpr float PAUSE_LENGTH = 0.f;
	constexpr int MASK_INFINIT_FOODS = 0x01;
	constexpr int MASK_WITH_ACCELERATION = 0x20;
}