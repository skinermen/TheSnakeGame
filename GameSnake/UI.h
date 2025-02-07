#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
	struct UIState
	{
		bool isGameTextVisible;
		bool isGameOverTextVisible;
		bool isWinnerTextVisible;
		bool isMainMenuTextVisible;
		bool isQuitMenuTextVisible;
		bool isScoreboardVisible;

		std::vector<Scoreboard> vectorScoreTable
		{
			{"Zeus", 0}, {"Femida", 0}, {"Gerakl", 0}, {"Afrodita", 0}, {"Afina", 0},
			{"Dionis", 0}, {"Ares", 0}, {"Germes", 0}, {"Morfey", 0}, {"YOU", 0}
		};

		std::vector<std::string> mainMenuItems
		{
			"START GAME", "DIFFICULTY", "LEADERBOARD", "OPTIONS", "EXIT"
		};
		std::vector<sf::Text> textItems;
		int selectedItemIndex = 0;

		sf::Text scoreText;
		sf::Text scoreTextGameOver;
		sf::Text inputText;
		sf::Text gameOverText;
		sf::Text gameOverTextInstructions;
		sf::Text winnerText;
		sf::Text mainMenuTextStartGame;
		sf::Text quitMenuText;
		sf::Text quitMenuTextVariants;
		sf::Text scoreboardNameText[SIZE_LEADERBOARD];
		sf::Text scoreboardTextTitle;
		sf::Text scoreboardTextInstructions;

		sf::Sound sound;
	};

	void InitTextUI(sf::Text& text, const sf::Font& font, int size, int style, sf::Color color, const std::string& name = "-");
	void InitUI(UIState& uiState, const sf::Font& font);
	void InitScoreboard(UIState& uiState, int numEatenFoods, const sf::Font& font, std::vector<Scoreboard>& scoreTable);
	void InitMainMenu(UIState& uiState, const sf::Font& font, std::vector<sf::Text> textItems);
	void moveUp(UIState& ui_state);
	void moveDown(UIState& ui_state);
	int getSelectedItemIndex(UIState& ui_state);
	void UpdateUI(UIState& uiState, const struct SGame& game);
	void DrawUI(UIState& uiState, SGame& game, sf::RenderWindow& window);
	void PlaySound(UIState& uiState, const sf::SoundBuffer& buffer);
}