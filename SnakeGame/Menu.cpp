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
		InitRectangleUI(menuState.mainMenuRectangleBackground, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Black, sf::Color::White, 10.f);
		
		InitTextUI(menuState.mainMenuTitle, menuState.font, 72, 1, sf::Color::White,
			"SNAKE");
		
		for (int i = 0; i < menuState.VStringMainMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, menuState.font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				menuState.VStringMainMenuItems[i]);
			menuState.vTextMainMenuItems.push_back(menuItem);
		}
	}
	
	void InitPauseMenu(SMenuState& menuState)
	{
		InitRectangleUI(menuState.pauseMenuRectangleBackground, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
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
		InitRectangleUI(menuState.nameInputMenuRectangleBackground, SCREEN_WIDTH - 20.f, SCREEN_HEIGHT - 20.f,
			sf::Color::Black, sf::Color::White, 10.f);
		InitTextUI(menuState.nameInputMenuText, menuState.font, 40, 1, sf::Color::White,
			"Enter your name: ");
	}

	void InitConfirmationMenu(SMenuState& menuState)
	{
		InitRectangleUI(menuState.confirmationMenuRectangleBackground, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.7f,
			sf::Color::Transparent, sf::Color::White, 10.f);
		InitTextUI(menuState.confirmationMenuText, menuState.font, 50, 1, sf::Color::White,
			"Enter the name");

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
		InitRectangleUI(menuState.gameOverRectangleBackground, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		InitTextUI(menuState.gameOverScoreTitle, menuState.font, 48, 1, sf::Color::White,
			"Number of points");
		InitTextUI(menuState.gameOverScores, menuState.font, 48, 1, sf::Color::White);
		InitTextUI(menuState.gameOverRecordsTitle, menuState.font, 40, 1, sf::Color::White,
			"Records:");
		
		for (int i = 0; i < menuState.VStringGameOverMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, menuState.font, 50, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				menuState.VStringGameOverMenuItems[i]);
			menuState.vTextGameOverMenuItems.push_back(menuItem);
		}
		InitGameOverLeaderboardItems(menuState);
	}

	void InitGameOverLeaderboardItems(SMenuState& menuState)
	{
		menuState.vTextGameOverLeaderboardItems.clear();
		for (int i = 0; i < SIZE_MINI_LEADERBOARD; i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text recordText;
			InitTextUI(recordText, menuState.font, 30, 1, sf::Color::White, std::to_string(i + 1)
				+ ". " + std::to_string(menuState.VLeaderboardItems[i].score));
			menuState.vTextGameOverLeaderboardItems.push_back(recordText);
		}
	}

	void InitDifficultyMenu(SMenuState& menuState)
	{
		InitRectangleUI(menuState.difficultyMenuRectangleBackground, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		InitTextUI(menuState.difficultyMenuTitle, menuState.font, 48, 1, sf::Color::White,
			"Choosing the difficulty");

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
		InitRectangleUI(menuState.leaderboardRectangleBackground, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		
		InitTextUI(menuState.leaderboardTextTitle, menuState.font, 48, 1, sf::Color::White,
			"Scoreboard:");
		InitTextUI(menuState.leaderboardTextInstructions, menuState.font, 24, 1, sf::Color::White,
			"Press B to return to the main menu");
		
		menuState.VLeaderboardItems.clear();
		LoadRecordsFromFile(menuState.VLeaderboardItems, LEADERBOARD_FILENAME);
		menuState.vTextLeaderboardItems.clear();
		for (int i = 0; i < menuState.VLeaderboardItems.size(); ++i)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text recordText;
			InitTextUI(recordText, menuState.font, 38, 1, sf::Color::White, std::to_string(i + 1)
				+ ". " + menuState.VLeaderboardItems[i].playerName + " - "
				+ std::to_string(menuState.VLeaderboardItems[i].score));
			menuState.vTextLeaderboardItems.push_back(recordText);
		}
	}

	void InitOptionsMenu(SMenuState& menuState)
	{
		InitRectangleUI(menuState.optionsMenuRectangleBackground, SCREEN_WIDTH - BORDER_SIZE * 2,
			SCREEN_HEIGHT - BORDER_SIZE * 2, sf::Color::Black, sf::Color::White, 10.f);
		
		InitTextUI(menuState.optionsMenuTitle, menuState.font, 60, 1, sf::Color::White,
			"Options");
		for (int i = 0; i < menuState.VStringOptionsMenuItems.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			sf::Text menuItem;
			InitTextUI(menuItem, menuState.font, 40, 1, (i == 0 ? sf::Color::Green : sf::Color::White),
				menuState.VStringOptionsMenuItems[i]);
			menuState.vTextOptionsMenuItems.push_back(menuItem);
			
			sf::RectangleShape rectangleItem;
			InitRectangleUI(rectangleItem, menuState.vTextOptionsMenuItems[0].getLocalBounds().height,
				menuState.vTextOptionsMenuItems[0].getLocalBounds().height,
				sf::Color::White, sf::Color::White, 5.f);
			menuState.vRectanglesOptionsMenu.push_back(rectangleItem);
		}
	}

	void DrawMainMenu(SMenuState& menuState, sf::RenderWindow& window)
	{		
		menuState.mainMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.mainMenuRectangleBackground);
		
		menuState.mainMenuTitle.setPosition(SCREEN_WIDTH / 2.f, menuState.mainMenuTitle.getLocalBounds().height);
		window.draw(menuState.mainMenuTitle);
		
		DrawMenuItems(window, menuState.vTextMainMenuItems,
			SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 4.f, 60.f);
	}
	
	void DrawPauseMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		window.draw(menuState.pauseBlurSprite);
		
		menuState.pauseMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.pauseMenuRectangleBackground);
			
		menuState.pauseMenuTitle.setPosition(SCREEN_WIDTH / 2.f, menuState.pauseMenuTitle.getLocalBounds().height);
		menuState.pauseMenuTitle.setOrigin(menuState.pauseMenuTitle.getLocalBounds().width / 2.f,
			menuState.pauseMenuTitle.getLocalBounds().height);
		window.draw(menuState.pauseMenuTitle);

		DrawMenuItems(window, menuState.vTextPauseMenuItems,
			SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 4.f, 60.f);
	}

	void DrawNameInputMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		menuState.nameInputMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.nameInputMenuRectangleBackground);

		menuState.nameInputMenuText.setOrigin(menuState.nameInputMenuText.getLocalBounds().width / 2.f,
			menuState.nameInputMenuText.getLocalBounds().height / 2.f);
		menuState.nameInputMenuText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.5f);
		window.draw(menuState.nameInputMenuText);
	}

	void DrawConfirmationMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		menuState.mainMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.mainMenuRectangleBackground);
		
		window.draw(menuState.pauseBlurSprite);

		menuState.confirmationMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.confirmationMenuRectangleBackground);
		
		menuState.confirmationMenuText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.5f);
		window.draw(menuState.confirmationMenuText);

		DrawMenuItems(window, menuState.vTextConfirmationMenuItems,
			SCREEN_WIDTH / 2.f, menuState.confirmationMenuText.getLocalBounds().width, 40.f);
	}
	
	void DrawGameOverMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		InitGameOverLeaderboardItems(menuState);
		
		menuState.gameOverRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.gameOverRectangleBackground);

		menuState.gameOverScoreTitle.setPosition(SCREEN_WIDTH / 2.f,
			menuState.gameOverScoreTitle.getLocalBounds().height);
		window.draw(menuState.gameOverScoreTitle);

		menuState.gameOverScores.setPosition(SCREEN_WIDTH / 2.f,
			menuState.gameOverScoreTitle.getPosition().y + menuState.gameOverScoreTitle.getLocalBounds().height);
		menuState.gameOverScores.setOrigin(menuState.gameOverScores.getLocalBounds().width / 2.f,
		menuState.gameOverScores.getLocalBounds().height / 2.f);
		window.draw(menuState.gameOverScores);
		
		menuState.gameOverRecordsTitle.setPosition(SCREEN_WIDTH / 2.f,
			menuState.gameOverScores.getPosition().y + menuState.gameOverScores.getLocalBounds().height + 100.f);
		window.draw(menuState.gameOverRecordsTitle);
		
		DrawMenuItems(window, menuState.vTextGameOverLeaderboardItems, SCREEN_WIDTH / 2.f,
			menuState.gameOverRecordsTitle.getPosition().y + menuState.gameOverRecordsTitle.getLocalBounds().height,
			35.f);
		
		DrawMenuItems(window, menuState.vTextGameOverMenuItems,
			SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 100.f * menuState.vTextGameOverMenuItems.size(), 60.f);
	}
	
	void DrawDifficultyMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		menuState.difficultyMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.difficultyMenuRectangleBackground);

		menuState.difficultyMenuTitle.setPosition(SCREEN_WIDTH / 2.f,
			menuState.difficultyMenuTitle.getLocalBounds().height);
		menuState.difficultyMenuTitle.setOrigin(menuState.difficultyMenuTitle.getLocalBounds().width / 2.f,
			menuState.difficultyMenuTitle.getLocalBounds().height / 2.f);
		window.draw(menuState.difficultyMenuTitle);

		DrawMenuItems(window, menuState.vTextDifficultyMenuItems,
			SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 4.f, 60.f);
	}
	
	void DrawLeaderboard(SMenuState& menuState, sf::RenderWindow& window)
	{
		InitLeaderboard(menuState);
		
		// Draw
		menuState.leaderboardRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.leaderboardRectangleBackground);
		
		menuState.leaderboardTextTitle.setPosition(SCREEN_WIDTH / 2.f, 40.f);
		window.draw(menuState.leaderboardTextTitle);
			
		menuState.leaderboardTextInstructions.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 50.f);
		window.draw(menuState.leaderboardTextInstructions);

		DrawMenuItems(window, menuState.vTextLeaderboardItems,
			SCREEN_WIDTH / 2.f, 90.f, 40.f);
	}
	

	void DrawOptionsMenu(SMenuState& menuState, sf::RenderWindow& window)
	{
		menuState.optionsMenuRectangleBackground.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		window.draw(menuState.optionsMenuRectangleBackground);
		
		menuState.optionsMenuTitle.setPosition(SCREEN_WIDTH / 2.f, 40.f);
		window.draw(menuState.optionsMenuTitle);

		DrawMenuItems(window, menuState.vTextOptionsMenuItems, SCREEN_WIDTH / 2.f - 50.f,
			SCREEN_HEIGHT / 4.f, 60.f);
		
		for (int i = 0; i < menuState.vRectanglesOptionsMenu.size(); i++)  // NOLINT(clang-diagnostic-sign-compare)
		{
			menuState.vRectanglesOptionsMenu[i].setOrigin
			(menuState.vRectanglesOptionsMenu[i].getLocalBounds().width,
			 menuState.vRectanglesOptionsMenu[i].getLocalBounds().height / 2.f);
			
			menuState.vRectanglesOptionsMenu[i].setPosition( SCREEN_WIDTH / 1.5f,
				menuState.vTextOptionsMenuItems[i].getPosition().y
				+ menuState.vTextOptionsMenuItems[i].getLocalBounds().height / 2.f);

			window.draw(menuState.vRectanglesOptionsMenu[i]);
		}
	}
	
	void DrawMenuItems(sf::RenderWindow& window, std::vector<sf::Text>& menuItems,
		float posX, float posY, float indentation)
	{
		float verticalIndentation = 0.f;
		for (auto& menuItem : menuItems) // NOLINT(clang-diagnostic-sign-compare)
		{
			menuItem.setPosition(posX, posY + verticalIndentation);
			window.draw(menuItem);
			verticalIndentation += indentation;
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
		ResetMenuSelection(menuState, menuState.vTextOptionsMenuItems);
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
		// We check, if the table has less than 10 records, then the current record will always be new
		if (leaderboard.size() < 10)
		{
			return true;
		}
    
		// If the current account is greater than the lowest record (the latter in the list)
		if (currentScore > leaderboard.back().score)
		{
			return true;
		}

		return false;
	}

	void SetFillColorRectangle(SMenuState& menuState, int selectedIndex, bool option)
	{
		if (option)
		{
			menuState.vRectanglesOptionsMenu[selectedIndex].setFillColor(sf::Color::White);
		}
		else
		{
			menuState.vRectanglesOptionsMenu[selectedIndex].setFillColor(sf::Color::Transparent);
		}
	}
	
}
