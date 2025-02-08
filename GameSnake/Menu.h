#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

// Show only the first seven players
constexpr int MAX_PLAYERS_TO_DISPLAY = 7;

struct Scoreboard
{
	std::string name;
	int score;
};

namespace SnakeGame
{
	struct MenuState
	{
		// Main menu
		std::vector<std::string> mainMenuItems
		{
			"START GAME", "DIFFICULTY", "LEADERBOARD", "OPTIONS", "EXIT"
		};
		sf::Text mainMenuTextStartGame;
		sf::Sprite backgroundMenu;
		sf::Texture mainMenuTexture;

		
		// Scoreboard
		std::vector<Scoreboard> vectorScoreTable
		{
				{"Zeus", 0}, {"Femida", 0}, {"Gerakl", 0}, {"Afrodita", 0}, {"Afina", 0},
				{"Dionis", 0}, {"Ares", 0}, {"Germes", 0}, {"Morfey", 0}, {"YOU", 0}
		};
		sf::Text scoreboardNameText[SIZE_LEADERBOARD];
		sf::Text scoreboardTextTitle;
		sf::Text scoreboardTextInstructions;
		sf::Sprite backgroundScoreboard;
		sf::Texture scoreboardTexture;

		// Pause menu
		sf::Text pauseMenuText;
		sf::Text pauseMenuTextVariants;

		// Game Over menu
		sf::Text gameOverScoreText;
		sf::Text gameOverText;
		sf::Text gameOverTextInstructions;

		// Winner Menu
		sf::Text winnerText;

		// Other
		std::vector<sf::Text> textItems;
		int selectedItemIndex = 0;
		int numScores = 0;
		sf::Font font;
		sf::Sprite backgroundGameZone;
		sf::Sprite backgroundLast;
		sf::Sprite pauseBlurSprite;
		sf::RenderTexture pauseBlurTexture;
	};

	// Init
	void InitPauseTexture(MenuState& menuState);
	void InitMainMenu(MenuState& menuState, const sf::Font& font, std::vector<sf::Text> textItems);
	void InitScoreboard(MenuState& menuState, int numEatenFoods, const sf::Font& font, std::vector<Scoreboard>& scoreTable);
	void InitPauseMenu(MenuState& menuState);
	void InitGameOverMenu(MenuState& menuState);
	void InitWinnerMenu(MenuState& menuState);
	void InitDifficultyMenu(MenuState& menuState);
	void InitOptionsMenu(MenuState& menuState);

	// Update
	
	// Draw
	void DrawMainMenu(MenuState& menuState, sf::RenderWindow& window);
	void DrawScoreboard(MenuState& menuState, sf::RenderWindow& window);
	void DrawPauseMenu(MenuState& menuState, sf::RenderWindow& window);
	void DrawGameOverMenu(MenuState& menuState, sf::RenderWindow& window);
	void DrawWinnerMenu(MenuState& menuState, sf::RenderWindow& window);
	void DrawDifficultyMenu(MenuState& menuState, sf::RenderWindow& window);
	void DrawOptionsMenu(MenuState& menuState, sf::RenderWindow& window);

	// Service
	void moveUp(MenuState& menuState);
	void moveDown(MenuState& menuState);
	int getSelectedItemIndex(MenuState& menuState);
}