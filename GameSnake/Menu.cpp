#include <string>
#include "Menu.h"
#include <fstream>
#include <iostream>
#include "Game.h"
#include "UI.h"

namespace SnakeGame
{
	void InitPauseTexture(SMenuState& menuState)
	{
		menuState.pauseBlurTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
		menuState.pauseBlurTexture.clear(sf::Color(0, 0, 0, 220));
		menuState.pauseBlurSprite.setTexture(menuState.pauseBlurTexture.getTexture());
	}
	
	void InitMainMenu(SMenuState& menuState)
	{
		InitRectangleUI(menuState.mainMenuRectangle, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Transparent, sf::Color::White, 10.f);
		
		InitTextUI(menuState.mainMenuTitle, menuState.font, 72, 1, sf::Color::White, "SNAKE");
		
		for (int i = 0; i < menuState.VStringMainMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, menuState.font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White), menuState.VStringMainMenuItems[i]);
			menuState.vTextMainMenuItems.push_back(menuItem);
		}
	}
	
	void InitPauseMenu(SMenuState& menuState)
	{
		InitRectangleUI(menuState.pauseMenuRectangle, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Transparent, sf::Color::White, 10.f);
		InitTextUI(menuState.pauseMenuTitle, menuState.font, 64, 1, sf::Color::White, "Pause menu");
		
		for (int i = 0; i < menuState.VStringPauseMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, menuState.font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				menuState.VStringPauseMenuItems[i]);
			menuState.vTextPauseMenuItems.push_back(menuItem);
		}
	}

	void InitNameInputMenu(SMenuState& menuState)
	{
		InitRectangleUI(menuState.nameInputMenuRectangle, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Black, sf::Color::White, 10.f);
		InitTextUI(menuState.nameInputMenuText, menuState.font, 40, 1, sf::Color::White, "Enter your name: ");
	}

	void InitConfirmationMenu(SMenuState& menuState)
	{
		InitRectangleUI(menuState.confirmationMenuRectangle, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.7f,
			sf::Color::Transparent, sf::Color::White, 10.f);
		InitTextUI(menuState.confirmationMenuText, menuState.font, 50, 1, sf::Color::White, "Enter the name");

		for (int i = 0; i < menuState.VStringConfirmationMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, menuState.font, 40, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				menuState.VStringConfirmationMenuItems[i]);
			menuState.vTextConfirmationMenuItems.push_back(menuItem);
		}
	}

	void InitGameOverMenu(SMenuState& menuState)
	{
		InitRectangleUI(menuState.gameOverRectangle, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		InitTextUI(menuState.gameOverScoreText, menuState.font, 48, 1, sf::Color::White);

		for (int i = 0; i < menuState.VStringGameOverMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, menuState.font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				menuState.VStringGameOverMenuItems[i]);
			menuState.vTextGameOverMenuItems.push_back(menuItem);
		}
	}

	void InitDifficultyMenu(SMenuState& menuState)
	{
		InitRectangleUI(menuState.difficultyMenuRectangle, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		InitTextUI(menuState.difficultyMenuTitle, menuState.font, 48, 1, sf::Color::White, "Choosing the difficulty");

		for (int i = 0; i < menuState.VStringDifficultyMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, menuState.font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				menuState.VStringDifficultyMenuItems[i].nameDifficulty);
			menuState.vTextDifficultyMenuItems.push_back(menuItem);
		}
	}
	
	void InitLeaderboard(SMenuState& menuState)
	{
		InitTextUI(menuState.leaderboardTextTitle, menuState.font, 48, 1, sf::Color::White, "Scoreboard:");
		InitTextUI(menuState.leaderboardTextInstructions, menuState.font, 24, 1, sf::Color::White, "Press B to return to the main menu");
		
		menuState.VLeaderboardItems.clear();
		LoadRecordsFromFile(menuState.VLeaderboardItems, LEADERBOARD_FILENAME);
		menuState.vTextLeaderboardItems.clear();
		for (int i = 0; i < menuState.VLeaderboardItems.size(); ++i)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text recordText;
			InitTextUI(recordText, menuState.font, 38, 1, sf::Color::White, std::to_string(i + 1)
				+ ". " + menuState.VLeaderboardItems[i].playerName + " - " + std::to_string(menuState.VLeaderboardItems[i].score));
			menuState.vTextLeaderboardItems.push_back(recordText);
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

	void DrawNameInputMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		menuState.nameInputMenuRectangle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.nameInputMenuRectangle);

		menuState.nameInputMenuText.setOrigin(menuState.nameInputMenuText.getLocalBounds().width / 2.f, menuState.nameInputMenuText.getLocalBounds().height / 2.f);
		menuState.nameInputMenuText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.5f);
		window.draw(menuState.nameInputMenuText);
	}

	void DrawConfirmationMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		menuState.mainMenuRectangle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.mainMenuRectangle);
		
		window.draw(menuState.pauseBlurSprite);

		menuState.confirmationMenuRectangle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.confirmationMenuRectangle);
		
		menuState.confirmationMenuText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.5f);
		window.draw(menuState.confirmationMenuText);

		float verticalIndentation = 50.f;
		for (auto& vTextConfirmationMenuItem : menuState.vTextConfirmationMenuItems)
		{
			vTextConfirmationMenuItem.setPosition(SCREEN_WIDTH / 2.f, menuState.confirmationMenuText.getPosition().y + verticalIndentation);
			window.draw(vTextConfirmationMenuItem);
			verticalIndentation += 40.f;
		}
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
		InitLeaderboard(menuState);
		// Blur screen
		window.draw(menuState.pauseBlurSprite);
		menuState.backgroundLast = menuState.leaderboardBackground;
			
		// Draw
		menuState.leaderboardTextTitle.setPosition(SCREEN_WIDTH / 2.f, 40.f);
		window.draw(menuState.leaderboardTextTitle);
			
		menuState.leaderboardTextInstructions.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 50.f);
		window.draw(menuState.leaderboardTextInstructions);
			
		float verticalIndentation = 0.f;
		for (int i = 0; i < SIZE_LEADERBOARD; ++i)
		{
			menuState.vTextLeaderboardItems[i].setPosition(SCREEN_WIDTH / 2.f, 90.f + verticalIndentation);
			window.draw(menuState.vTextLeaderboardItems[i]);
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

	void AddRecord(SMenuState& menuState, const std::string& playerName, int score)
	{
		// Add a new record
		menuState.VLeaderboardItems.push_back({playerName, score});
		
		// Sort vector Score Table
		std::ranges::stable_sort
		(menuState.VLeaderboardItems, [](const SLeaderboard& a, const SLeaderboard& b)
			{
				return a.score > b.score;
			}
		);
		
		// Leave only the top 10
		if (menuState.VLeaderboardItems.size() > 10)
		{
			menuState.VLeaderboardItems.pop_back();
		}

		SaveRecordsToFile(menuState.VLeaderboardItems, LEADERBOARD_FILENAME);
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

	void SaveRecordsToFile(const std::vector<SLeaderboard>& leaderboard, const std::string& filename)
	{
		std::ofstream file(filename, std::ios::out | std::ios::trunc);
		if (file.is_open())
		{
			for (const auto& record : leaderboard)
			{
				file << record.playerName << " " << record.score << "\n";
			}
			file.close();
		}
		else
		{
			std::cerr << "Error: failed to open a record file!\n";
		}
	}

	void LoadRecordsFromFile(std::vector<SLeaderboard>& leaderboard, const std::string& filename)
	{
		std::ifstream file(filename);

		// Clean the current list before loading
		leaderboard.clear();
    
		// Check if there is a file
		if (!file)
		{
			std::ofstream createFile(filename); // Create an empty file
			if (!createFile)
			{
				std::cerr << "Error: it was not possible to create a record file!\n";
			}
			return; // The file was empty, there are no records
		}

		std::string name;
		int score;
		while (file >> name >> score)
		{
			leaderboard.push_back(SLeaderboard{name, score});
		}
		file.close();
	}

	bool IsNewRecord(const std::vector<SLeaderboard>& leaderboard, int currentScore)
	{
		// Проверяем, если в таблице меньше 10 рекордов, то текущий рекорд всегда будет новым
		if (leaderboard.size() < 10)
		{
			return true;
		}
    
		// Если текущий счёт больше, чем самый низкий рекорд (последний в списке)
		if (currentScore > leaderboard.back().score)
		{
			return true;
		}

		return false;
	}
	
}
