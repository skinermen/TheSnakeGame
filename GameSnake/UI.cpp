#include <string>
#include <random>
#include <cassert>
#include "UI.h"
#include "Game.h"

namespace SnakeGame
{
	void InitTextUI(sf::Text& text, const sf::Font& font, int size, int style, sf::Color color, const std::string& name)
	{
		text.setFont(font);
		text.setCharacterSize(size);
		text.setStyle(style);
		text.setFillColor(color);
		text.setString(name);
	}

	void InitUIResources(UIState& uiState)
	{
		assert(uiState.menuState.font.loadFromFile(RESOURCES_PATH + "\\Fonts/Roboto-Regular.ttf"));
		assert(uiState.snakeTextureHead.loadFromFile(RESOURCES_PATH + "\\snake.png"));
		assert(uiState.snakeTextureBody.loadFromFile(RESOURCES_PATH + "\\Snake_Body.png"));
		assert(uiState.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(uiState.wallTexture.loadFromFile(RESOURCES_PATH + "\\wall.png"));
		assert(uiState.noneTexture.loadFromFile(RESOURCES_PATH + "\\none.png"));
		// assert(uiState.grassTexture.loadFromFile(RESOURCES_PATH + "\\Grass.png"));
		assert(uiState.menuState.scoreboardTexture.loadFromFile(RESOURCES_PATH + "\\Scoreboard.png"));
		assert(uiState.menuState.mainMenuTexture.loadFromFile(RESOURCES_PATH + "\\Menu.png"));
		assert(uiState.icon.loadFromFile(RESOURCES_PATH + "\\Icon.png"));
		assert(uiState.eatAppleBuffer.loadFromFile(RESOURCES_PATH + "\\MushroomEat.wav"));
		assert(uiState.deathBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(uiState.winnerBuffer.loadFromFile(RESOURCES_PATH + "\\Winner.wav"));
		assert(uiState.musicMainTheme.openFromFile(RESOURCES_PATH + "\\FrenchMainMusic.wav"));
	}

	void InitUI(UIState& uiState, const sf::Font& font)
	{
		InitUIResources(uiState);
		InitPauseTexture(uiState.menuState);
		uiState.noneSprite.setTexture(uiState.noneTexture);
		
		// Score Text
		InitTextUI(uiState.gameScoreText, font, 24, 0, sf::Color::White);

		// Input Text
		InitTextUI(uiState.inputText, font, 24, 0, sf::Color::White, "Use WASD to move, Space to restart, ESC to exit");
		uiState.inputText.setOrigin(GetTextOrigin(uiState.inputText, { 1.f, 0.f }));

		// Game over Text
		InitGameOverMenu(uiState.menuState);

		// Main Menu Text
		InitMainMenu(uiState.menuState, font, uiState.menuState.textItems);

		// Score table
		InitScoreboard(uiState.menuState, uiState.menuState.numScores, uiState.menuState.font, uiState.menuState.vectorScoreTable);
		
		// Pause Menu Text
		InitPauseMenu(uiState.menuState);
		
		// Winner Text
		InitWinnerMenu(uiState.menuState);
	}

	void UpdateUI(UIState& uiState, const struct SGame& game)
	{
		uiState.gameScoreText.setString("Scores: " + std::to_string(uiState.menuState.numScores));
		uiState.menuState.gameOverScoreText.setString("Scores: " + std::to_string(uiState.menuState.numScores));
		uiState.isGameOverTextVisible = GetCurrentGameState(game) == GameState::GameOver;
		sf::Color gameOverTextColor = (int)game.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;

		uiState.menuState.gameOverText.setFillColor(gameOverTextColor);

		if (GetCurrentGameState(game) == GameState::MainMenu)
		{
			uiState.isGameTextVisible = true;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = true;
			uiState.isPauseMenuTextVisible = false;
			uiState.isWinnerTextVisible = false;
			uiState.isScoreboardVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::Playing)
		{
			uiState.isGameTextVisible = true;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = false;
			uiState.isWinnerTextVisible = false;
			uiState.isScoreboardVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::GameOver)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = true;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = false;
			uiState.isWinnerTextVisible = false;
			uiState.isScoreboardVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::Scoreboard)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = false;
			uiState.isWinnerTextVisible = false;
			uiState.isScoreboardVisible = true;
		}

		if (GetCurrentGameState(game) == GameState::Winner)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = false;
			uiState.isWinnerTextVisible = true;
			uiState.isScoreboardVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::QuitMenu)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = true;
			uiState.isWinnerTextVisible = false;
			uiState.isScoreboardVisible = false;
		}
	}

	void DrawUI(UIState& uiState, SGame& game, sf::RenderWindow& window)
	{
		if (uiState.isGameTextVisible)
		{
			uiState.gameScoreText.setPosition(10.f, 10.f);
			window.draw(uiState.gameScoreText);

			uiState.inputText.setPosition(window.getSize().x - 10.f, 10.f);
			window.draw(uiState.inputText);
		}

		if (uiState.isMainMenuTextVisible)
		{
			DrawMainMenu(uiState.menuState, window);
		}

		if (uiState.isScoreboardVisible)
		{
			DrawScoreboard(uiState.menuState, window);
		}

		if (uiState.isPauseMenuTextVisible)
		{
			DrawPauseMenu(uiState.menuState, window);
		}

		if (uiState.isGameOverTextVisible)
		{
			DrawGameOverMenu(uiState.menuState, window);
		}

		if (uiState.isWinnerTextVisible)
		{
			DrawWinnerMenu(uiState.menuState, window);
		}
	}

	void PlaySound(UIState& uiState, const sf::SoundBuffer& buffer)
	{
		uiState.sound.setBuffer(buffer);
		uiState.sound.setVolume(50);
		uiState.sound.play();
	}
}
