#include <string>
#include "Menu.h"
#include "Math.h"
#include "UI.h"

namespace SnakeGame
{
	void InitPauseTexture(MenuState& menuState)
	{
		// Init pause texture
		menuState.pauseBlurTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
		menuState.pauseBlurTexture.clear(sf::Color(0, 0, 0, 100));
		menuState.pauseBlurSprite.setTexture(menuState.pauseBlurTexture.getTexture());
	}
	
	void InitMainMenu(MenuState& menuState, const sf::Font& font, std::vector<sf::Text> textItems)
	{
		InitTextUI(menuState.mainMenuTextStartGame, font, 72, 1, sf::Color::White, "SNAKE");
		menuState.mainMenuTextStartGame.setOrigin(GetTextOrigin(menuState.mainMenuTextStartGame, { 0.5f, 0.5f }));
		
		for (int i = 0; i < menuState.mainMenuItems.size(); i++)
		{
			sf::Text menuItem;
			menuItem.setFont(font);
			InitTextUI(menuItem, font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White), menuState.mainMenuItems[i]);
			menuState.textItems.push_back(menuItem);
		}
		menuState.selectedItemIndex = 0;
	}

	void InitScoreboard(MenuState& menuState, int numEatenFoods, const sf::Font& font, std::vector<Scoreboard>& scoreTable)
	{
		InitTextUI(menuState.scoreboardTextTitle, font, 48, 1, sf::Color::White, "Scoreboard:");
		menuState.scoreboardTextTitle.setOrigin(GetTextOrigin(menuState.scoreboardTextTitle, { 0.5f, 0.5f }));

		InitTextUI(menuState.scoreboardTextInstructions, font, 24, 1, sf::Color::White, "Press ESC to return to the main menu");
		menuState.scoreboardTextInstructions.setOrigin(GetTextOrigin(menuState.scoreboardTextInstructions, { 0.5f, 0.5f }));

		for (Scoreboard& item : menuState.vectorScoreTable)
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
		
		int i = 0;
        
		// Sort vector Score Table
		stable_sort(menuState.vectorScoreTable.begin(), menuState.vectorScoreTable.end(),
					[](const Scoreboard& a, const Scoreboard& b)
					{
						return a.score > b.score;
					});

		// Init text
		for (Scoreboard& item : scoreTable)
		{
			if (item.name == "YOU")
			{
				InitTextUI(menuState.scoreboardNameText[i], font, 40, 1, sf::Color::White);
				if (item.score < numEatenFoods)
				{
					item.score = numEatenFoods;
				}
			}
			else
			{
				InitTextUI(menuState.scoreboardNameText[i], font, 40, 1, sf::Color::Green);
			}

			menuState.scoreboardNameText[i].setString(item.name + ": " + std::to_string(item.score));
			menuState.scoreboardNameText[i].setOrigin(100.f, 10.f);
			++i;
		}
	}

	void InitPauseMenu(MenuState& menuState)
	{
		InitTextUI(menuState.pauseMenuText, menuState.font, 48, 1, sf::Color::White, "Pause menu");
		InitTextUI(menuState.pauseMenuTextVariants, menuState.font, 24, 3, sf::Color::White,
			"Esc - resume\nSpace - restart\nM - main menu\nEnter - quit");
	}

	void InitGameOverMenu(MenuState& menuState)
	{
		InitTextUI(menuState.gameOverScoreText, menuState.font, 48, 1, sf::Color::Yellow);
		menuState.gameOverScoreText.setOrigin(GetTextOrigin(menuState.gameOverScoreText, { 0.5f, 0.5f }));
		InitTextUI(menuState.gameOverText, menuState.font, 76, 1, sf::Color::Yellow, "GAME OVER");
		menuState.gameOverText.setOrigin(GetTextOrigin(menuState.gameOverText, { 0.5f, 0.5f }));
		InitTextUI(menuState.gameOverTextInstructions, menuState.font, 24, 1, sf::Color::Yellow, "SPACE - restart game\nM - menu\nEsc - quit");
		menuState.gameOverTextInstructions.setOrigin(GetTextOrigin(menuState.gameOverTextInstructions, { 0.5f, 0.5f }));
	}

	void InitWinnerMenu(MenuState& menuState)
	{
		InitTextUI(menuState.winnerText, menuState.font, 76, 1, sf::Color::Green, "WINNER");
		menuState.winnerText.setOrigin(GetTextOrigin(menuState.winnerText, { 0.5f, 0.5f }));
	}

	void InitDifficultyMenu(MenuState& menuState)
	{
		
	}

	void InitOptionsMenu(MenuState& menuState)
	{
		
	}

	void DrawMainMenu(MenuState& menuState, sf::RenderWindow& window)
	{
		menuState.backgroundLast = menuState.backgroundMenu;
		window.draw(menuState.backgroundMenu);
		
		menuState.mainMenuTextStartGame.setPosition(window.getSize().x / 2.f, 100.f);
		window.draw(menuState.mainMenuTextStartGame);
		float verticalIndentation = 0.f;
			
		for (int i = 0; i < menuState.mainMenuItems.size(); ++i)
		{
			sf::FloatRect bounds = menuState.textItems[i].getLocalBounds();
			menuState.textItems[i].setPosition((SCREEN_WIDTH - bounds.width) / 2, SCREEN_HEIGHT / 4.f + verticalIndentation);
			window.draw(menuState.textItems[i]);
			verticalIndentation += 60.f;
		}
	}
	
	void DrawScoreboard(MenuState& menuState, sf::RenderWindow& window)
	{
		// Blur screen
		window.draw(menuState.pauseBlurSprite);
		menuState.backgroundLast = menuState.backgroundScoreboard;
			
		// Draw
		menuState.scoreboardTextTitle.setPosition(window.getSize().x / 2.f, 40.f);
		window.draw(menuState.scoreboardTextTitle);
			
		menuState.scoreboardTextInstructions.setPosition(window.getSize().x / 2.f, window.getSize().y - 50.f);
		window.draw(menuState.scoreboardTextInstructions);
			
		float verticalIndentation = 0.f;
		for (int i = 0; i < MAX_PLAYERS_TO_DISPLAY; ++i)
		{
			menuState.scoreboardNameText[i].setPosition(window.getSize().x / 2.f, 90.f + verticalIndentation);
			window.draw(menuState.scoreboardNameText[i]);
			verticalIndentation += 40.f;
		}
	}

	void DrawPauseMenu(MenuState& menuState, sf::RenderWindow& window)
	{
		window.draw(menuState.pauseBlurSprite);
			
		menuState.pauseMenuText.setPosition(10.f, 410.f);
		window.draw(menuState.pauseMenuText);

		menuState.pauseMenuTextVariants.setPosition(10.f, 470.f);
		window.draw(menuState.pauseMenuTextVariants);
	}

	void DrawGameOverMenu(MenuState& menuState, sf::RenderWindow& window)
	{
		window.draw(menuState.pauseBlurSprite);
			
		menuState.gameOverText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
		window.draw(menuState.gameOverText);

		menuState.gameOverScoreText.setPosition(window.getSize().x / 2.f, 15.f);
		window.draw(menuState.gameOverScoreText);
			
		menuState.gameOverTextInstructions.setPosition(window.getSize().x / 2.f, window.getSize().y - 45.f);
		window.draw(menuState.gameOverTextInstructions);
	}

	void DrawWinnerMenu(MenuState& menuState, sf::RenderWindow& window)
	{
		window.draw(menuState.pauseBlurSprite);
			
		menuState.winnerText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
		window.draw(menuState.winnerText);

		menuState.gameOverScoreText.setPosition(window.getSize().x / 2.f, 15.f);
		window.draw(menuState.gameOverScoreText);
			
		menuState.gameOverTextInstructions.setPosition(window.getSize().x / 2.f, window.getSize().y - 45.f);
		window.draw(menuState.gameOverTextInstructions);
	}

	void DrawDifficultyMenu(MenuState& menuState, sf::RenderWindow& window)
	{
		
	}

	void DrawOptionsMenu(MenuState& menuState, sf::RenderWindow& window)
	{
		
	}
	
	void moveUp(MenuState& menuState)
	{
		if (menuState.selectedItemIndex > 0)
		{
			menuState.textItems[menuState.selectedItemIndex].setFillColor(sf::Color::White);
			menuState.selectedItemIndex--;
			menuState.textItems[menuState.selectedItemIndex].setFillColor(sf::Color::Green);
		}
	}

	void moveDown(MenuState& menuState)
	{
		if (menuState.selectedItemIndex < menuState.textItems.size() - 1)
		{
			menuState.textItems[menuState.selectedItemIndex].setFillColor(sf::Color::White);
			menuState.selectedItemIndex++;
			menuState.textItems[menuState.selectedItemIndex].setFillColor(sf::Color::Green);
		}
	}

	int getSelectedItemIndex(MenuState& menuState)
	{
		return menuState.selectedItemIndex;
	}
	
}
