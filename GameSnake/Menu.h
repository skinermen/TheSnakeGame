﻿#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

struct SLeaderboard
{
	std::string name;
	int score;
};

struct SDifficultySettings
{
	std::string nameDifficulty;
	float snakeSpeed;
	int scoresPerApple;
};

namespace SnakeGame
{
	struct SGame;
	enum class GameState;
	
	struct SMenuState
	{		
		// Main menu
		std::vector<std::string> VStringMainMenuItems
		{
			"START GAME", "DIFFICULTY", "LEADERBOARD", "OPTIONS", "EXIT"
		};
		std::vector<sf::Text> vTextMainMenuItems;
		sf::Text mainMenuTitle;
		sf::Sprite backgroundMenu;
		sf::Texture mainMenuTexture;
		sf::RectangleShape mainMenuRectangle;
		
		// Pause menu
		std::vector<std::string> VStringPauseMenuItems
		{
			"RESUME", "MAIN MENU"
		};
		std::vector<sf::Text> vTextPauseMenuItems;
		sf::Text pauseMenuTitle;
		sf::RectangleShape pauseMenuRectangle;
		
		// Game Over menu
		std::vector<std::string> VStringGameOverMenuItems
		{
			"NEW GAME", "MAIN MENU"
		};
		std::vector<sf::Text> vTextGameOverMenuItems;
		sf::Text gameOverScoreText;
		sf::RectangleShape gameOverRectangle;

		// Difficulty menu
		std::vector<SDifficultySettings> VStringDifficultyMenuItems
		{
			{"EASY", INITIAL_SPEED_EASY, SCORES_PER_APPLE_EASY},
			{"HARDER EASY", INITIAL_SPEED_HARDER_EASY, SCORES_PER_APPLE_HARDER_EASY},
			{"MEDIUM", INITIAL_SPEED_MEDIUM, SCORES_PER_APPLE_MEDIUM},
			{"EASIER HARD", INITIAL_SPEED_EASIER_HARD, SCORES_PER_APPLE_EASIER_HARD},
			{"HARD", INITIAL_SPEED_HARD, SCORES_PER_APPLE_HARD}
		};
		std::vector<sf::Text> vTextDifficultyMenuItems;
		sf::Text difficultyMenuTitle;
		sf::RectangleShape difficultyMenuRectangle;

		// Leaderboard
		std::vector<SLeaderboard> VLeaderboardItems;
		sf::Text leaderboardNameText[SIZE_LEADERBOARD];
		sf::Text leaderboardTextTitle;
		sf::Text leaderboardTextInstructions;
		sf::Sprite leaderboardBackground;
		sf::Texture leaderboardTexture;
		
		// Winner Menu
		sf::Text winnerText;

		// Other
		sf::Text limiter;
		unsigned int selectedItemIndex = 0;
		int numScores = 0;
		sf::Font font;
		sf::Sprite backgroundGameZone;
		sf::Sprite backgroundLast;
		sf::Sprite pauseBlurSprite;
		sf::RenderTexture pauseBlurTexture;
	};

	// Init
	void InitPauseTexture(SMenuState& menuState);
	void InitMainMenu(SMenuState& menuState, const sf::Font& font);
	void InitPauseMenu(SMenuState& menuState, const sf::Font& font);
	void InitGameOverMenu(SMenuState& menuState, const sf::Font& font);
	void InitDifficultyMenu(SMenuState& menuState, const sf::Font& font);
	void InitLeaderboard(SMenuState& menuState, int numEatenFoods, const sf::Font& font, std::vector<SLeaderboard>& leaderTable);
	void InitOptionsMenu(SMenuState& menuState);
	
	// Draw
	void DrawMainMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawPauseMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawGameOverMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawLeaderboard(SMenuState& menuState, sf::RenderWindow& window);
	void DrawDifficultyMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawOptionsMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawMenuItems(sf::RenderWindow& window, std::vector<sf::Text>& menuItems);

	// Service
	void MoveUp(SMenuState& menuState, std::vector<sf::Text>& menuItems);
	void MoveDown(SMenuState& menuState, std::vector<sf::Text>& menuItems);
	void ResetMenuSelection(const SMenuState& menuState, std::vector<sf::Text>& menuItems);
	void ResetAllMenuSelection(SMenuState& menuState);
}