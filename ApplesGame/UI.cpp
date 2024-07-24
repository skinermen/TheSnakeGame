#include <string>
#include "UI.h"
#include <random>
#include "Game.h"

namespace ApplesGame
{
	void InitTextUI(sf::Text& text, const sf::Font& font, int size, int style, sf::Color color, const std::string& name)
	{
		text.setFont(font);
		text.setCharacterSize(size);
		text.setStyle(style);
		text.setFillColor(color);
		text.setString(name);
	}

	void InitUI(UIState& uiState, const sf::Font& font)
	{
		// Score Text
		InitTextUI(uiState.scoreText, font, 24, 0, sf::Color::White);
		InitTextUI(uiState.scoreTextGameOver, font, 48, 1, sf::Color::Yellow);

		// Input Text
		InitTextUI(uiState.inputText, font, 24, 0, sf::Color::White, "Use WASD to move, Space to restart, ESC to exit");
		uiState.inputText.setOrigin(GetTextOrigin(uiState.inputText, { 1.f, 0.f }));

		// Game over Text
		InitTextUI(uiState.gameOverText, font, 76, 1, sf::Color::Yellow, "GAME OVER");
		uiState.gameOverText.setOrigin(GetTextOrigin(uiState.gameOverText, { 0.5f, 0.5f }));
		InitTextUI(uiState.gameOverTextInstructions, font, 24, 1, sf::Color::Yellow, "SPACE - restart game\nM - menu\nEsc - quit");
		uiState.gameOverTextInstructions.setOrigin(GetTextOrigin(uiState.gameOverTextInstructions, { 0.5f, 0.5f }));

		// Main Menu Text
		InitTextUI(uiState.mainMenuTextStartGame, font, 72, 1, sf::Color::Green, "Press the SPACE\nto start the game");
		uiState.mainMenuTextStartGame.setOrigin(GetTextOrigin(uiState.mainMenuTextStartGame, { 0.5f, 0.5f }));
		InitTextUI(uiState.mainMenuTextInsructions, font, 24, 3, sf::Color::Green, "Use the keys 1, 2 to select the game mode");
		InitTextUI(uiState.mainMenuGameModeUnlimitedFoods, font, 24, 1, sf::Color::White);
		InitTextUI(uiState.mainMenuGameModeAcceleration, font, 24, 1, sf::Color::White);

		// Quit Menu Text
		InitTextUI(uiState.quitMenuText, font, 48, 1, sf::Color::White, "Pause menu");
		InitTextUI(uiState.quitMenuTextVariants, font, 24, 3, sf::Color::White,
			"Esc - resume\nSpace - restart\nM - main menu\nEnter - quit");
		
		// Winner Text
		InitTextUI(uiState.winnerText, font, 76, 1, sf::Color::Green, "WINNER");
		uiState.winnerText.setOrigin(GetTextOrigin(uiState.winnerText, { 0.5f, 0.5f }));

		// Leaderboard
		for (Leaderboard& item : uiState.vectorScoreTable)
		{
			if (item.name == "YOU")
			{
				item.score = 0;
			}
			else
			{
				item.score = GetRandomInt(5, NUM_FOOD_MAX - 5);
			}
		}
	}

	void InitLeaderboard(UIState& uiState, int numEatenFoods, const sf::Font& font, std::vector<Leaderboard>& scoreTable)
	{
		int i = 0;
        
		// Sort vector Score Table
		stable_sort(uiState.vectorScoreTable.begin(), uiState.vectorScoreTable.end(),
					[](const Leaderboard& a, const Leaderboard& b)
					{
						return a.score > b.score;
					});

		// Init text
		for (Leaderboard& item : scoreTable)
		{
			if (item.name == "YOU")
			{
				InitTextUI(uiState.leaderboardNameText[i], font, 40, 1, sf::Color::White);
				if (item.score < numEatenFoods)
				{
					item.score = numEatenFoods;
				}
			}
			else
			{
				InitTextUI(uiState.leaderboardNameText[i], font, 40, 1, sf::Color::Green);
			}

			uiState.leaderboardNameText[i].setString(item.name + ": " + std::to_string(item.score));
			uiState.leaderboardNameText[i].setOrigin(100.f, 10.f);
			++i;
		}
	}

	void UpdateUI(UIState& uiState, const struct SGame& game)
	{
		uiState.scoreText.setString("Mushrooms eaten: " + std::to_string(game.numEatenFoods));
		uiState.scoreTextGameOver.setString("Scores: " + std::to_string(game.numEatenFoods));
		uiState.scoreTextGameOver.setOrigin(GetTextOrigin(uiState.scoreTextGameOver, { 0.5f, 0.5f }));

		uiState.mainMenuGameModeUnlimitedFoods.setString("Unlimited mushrooms: " + GetButtonText(game, MASK_INFINIT_FOODS));
		uiState.mainMenuGameModeAcceleration.setString("Acceleration of movement: " + GetButtonText(game, MASK_WITH_ACCELERATION));

		uiState.isGameOverTextVisible = GetCurrentGameState(game) == GameState::GameOver;
		sf::Color gameOverTextColor = (int)game.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		uiState.gameOverText.setFillColor(gameOverTextColor);

		if (GetCurrentGameState(game) == GameState::MainMenu)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = true;
			uiState.isQuitMenuTextVisible = false;
			uiState.isWinnerTextVisible = false;
			uiState.isLeaderboardVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::Playing)
		{
			uiState.isGameTextVisible = true;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isQuitMenuTextVisible = false;
			uiState.isWinnerTextVisible = false;
			uiState.isLeaderboardVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::GameOver)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = true;
			uiState.isMainMenuTextVisible = false;
			uiState.isQuitMenuTextVisible = false;
			uiState.isWinnerTextVisible = false;
			uiState.isLeaderboardVisible = false;
		}

		if (game.isScreenLeaderboard)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isQuitMenuTextVisible = false;
			uiState.isWinnerTextVisible = false;
			uiState.isLeaderboardVisible = true;
		}

		if (GetCurrentGameState(game) == GameState::Winner)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isQuitMenuTextVisible = false;
			uiState.isWinnerTextVisible = true;
			uiState.isLeaderboardVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::QuitMenu)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isQuitMenuTextVisible = true;
			uiState.isWinnerTextVisible = false;
			uiState.isLeaderboardVisible = false;
		}
	}

	void DrawUI(UIState& uiState, SGame& game, sf::RenderWindow& window)
	{
		// Init pause texture
		game.pauseBlurTexture.create(window.getSize().x, window.getSize().y);
		game.pauseBlurTexture.clear(sf::Color(0, 0, 0, 100));
		game.pauseBlurSprite.setTexture(game.pauseBlurTexture.getTexture());
		
		if (uiState.isGameTextVisible)
		{
			uiState.scoreText.setPosition(10.f, 10.f);
			window.draw(uiState.scoreText);

			uiState.inputText.setPosition(window.getSize().x - 10.f, 10.f);
			window.draw(uiState.inputText);
		}

		if (uiState.isMainMenuTextVisible)
		{
			if (GetCurrentGameState(game) == GameState::MainMenu)
			{
				game.backgroundLast = game.backgroundMenu;
				window.draw(game.backgroundMenu);
			}
			
			uiState.mainMenuTextStartGame.setPosition(window.getSize().x / 2.f, 100.f);
			window.draw(uiState.mainMenuTextStartGame);
			
			uiState.mainMenuTextInsructions.setPosition(10.f, window.getSize().y - 100.f);
			window.draw(uiState.mainMenuTextInsructions);

			uiState.mainMenuGameModeUnlimitedFoods.setPosition(10.f, window.getSize().y - 75.f);
			window.draw(uiState.mainMenuGameModeUnlimitedFoods);

			uiState.mainMenuGameModeAcceleration.setPosition(10.f, window.getSize().y - 50.f);
			window.draw(uiState.mainMenuGameModeAcceleration);
		}

		if (uiState.isGameOverTextVisible)
		{
			// Blur screen
			window.draw(game.pauseBlurSprite);
			
			uiState.gameOverText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			window.draw(uiState.gameOverText);

			uiState.scoreTextGameOver.setPosition(window.getSize().x / 2.f, 15.f);
			window.draw(uiState.scoreTextGameOver);
			
			uiState.gameOverTextInstructions.setPosition(window.getSize().x / 2.f, window.getSize().y - 45.f);
			window.draw(uiState.gameOverTextInstructions);
		}

		if (uiState.isWinnerTextVisible)
		{
			// Blur screen
			window.draw(game.pauseBlurSprite);
			
			uiState.winnerText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			window.draw(uiState.winnerText);

			uiState.scoreTextGameOver.setPosition(window.getSize().x / 2.f, 15.f);
			window.draw(uiState.scoreTextGameOver);
			
			uiState.gameOverTextInstructions.setPosition(window.getSize().x / 2.f, window.getSize().y - 45.f);
			window.draw(uiState.gameOverTextInstructions);
		}

		if (uiState.isLeaderboardVisible)
		{
			// Blur screen
			window.draw(game.pauseBlurSprite);

			// Score table
			InitLeaderboard(uiState, game.numEatenFoods, game.font, uiState.vectorScoreTable);
			
			// Draw
			float verticalIndentation = 0.f;
			for (int i = 0; i < MAX_PLAYERS_TO_DISPLAY; ++i)
			{
				uiState.leaderboardNameText[i].setPosition(window.getSize().x / 2.f, window.getSize().y / 5.f + verticalIndentation);
				window.draw(uiState.leaderboardNameText[i]);
				verticalIndentation += 40.f;
			}
		}

		if (uiState.isQuitMenuTextVisible)
		{
			if (GetPreviousGameState(game) == GameState::MainMenu)
			{
				window.draw(game.backgroundLast);
			}
			
			// Blur screen
			window.draw(game.pauseBlurSprite);
			
			uiState.quitMenuText.setPosition(10.f, 410.f);
			window.draw(uiState.quitMenuText);

			uiState.quitMenuTextVariants.setPosition(10.f, 470.f);
			window.draw(uiState.quitMenuTextVariants);
		}
	}

	void PlaySound(UIState& uiState, const sf::SoundBuffer& buffer)
	{
		uiState.sound.setBuffer(buffer);
		uiState.sound.setVolume(50);
		uiState.sound.play();
	}
}
