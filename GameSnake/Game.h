#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
		Winner,
		GameOver,
		QuitMenu,
		Scoreboard,
		Difficulty,
		Options,
	};
	
	struct SGame
	{
		// Game state
		bool isScreenLeaderboard = false;
		bool isPlayMusic = false;

		// Key state
		bool onKeyHold = false;
		
		// Global game data
		int numEatenApples = 0;
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
	
	void UpdateMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game);
	void UpdateQuitMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game);
	void UpdatePlayingState(const sf::Event& event, SGame& game, float currentTime);
	void UpdateGame(SGame& game, float currentTime, sf::RenderWindow& window, sf::Event event);
	void UpdateGameOverState(SGame& game, sf::RenderWindow& window, float deltaTime);
	void UpdateScoreboardState(SGame& game, sf::Event& event);
	
	void HandleMainMenuSelection(int selectedIndex, SGame& game, sf::RenderWindow& window);

	void PushGameState(SGame& game, GameState state);
	void PopGameState(SGame& game);
	void SwitchGameState(SGame& game, GameState newState);
	GameState GetCurrentGameState(const SGame& game);
	GameState GetPreviousGameState(const SGame& game);
	
	int GetRandomEmptyCell(const SGame& game);
	void DrawGame(SGame& game, sf::RenderWindow& window);
	void ToggleGameMode(SGame& game, const int modeSelection);
	std::string GetButtonText(const SGame& game, const int modeSelection);
}

