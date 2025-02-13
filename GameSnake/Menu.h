#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

struct SScoreboard
{
	std::string name;
	int score;
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

		// Scoreboard
		std::vector<SScoreboard> VScoreTableItems
		{
				{"Zeus", 0}, {"Femida", 0}, {"Gerakl", 0}, {"Afrodita", 0}, {"Afina", 0},
				{"Dionis", 0}, {"Ares", 0}, {"Germes", 0}, {"Morfey", 0}, {"YOU", 0}
		};
		sf::Text scoreboardNameText[SIZE_LEADERBOARD];
		sf::Text scoreboardTextTitle;
		sf::Text scoreboardTextInstructions;
		sf::Sprite backgroundScoreboard;
		sf::Texture scoreboardTexture;
		

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
	void InitScoreboard(SMenuState& menuState, int numEatenFoods, const sf::Font& font, std::vector<SScoreboard>& scoreTable);
	void InitDifficultyMenu(SMenuState& menuState);
	void InitOptionsMenu(SMenuState& menuState);
	
	// Draw
	void DrawMainMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawPauseMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawGameOverMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawScoreboard(SMenuState& menuState, sf::RenderWindow& window);
	void DrawDifficultyMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawOptionsMenu(SMenuState& menuState, sf::RenderWindow& window);
	void DrawMenuItems(sf::RenderWindow& window, std::vector<sf::Text>& menuItems);

	// Service
	void MoveUp(SMenuState& menuState, std::vector<sf::Text>& menuItems);
	void MoveDown(SMenuState& menuState, std::vector<sf::Text>& menuItems);
	void ResetMenuSelection(SMenuState& menuState, std::vector<sf::Text>& menuItems);
}