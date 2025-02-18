#include <string>
#include <random>
#include <cassert>
#include "UI.h"

#include <iostream>

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
		text.setOrigin(GetTextOrigin(text));
	}

	void InitRectangleUI(sf::RectangleShape& rectangle, float sizeX, float sizeY, sf::Color fillColor, sf::Color outlineColor, float outlineThickness)
	{
		rectangle.setSize(sf::Vector2f(sizeX, sizeY));
		rectangle.setOrigin(rectangle.getSize().x / 2.f, rectangle.getSize().y / 2.f);
		rectangle.setFillColor(fillColor);
		rectangle.setOutlineColor(outlineColor);
		rectangle.setOutlineThickness(outlineThickness);
	}

	void InitUIResources(UIState& uiState)
	{
		assert(uiState.menuState.font.loadFromFile(RESOURCES_PATH + "\\Fonts/Roboto-Regular.ttf"));
		assert(uiState.snakeTextureHead.loadFromFile(RESOURCES_PATH + "\\snake.png"));
		assert(uiState.snakeTextureBody.loadFromFile(RESOURCES_PATH + "\\Snake_Body.png"));
		assert(uiState.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(uiState.wallTexture.loadFromFile(RESOURCES_PATH + "\\wall.png"));
		assert(uiState.noneTexture.loadFromFile(RESOURCES_PATH + "\\none.png"));
		assert(uiState.menuState.leaderboardTexture.loadFromFile(RESOURCES_PATH + "\\Scoreboard.png"));
		assert(uiState.menuState.mainMenuTexture.loadFromFile(RESOURCES_PATH + "\\Menu.png"));
		assert(uiState.icon.loadFromFile(RESOURCES_PATH + "\\Icon.png"));
		assert(uiState.eatAppleBuffer.loadFromFile(RESOURCES_PATH + "\\MushroomEat.wav"));
		assert(uiState.deathBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(uiState.winnerBuffer.loadFromFile(RESOURCES_PATH + "\\Winner.wav"));
		assert(uiState.musicMainTheme.openFromFile(RESOURCES_PATH + "\\FrenchMainMusic.wav"));
	}

	void InitUI(UIState& uiState)
	{
		InitUIResources(uiState);
		InitPauseTexture(uiState.menuState);
		uiState.noneSprite.setTexture(uiState.noneTexture);
		
		// Playing Resources
		InitRectangleUI(uiState.playingRectangle, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Transparent, sf::Color::White, 10.f);
		
		InitTextUI(uiState.playingScoreText, uiState.menuState.font, 24, 0, sf::Color::White);
		
		InitTextUI(uiState.playingInputText, uiState.menuState.font, 24, 0, sf::Color::White, "Use WASD to move, Space to restart, ESC to exit");

		// Main Menu Text
		InitMainMenu(uiState.menuState);
		
		// Pause Menu Text
		InitPauseMenu(uiState.menuState);

		// Name Input Menu Text
		InitNameInputMenu(uiState.menuState);
		
		// Confirmation Menu Text
		InitConfirmationMenu(uiState.menuState);
		
		// Game over Text
		InitGameOverMenu(uiState.menuState);

		// Difficulty Menu Text
		InitDifficultyMenu(uiState.menuState);

		// Score table
		InitLeaderboard(uiState.menuState);
		
	}

	void UpdateUI(UIState& uiState, const SGame& game)
	{
		uiState.playingScoreText.setString("Scores: " + std::to_string(uiState.menuState.numScores));
		uiState.menuState.gameOverScoreText.setString("Scores: " + std::to_string(uiState.menuState.numScores));
		uiState.isGameOverMenuTextVisible = GetCurrentGameState(game) == GameState::GameOver;

		if (GetCurrentGameState(game) == GameState::Playing)
		{
			uiState.isPlayingTextVisible = true;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = false;
			uiState.isNameInputMenuTextVisible = false;
			uiState.isConfirmationMenuTextVisible = false;
			uiState.isGameOverMenuTextVisible = false;
			uiState.isDifficultyMenuTextVisible = false;
			uiState.isScoreboardMenuVisible = false;
			uiState.isOptionsMenuTextVisible = false;
		}
		
		if (GetCurrentGameState(game) == GameState::MainMenu)
		{
			uiState.isPlayingTextVisible = false;
			uiState.isMainMenuTextVisible = true;
			uiState.isPauseMenuTextVisible = false;
			uiState.isNameInputMenuTextVisible = false;
			uiState.isConfirmationMenuTextVisible = false;
			uiState.isGameOverMenuTextVisible = false;
			uiState.isDifficultyMenuTextVisible = false;
			uiState.isScoreboardMenuVisible = false;
			uiState.isOptionsMenuTextVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::PauseMenu)
		{
			uiState.isPlayingTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = true;
			uiState.isNameInputMenuTextVisible = false;
			uiState.isConfirmationMenuTextVisible = false;
			uiState.isGameOverMenuTextVisible = false;
			uiState.isDifficultyMenuTextVisible = false;
			uiState.isScoreboardMenuVisible = false;
			uiState.isOptionsMenuTextVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::NameInputMenu)
		{
			uiState.isPlayingTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = false;
			uiState.isNameInputMenuTextVisible = true;
			uiState.isConfirmationMenuTextVisible = false;
			uiState.isGameOverMenuTextVisible = false;
			uiState.isDifficultyMenuTextVisible = false;
			uiState.isScoreboardMenuVisible = false;
			uiState.isOptionsMenuTextVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::ConfirmationMenu)
		{
			uiState.isPlayingTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = false;
			uiState.isNameInputMenuTextVisible = false;
			uiState.isConfirmationMenuTextVisible = true;
			uiState.isGameOverMenuTextVisible = false;
			uiState.isDifficultyMenuTextVisible = false;
			uiState.isScoreboardMenuVisible = false;
			uiState.isOptionsMenuTextVisible = false;
		}
		
		if (GetCurrentGameState(game) == GameState::GameOver)
		{
			uiState.isPlayingTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = false;
			uiState.isNameInputMenuTextVisible = false;
			uiState.isConfirmationMenuTextVisible = false;
			uiState.isGameOverMenuTextVisible = true;
			uiState.isDifficultyMenuTextVisible = false;
			uiState.isScoreboardMenuVisible = false;
			uiState.isOptionsMenuTextVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::Difficulty)
		{
			uiState.isPlayingTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = false;
			uiState.isNameInputMenuTextVisible = false;
			uiState.isConfirmationMenuTextVisible = false;
			uiState.isGameOverMenuTextVisible = false;
			uiState.isDifficultyMenuTextVisible = true;
			uiState.isScoreboardMenuVisible = false;
			uiState.isOptionsMenuTextVisible = false;
		}
		
		if (GetCurrentGameState(game) == GameState::Leaderboard)
		{
			uiState.isPlayingTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = false;
			uiState.isNameInputMenuTextVisible = false;
			uiState.isConfirmationMenuTextVisible = false;
			uiState.isGameOverMenuTextVisible = false;
			uiState.isDifficultyMenuTextVisible = false;
			uiState.isScoreboardMenuVisible = true;
			uiState.isOptionsMenuTextVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::Options)
		{
			uiState.isPlayingTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isPauseMenuTextVisible = false;
			uiState.isNameInputMenuTextVisible = false;
			uiState.isConfirmationMenuTextVisible = false;
			uiState.isGameOverMenuTextVisible = false;
			uiState.isDifficultyMenuTextVisible = false;
			uiState.isScoreboardMenuVisible = false;
			uiState.isOptionsMenuTextVisible = true;
		}

	}

	void DrawUI(UIState& uiState, sf::RenderWindow& window)
	{
		if (uiState.isPlayingTextVisible)
		{
			uiState.playingRectangle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
			window.draw(uiState.playingRectangle);
			
			uiState.playingScoreText.setPosition(10.f + BORDER_SIZE, 10.f + BORDER_SIZE);
			uiState.playingScoreText.setOrigin(0.f, 0.f);
			window.draw(uiState.playingScoreText);

			uiState.playingInputText.setPosition(window.getSize().x - 10.f - BORDER_SIZE, 10.f + BORDER_SIZE);
			uiState.playingInputText.setOrigin(uiState.playingInputText.getLocalBounds().width, 0.f);
			window.draw(uiState.playingInputText);
		}

		if (uiState.isMainMenuTextVisible)
		{
			DrawMainMenu(uiState.menuState, window);
		}

		if (uiState.isPauseMenuTextVisible)
		{
			uiState.musicMainTheme.pause();
			DrawPauseMenu(uiState.menuState, window);
		}

		if (uiState.isNameInputMenuTextVisible)
		{
			DrawNameInputMenu(uiState.menuState, window);
		}

		if (uiState.isConfirmationMenuTextVisible)
		{
			uiState.musicMainTheme.pause();
			DrawConfirmationMenu(uiState.menuState, window);
		}

		if (uiState.isGameOverMenuTextVisible)
		{
			uiState.musicMainTheme.pause();
			DrawGameOverMenu(uiState.menuState, window);
		}

		if (uiState.isDifficultyMenuTextVisible)
		{
			DrawDifficultyMenu(uiState.menuState, window);
		}

		if (uiState.isScoreboardMenuVisible)
		{
			DrawLeaderboard(uiState.menuState, window);
		}
		
		if (uiState.isOptionsMenuTextVisible)
		{
			DrawOptionsMenu(uiState.menuState, window);
		}
	}

	void PlaySound(UIState& uiState, const sf::SoundBuffer& buffer)
	{
		uiState.sound.setBuffer(buffer);
		uiState.sound.setVolume(50);
		uiState.sound.play();
	}
}
