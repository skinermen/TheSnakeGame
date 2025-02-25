#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

struct SLeaderboard
{
	std::string playerName;
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
		sf::Texture mainMenuTexture;
		sf::RectangleShape mainMenuRectangleBackground;
		
		// Pause menu
		std::vector<std::string> VStringPauseMenuItems
		{
			"RESUME", "MAIN MENU"
		};
		std::vector<sf::Text> vTextPauseMenuItems;
		sf::Text pauseMenuTitle;
		sf::RectangleShape pauseMenuRectangleBackground;

		// Name Input Menu
		sf::Text nameInputMenuText;
		std::string nameInputPlayerName;
		sf::RectangleShape nameInputMenuRectangleBackground;

		// Confirmation Menu
		sf::Text confirmationMenuText;
		std::vector<std::string> VStringConfirmationMenuItems
		{
			"No", "Yes"
		};
		std::vector<sf::Text> vTextConfirmationMenuItems;
		sf::RectangleShape confirmationMenuRectangleBackground;
		
		// Game Over menu
		std::vector<std::string> VStringGameOverMenuItems
		{
			"NEW GAME", "MAIN MENU"
		};
		std::vector<sf::Text> vTextGameOverMenuItems;
		std::vector<sf::Text> vTextGameOverLeaderboardItems;
		sf::Text gameOverScoreTitle;
		sf::Text gameOverScores;
		sf::Text gameOverRecordsTitle;
		sf::RectangleShape gameOverRectangleBackground;

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
		sf::RectangleShape difficultyMenuRectangleBackground;

		// Leaderboard
		std::vector<SLeaderboard> VLeaderboardItems;
		std::vector<sf::Text> vTextLeaderboardItems;
		sf::RectangleShape leaderboardRectangleBackground;
		sf::Text leaderboardTextTitle;
		sf::Text leaderboardTextInstructions;
		sf::Texture leaderboardTexture;

		// Options
		sf::Text optionsMenuTitle;
		std::vector<std::string> VStringOptionsMenuItems
		{
			{"Sounds"}, {"Music"}
		};
		std::vector<sf::Text> vTextOptionsMenuItems;
		std::vector<sf::RectangleShape> vRectanglesOptionsMenu;
		sf::RectangleShape optionsMenuRectangleBackground;
		bool isSoundOn = true;
		bool isMusicOn = true;
		
		// Other
		sf::Text limiter;
		unsigned int selectedItemIndex = 0;
		int numScores = 0;
		sf::Font font;
		sf::Sprite pauseBlurSprite;
		sf::RenderTexture pauseBlurTexture;
	};

	// Init
	void InitPauseTexture(SMenuState& menuState);
	void InitMainMenu(SMenuState& menuState);
	void InitPauseMenu(SMenuState& menuState);
	void InitNameInputMenu(SMenuState& menuState);
	void InitConfirmationMenu(SMenuState& menuState);
	void InitGameOverMenu(SMenuState& menuState);
	void InitGameOverLeaderboardItems(SMenuState& menuState);
	void InitDifficultyMenu(SMenuState& menuState);
	void InitLeaderboard(SMenuState& menuState);
	void InitOptionsMenu(SMenuState& menuState);
	
	// Draw
	void DrawMainMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawPauseMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawNameInputMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawConfirmationMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawGameOverMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawLeaderboard(SMenuState& menuState, sf::RenderWindow& window);
	void DrawDifficultyMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawOptionsMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawMenuItems(sf::RenderWindow& window, std::vector<sf::Text>& menuItems,
		float posX, float posY, float indentation);

	// Service
	void AddRecord(SMenuState& menuState, const std::string& playerName, int score);
	void MoveUp(SMenuState& menuState, std::vector<sf::Text>& menuItems);
	void MoveDown(SMenuState& menuState, std::vector<sf::Text>& menuItems);
	void ResetMenuSelection(const SMenuState& menuState, std::vector<sf::Text>& menuItems);
	void ResetAllMenuSelection(SMenuState& menuState);
	void SaveRecordsToFile(const std::vector<SLeaderboard>& leaderboard, const std::string& filename);
	void LoadRecordsFromFile(std::vector<SLeaderboard>& leaderboard, const std::string& filename);
	bool IsNewRecord(const std::vector<SLeaderboard>& leaderboard, int currentScore);
	void SetFillColorRectangle(SMenuState& menuState, int selectedIndex, bool option);
}