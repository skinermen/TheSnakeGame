#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Apple.h"
#include "Wall.h"
#include "UI.h"
#include <string>
#include <pplwin.h>

namespace SnakeGame
{
	enum class GameState
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		PauseMenu,
		Leaderboard,
		Difficulty,
		Options,
	};
	
	struct SGame
	{
		// Game state
		bool isScreenLeaderboard = false;

		// Key state
		bool onKeyHold = false;
		bool difficultySelected = false;
		
		// Global game data
		int numEatenApples = 0;
		int scoresPerApple = SCORES_PER_APPLE_EASY;
		float timeSinceGameOver = 0.f;
		UIState uiState;
		std::vector<GameState> gameStateStack;
		int field[FIELD_SIZE_X][FIELD_SIZE_Y];


		// Init object state
		SSnake snake;
		std::vector<SApple> applesVec;
		std::vector<SWall> wallsVec;

		// Game mode data
		int gameMode = 0;
		
		sf::Event event;
	};

	void InitGame(SGame& game, sf::RenderWindow& window);
	void InitGameState(SGame& game);
	void InitField (SGame& game);
	void InitStartNewGame(SGame& game);
	
	void UpdateGame(SGame& game, float currentTime, sf::RenderWindow& window, const sf::Event& event);
	void UpdatePlayingState(const sf::Event& event, SGame& game, float currentTime);
	void UpdateMenuState(SGame& game, const sf::Event& event, sf::RenderWindow& window, std::vector<sf::Text>& menuItems);
	void UpdateLeaderboardState(SGame& game, const sf::Event& event);
	
	void HandleMainMenuSelection(unsigned int selectedIndex, SGame& game, sf::RenderWindow& window);
	void HandlePauseMenuSelection(unsigned int selectedIndex, SGame& game);
	void HandleGameOverMenuSelection(unsigned int selectedIndex, SGame& game);
	void HandleDifficultyMenuSelection(unsigned int selectedIndex, SGame& game);

	void DrawGame(SGame& game, sf::RenderWindow& window);
	
	void PushGameState(SGame& game, GameState state);
	void PopGameState(SGame& game);
	void SwitchGameState(SGame& game, GameState newState);
	
	GameState GetCurrentGameState(const SGame& game);
	GameState GetPreviousGameState(const SGame& game);
	int GetRandomEmptyCell(const SGame& game);
	std::string GetButtonText(const SGame& game, int modeSelection);

	void ToggleGameMode(SGame& game, int modeSelection);
}

