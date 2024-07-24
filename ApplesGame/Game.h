#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Food.h"
#include "Barrier.h"
#include "UI.h"
#include <string>
#include <pplwin.h>

namespace ApplesGame
{
	enum class GameState
	{
		None = 0,
		MainMenu,
		Playing,
		Winner,
		GameOver,
		QuitMenu,
	};
	
	struct SGame
	{
		// Game state
		bool isScreenLeaderboard = false;
		bool isPlayMusic = false;

		// Key state
		bool onKeyHold1 = false;
		bool onKeyHold2 = false;
		bool onKeyHoldTab = false;
		bool onKeyEsc = false;
		
		// Global game data
		int numFoods = 0;
		int numEatenFoods = 0;
		float timeSinceGameOver = 0.f;
		sf::Sprite backgroundGameZone;
		sf::Sprite backgroundMenu;
		sf::Sprite backgroundLast;
		UIState uiState;
		std::vector<GameState> gameStateStack;

		// Init object state
		SPlayer player;
		std::vector<SFood> foodsVec;
		std::vector<SBarrier> barriersVec;

		// Game mode data
		int gameMode = 0;

		// Resources
		sf::Texture playerTextureSide;
		sf::Texture playerTextureTop;
		sf::Texture foodTexture;
		sf::Texture barrierTexture;
		sf::Texture grassTexture;
		sf::Texture menuTexture;
		sf::RenderTexture pauseBlurTexture;
		sf::Sprite pauseBlurSprite;
		sf::Font font;
		sf::SoundBuffer eatFoodBuffer;
		sf::SoundBuffer deathBuffer;
		sf::SoundBuffer winnerBuffer;
		sf::Music musicMainTheme;
		sf::Image icon;
		sf::Event event;
	};

	void InitGame(SGame& game, sf::RenderWindow& window);
	void InitGameState(SGame& game);
	
	void UpdateMainMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game);
	void UpdateQuitMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game);
	void UpdatePlayingState(const sf::Event& event, SGame& game, float deltaTime);
	void UpdateGame(SGame& game, float deltaTime, sf::RenderWindow& window, sf::Event event);
	void UpdateGameOverState(SGame& game, sf::RenderWindow& window, float deltaTime);

	void PushGameState(SGame& game, GameState state);
	void PopGameState(SGame& game);
	void SwitchGameState(SGame& game, GameState newState);
	void SwitchGameStateInternal(SGame& game, GameState oldState, GameState newState);
	GameState GetCurrentGameState(const SGame& game);
	GameState GetPreviousGameState(const SGame& game);

	void ShutdownPlayingState(SGame& game);
	void InitGameOverState(SGame& game);
	void ShutdownGameOverState(SGame& game);
	
	void DrawGame(SGame& game, sf::RenderWindow& window);
	void DeinitializeGame(SGame& game);

	void HandleInput(const sf::Event& event, sf::RenderWindow& window, SGame& game);
	void ToggleGameMode(SGame& game, const int modeSelection);
	std::string GetButtonText(const SGame& game, const int modeSelection);
}
