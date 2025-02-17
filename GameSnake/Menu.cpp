#include <string>
#include "Menu.h"
#include "Game.h"
#include "Math.h"
#include "UI.h"

namespace SnakeGame
{
	void InitPauseTexture(SMenuState& menuState)
	{
		// Init pause texture
		menuState.pauseBlurTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
		menuState.pauseBlurTexture.clear(sf::Color(0, 0, 0, 220));
		menuState.pauseBlurSprite.setTexture(menuState.pauseBlurTexture.getTexture());
	}
	
	void InitMainMenu(SMenuState& menuState, const sf::Font& font)
	{
		InitRectangleUI(menuState.mainMenuRectangle, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Transparent, sf::Color::White, 10.f);
		
		InitTextUI(menuState.mainMenuTitle, font, 72, 1, sf::Color::White, "SNAKE");
		
		for (int i = 0; i < menuState.VStringMainMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White), menuState.VStringMainMenuItems[i]);
			menuState.vTextMainMenuItems.push_back(menuItem);
		}
	}
	
	void InitPauseMenu(SMenuState& menuState, const sf::Font& font)
	{
		InitRectangleUI(menuState.pauseMenuRectangle, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Transparent, sf::Color::White, 10.f);
		InitTextUI(menuState.pauseMenuTitle, font, 64, 1, sf::Color::White, "Pause menu");
		
		for (int i = 0; i < menuState.VStringPauseMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				menuState.VStringPauseMenuItems[i]);
			menuState.vTextPauseMenuItems.push_back(menuItem);
		}
	}

	void InitGameOverMenu(SMenuState& menuState, const sf::Font& font)
	{
		InitRectangleUI(menuState.gameOverRectangle, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		InitTextUI(menuState.gameOverScoreText, menuState.font, 48, 1, sf::Color::White);

		for (int i = 0; i < menuState.VStringGameOverMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				menuState.VStringGameOverMenuItems[i]);
			menuState.vTextGameOverMenuItems.push_back(menuItem);
		}
	}

	void InitDifficultyMenu(SMenuState& menuState, const sf::Font& font)
	{
		InitRectangleUI(menuState.difficultyMenuRectangle, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		InitTextUI(menuState.difficultyMenuTitle, menuState.font, 48, 1, sf::Color::White, "Choosing the difficulty");

		for (int i = 0; i < menuState.VStringDifficultyMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				menuState.VStringDifficultyMenuItems[i].nameDifficulty);
			menuState.vTextDifficultyMenuItems.push_back(menuItem);
		}
	}
	
	void InitLeaderboard(SMenuState& menuState, int numEatenFoods, const sf::Font& font, std::vector<SLeaderboard>& leaderTable)
	{
		InitTextUI(menuState.leaderboardTextTitle, font, 48, 1, sf::Color::White, "Scoreboard:");
		InitTextUI(menuState.leaderboardTextInstructions, font, 24, 1, sf::Color::White, "Press ESC to return to the main menu");

		for (SLeaderboard& item : menuState.VLeaderboardItems)
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
		std::ranges::stable_sort
		(menuState.VLeaderboardItems, [](const SLeaderboard& a, const SLeaderboard& b)
			{
				return a.score > b.score;
			}
		);

		// Init text
		for (SLeaderboard& item : leaderTable)
		{
			if (item.name == "YOU")
			{
				InitTextUI(menuState.leaderboardNameText[i], font, 40, 1, sf::Color::White);
				if (item.score < numEatenFoods)
				{
					item.score = numEatenFoods;
				}
			}
			else
			{
				InitTextUI(menuState.leaderboardNameText[i], font, 40, 1, sf::Color::Green);
			}

			menuState.leaderboardNameText[i].setString(item.name + ": " + std::to_string(item.score));
			menuState.leaderboardNameText[i].setOrigin(100.f, 10.f);
			++i;
		}
	}

	void InitOptionsMenu(SMenuState& menuState)
	{
		
	}

	void DrawMainMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		menuState.backgroundLast = menuState.backgroundMenu;
		window.draw(menuState.backgroundMenu);
		
		menuState.mainMenuRectangle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.mainMenuRectangle);
		
		menuState.mainMenuTitle.setPosition(SCREEN_WIDTH / 2.f, 100.f);
		window.draw(menuState.mainMenuTitle);
		
		DrawMenuItems(window, menuState.vTextMainMenuItems);
	}
	
	void DrawPauseMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		window.draw(menuState.pauseBlurSprite);
		
		menuState.pauseMenuRectangle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.pauseMenuRectangle);
			
		menuState.pauseMenuTitle.setPosition(SCREEN_WIDTH / 2.f, menuState.pauseMenuTitle.getLocalBounds().height);
		menuState.pauseMenuTitle.setOrigin(menuState.pauseMenuTitle.getLocalBounds().width / 2.f,
			menuState.pauseMenuTitle.getLocalBounds().height);
		window.draw(menuState.pauseMenuTitle);

		DrawMenuItems(window, menuState.vTextPauseMenuItems);
	}
	
	void DrawGameOverMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		menuState.gameOverRectangle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.gameOverRectangle);

		menuState.gameOverScoreText.setPosition(SCREEN_WIDTH / 2.f, menuState.gameOverScoreText.getLocalBounds().height);
		menuState.gameOverScoreText.setOrigin(menuState.gameOverScoreText.getLocalBounds().width / 2.f,
			menuState.gameOverScoreText.getLocalBounds().height / 2.f);
		window.draw(menuState.gameOverScoreText);

		DrawMenuItems(window, menuState.vTextGameOverMenuItems);
	}
	
	void DrawDifficultyMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		menuState.difficultyMenuRectangle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.difficultyMenuRectangle);

		menuState.difficultyMenuTitle.setPosition(SCREEN_WIDTH / 2.f, menuState.difficultyMenuTitle.getLocalBounds().height);
		menuState.difficultyMenuTitle.setOrigin(menuState.difficultyMenuTitle.getLocalBounds().width / 2.f,
			menuState.difficultyMenuTitle.getLocalBounds().height / 2.f);
		window.draw(menuState.difficultyMenuTitle);

		DrawMenuItems(window, menuState.vTextDifficultyMenuItems);
	}
	
	void DrawLeaderboard(SMenuState& menuState, sf::RenderWindow& window)
	{
		// Blur screen
		window.draw(menuState.pauseBlurSprite);
		menuState.backgroundLast = menuState.leaderboardBackground;
			
		// Draw
		menuState.leaderboardTextTitle.setPosition(SCREEN_WIDTH / 2.f, 40.f);
		window.draw(menuState.leaderboardTextTitle);
			
		menuState.leaderboardTextInstructions.setPosition(window.getSize().x / 2.f, window.getSize().y - 50.f);
		window.draw(menuState.leaderboardTextInstructions);
			
		float verticalIndentation = 0.f;
		for (int i = 0; i < MAX_LINES_TO_LEADERBOARD; ++i)
		{
			menuState.leaderboardNameText[i].setPosition(window.getSize().x / 2.f, 90.f + verticalIndentation);
			window.draw(menuState.leaderboardNameText[i]);
			verticalIndentation += 40.f;
		}
	}
	

	void DrawOptionsMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		
	}
	
	void DrawMenuItems(sf::RenderWindow& window, std::vector<sf::Text>& menuItems)
	{
		float verticalIndentation = 0.f;
		for (auto& menuItem : menuItems) // NOLINT(clang-diagnostic-sign-compare)
		{
			menuItem.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 4.f + verticalIndentation);
			window.draw(menuItem);
			verticalIndentation += 60.f;
		}
	}
	
	void MoveUp(SMenuState& menuState, std::vector<sf::Text>& menuItems)
	{
		if (menuState.selectedItemIndex > 0)
		{
			menuItems[menuState.selectedItemIndex].setFillColor(sf::Color::White);
			menuState.selectedItemIndex--;
			menuItems[menuState.selectedItemIndex].setFillColor(sf::Color::Green);
		}
	}
	
	void MoveDown(SMenuState& menuState, std::vector<sf::Text>& menuItems)
	{
		if (menuState.selectedItemIndex < menuItems.size() - 1)  // NOLINT(clang-diagnostic-sign-compare)
		{
			menuItems[menuState.selectedItemIndex].setFillColor(sf::Color::White);
			menuState.selectedItemIndex++;
			menuItems[menuState.selectedItemIndex].setFillColor(sf::Color::Green);
		}
	}

	void ResetMenuSelection(const SMenuState& menuState, std::vector<sf::Text>& menuItems)
	{
		for (auto& text : menuItems)
		{
			text.setFillColor(sf::Color::White);
		}
		menuItems[menuState.selectedItemIndex].setFillColor(sf::Color::Green);
	}
	void ResetAllMenuSelection(SMenuState& menuState)
	{
		menuState.selectedItemIndex = 0;

		ResetMenuSelection(menuState, menuState.vTextMainMenuItems);
		ResetMenuSelection(menuState, menuState.vTextDifficultyMenuItems);
		ResetMenuSelection(menuState, menuState.vTextPauseMenuItems);
		ResetMenuSelection(menuState, menuState.vTextGameOverMenuItems);
	}
	
}
