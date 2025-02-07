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
	};
	
	struct SGame
	{
		// Game state
		bool isScreenLeaderboard = false;
		bool isPlayMusic = false;

		// Key state
		bool onKeyHold = false;
		// bool onKeyHoldTab = false;
		// bool onKeyEsc = false;
		
		// Global game data
		int numEatenApples = 0;
		int numScores = 0;
		float timeSinceGameOver = 0.f;
		sf::Sprite backgroundGameZone;
		sf::Sprite backgroundMenu;
		sf::Sprite backgroundLast;
		sf::Sprite backgroundScoreboard;
		UIState uiState;
		std::vector<GameState> gameStateStack;
		int field[FIELD_SIZE_X][FIELD_SIZE_Y];


		// Init object state
		SSnake snake;
		std::vector<SApple> applesVec;
		std::vector<SWall> wallsVec;

		// Game mode data
		int gameMode = 0;

		// Resources
		sf::Texture snakeTextureHead;
		sf::Texture snakeTextureBody;
		sf::Texture appleTexture;
		sf::Texture wallTexture;
		sf::Texture noneTexture;
		sf::Texture grassTexture;
		sf::Texture menuTexture;
		sf::Texture scoreboardTexture;
		sf::RenderTexture pauseBlurTexture;
		sf::Sprite pauseBlurSprite;
		sf::Sprite noneSprite;
		sf::Font font;
		sf::SoundBuffer eatAppleBuffer;
		sf::SoundBuffer deathBuffer;
		sf::SoundBuffer winnerBuffer;
		sf::Music musicMainTheme;
		sf::Image icon;
		sf::Event event;
	};

	void InitGame(SGame& game, sf::RenderWindow& window);
	void InitGameState(SGame& game);
	void InitField (SGame& game);
	
	void UpdateMainMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game);
	void HandleMenuSelection(int selectedIndex, SGame& game, UIState& uiState, sf::RenderWindow& window);
	void UpdateQuitMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game);
	void UpdatePlayingState(const sf::Event& event, SGame& game, float currentTime);
	void UpdateGame(SGame& game, float currentTime, sf::RenderWindow& window, sf::Event event);
	void UpdateGameOverState(SGame& game, sf::RenderWindow& window, float deltaTime);
	void UpdateScoreboardState(SGame& game, sf::Event& event);

	void PushGameState(SGame& game, GameState state);
	void PopGameState(SGame& game);
	void SwitchGameState(SGame& game, GameState newState);
	void SwitchGameStateInternal(SGame& game, GameState oldState, GameState newState);
	GameState GetCurrentGameState(const SGame& game);
	GameState GetPreviousGameState(const SGame& game);
	
	void InitGameOverState(SGame& game);
	
	int GetRandomEmptyCell(const SGame& game);
	
	void DrawGame(SGame& game, sf::RenderWindow& window);
	
	void ToggleGameMode(SGame& game, const int modeSelection);
	std::string GetButtonText(const SGame& game, const int modeSelection);
}

