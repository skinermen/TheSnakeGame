#include <string>
#include "UI.h"
#include <random>
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
		InitTextUI(uiState.mainMenuTextStartGame, font, 72, 1, sf::Color::White, "SNAKE");
		uiState.mainMenuTextStartGame.setOrigin(GetTextOrigin(uiState.mainMenuTextStartGame, { 0.5f, 0.5f }));
		InitMainMenu(uiState, font, uiState.textItems);

		// Quit Menu Text
		InitTextUI(uiState.quitMenuText, font, 48, 1, sf::Color::White, "Pause menu");
		InitTextUI(uiState.quitMenuTextVariants, font, 24, 3, sf::Color::White,
			"Esc - resume\nSpace - restart\nM - main menu\nEnter - quit");
		
		// Winner Text
		InitTextUI(uiState.winnerText, font, 76, 1, sf::Color::Green, "WINNER");
		uiState.winnerText.setOrigin(GetTextOrigin(uiState.winnerText, { 0.5f, 0.5f }));

		// Scoreboard
		InitTextUI(uiState.scoreboardTextTitle, font, 48, 1, sf::Color::White, "Scoreboard:");
		uiState.scoreboardTextTitle.setOrigin(GetTextOrigin(uiState.scoreboardTextTitle, { 0.5f, 0.5f }));

		InitTextUI(uiState.scoreboardTextInstructions, font, 24, 1, sf::Color::White, "Press ESC to return to the main menu");
		uiState.scoreboardTextInstructions.setOrigin(GetTextOrigin(uiState.scoreboardTextInstructions, { 0.5f, 0.5f }));

		for (Scoreboard& item : uiState.vectorScoreTable)
		{
			if (item.name == "YOU")
			{
				item.score = 0;
			}
			else
			{
				item.score = GetRandomInt(10, 20);
			}
		}
	}

	void InitScoreboard(UIState& uiState, int numEatenFoods, const sf::Font& font, std::vector<Scoreboard>& scoreTable)
	{
		int i = 0;
        
		// Sort vector Score Table
		stable_sort(uiState.vectorScoreTable.begin(), uiState.vectorScoreTable.end(),
					[](const Scoreboard& a, const Scoreboard& b)
					{
						return a.score > b.score;
					});

		// Init text
		for (Scoreboard& item : scoreTable)
		{
			if (item.name == "YOU")
			{
				InitTextUI(uiState.scoreboardNameText[i], font, 40, 1, sf::Color::White);
				if (item.score < numEatenFoods)
				{
					item.score = numEatenFoods;
				}
			}
			else
			{
				InitTextUI(uiState.scoreboardNameText[i], font, 40, 1, sf::Color::Green);
			}

			uiState.scoreboardNameText[i].setString(item.name + ": " + std::to_string(item.score));
			uiState.scoreboardNameText[i].setOrigin(100.f, 10.f);
			++i;
		}
	}

	void InitMainMenu(UIState& uiState, const sf::Font& font, std::vector<sf::Text> textItems)
	{
		for (int i = 0; i < uiState.mainMenuItems.size(); i++)
		{
			sf::Text menuItem;
			menuItem.setFont(font);
			InitTextUI(menuItem, font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White), uiState.mainMenuItems[i]);
			// menuItem.setOrigin(GetTextOrigin(uiState.mainMenuTextStartGame, { 0.5f, 0.5f }));
			uiState.textItems.push_back(menuItem);
		}
		uiState.selectedItemIndex = 0; // Начальный выбор
	}

	void moveUp(UIState& ui_state)
	{
		if (ui_state.selectedItemIndex > 0)
		{
			ui_state.textItems[ui_state.selectedItemIndex].setFillColor(sf::Color::White);
			ui_state.selectedItemIndex--;
			ui_state.textItems[ui_state.selectedItemIndex].setFillColor(sf::Color::Green);
		}
	}

	void moveDown(UIState& ui_state)
	{
		if (ui_state.selectedItemIndex < ui_state.textItems.size() - 1)
		{
			ui_state.textItems[ui_state.selectedItemIndex].setFillColor(sf::Color::White);
			ui_state.selectedItemIndex++;
			ui_state.textItems[ui_state.selectedItemIndex].setFillColor(sf::Color::Green);
		}
	}

	int getSelectedItemIndex(UIState& ui_state)
	{
		return ui_state.selectedItemIndex;
	}

	void UpdateUI(UIState& uiState, const struct SGame& game)
	{
		uiState.scoreText.setString("Scores: " + std::to_string(game.numScores));
		uiState.scoreTextGameOver.setString("Scores: " + std::to_string(game.numScores));
		uiState.scoreTextGameOver.setOrigin(GetTextOrigin(uiState.scoreTextGameOver, { 0.5f, 0.5f }));

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
			uiState.isScoreboardVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::Playing)
		{
			uiState.isGameTextVisible = true;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isQuitMenuTextVisible = false;
			uiState.isWinnerTextVisible = false;
			uiState.isScoreboardVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::GameOver)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = true;
			uiState.isMainMenuTextVisible = false;
			uiState.isQuitMenuTextVisible = false;
			uiState.isWinnerTextVisible = false;
			uiState.isScoreboardVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::Scoreboard)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isQuitMenuTextVisible = false;
			uiState.isWinnerTextVisible = false;
			uiState.isScoreboardVisible = true;
		}

		if (GetCurrentGameState(game) == GameState::Winner)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isQuitMenuTextVisible = false;
			uiState.isWinnerTextVisible = true;
			uiState.isScoreboardVisible = false;
		}

		if (GetCurrentGameState(game) == GameState::QuitMenu)
		{
			uiState.isGameTextVisible = false;
			uiState.isGameOverTextVisible = false;
			uiState.isMainMenuTextVisible = false;
			uiState.isQuitMenuTextVisible = true;
			uiState.isWinnerTextVisible = false;
			uiState.isScoreboardVisible = false;
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

			game.backgroundLast = game.backgroundMenu;
			window.draw(game.backgroundMenu);
			
			
			uiState.mainMenuTextStartGame.setPosition(window.getSize().x / 2.f, 100.f);
			window.draw(uiState.mainMenuTextStartGame);
			float verticalIndentation = 0.f;
			
			for (int i = 0; i < uiState.mainMenuItems.size(); ++i)
			{
				sf::FloatRect bounds = uiState.textItems[i].getLocalBounds();
				uiState.textItems[i].setPosition((SCREEN_WIDTH - bounds.width) / 2, SCREEN_HEIGHT / 4.f + verticalIndentation);
				window.draw(uiState.textItems[i]);
				verticalIndentation += 60.f;
			}
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

		if (uiState.isScoreboardVisible)
		{
			// Blur screen
			window.draw(game.pauseBlurSprite);
			game.backgroundLast = game.backgroundScoreboard;

			// Score table
			InitScoreboard(uiState, game.numScores, game.font, uiState.vectorScoreTable);
			
			// Draw
			uiState.scoreboardTextTitle.setPosition(window.getSize().x / 2.f, 40.f);
			window.draw(uiState.scoreboardTextTitle);
			
			uiState.scoreboardTextInstructions.setPosition(window.getSize().x / 2.f, window.getSize().y - 50.f);
			window.draw(uiState.scoreboardTextInstructions);
			
			float verticalIndentation = 0.f;
			for (int i = 0; i < MAX_PLAYERS_TO_DISPLAY; ++i)
			{
				uiState.scoreboardNameText[i].setPosition(window.getSize().x / 2.f, 90.f + verticalIndentation);
				window.draw(uiState.scoreboardNameText[i]);
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
