// ReSharper disable CppClangTidyClangDiagnosticCoveredSwitchDefault
#include "Game.h"
#include <cassert>
#include <iostream>
#include <random>

namespace SnakeGame
{
	void InitGame(SGame& game, sf::RenderWindow& window)
	{
		InitUI(game.uiState);
		PushGameState(game, GameState::MainMenu);
		InitGameState(game);
		InitField(game);
		window.setIcon(32, 32, game.uiState.icon.getPixelsPtr());
	}

	void InitGameState(SGame& game)
	{
		// Set default values
		game.numEatenApples = 0;
		game.uiState.menuState.numScores = 0;
		game.timeSinceGameOver = 0.f;

		// Init Player
		InitSnake(game.snake, game);
		
		// Init Walls
		if (!game.wallsVec.empty())
		{
			game.wallsVec.clear();
		}
		
		SWall wall;
		InitWall(wall, game);
		game.wallsVec.emplace_back(wall);
		
		// Init Apples
		if (!game.applesVec.empty())
		{
			game.applesVec.clear();
		}
		
		SApple apple;
		InitApple(apple, game);
		game.applesVec.emplace_back(apple);
		
		game.uiState.menuState.backgroundMenu.setTexture(game.uiState.menuState.mainMenuTexture);
		SetSpriteSize(game.uiState.menuState.backgroundMenu, SCREEN_WIDTH, SCREEN_HEIGHT);
		game.uiState.menuState.leaderboardBackground.setTexture(game.uiState.menuState.leaderboardTexture);
		SetSpriteSize(game.uiState.menuState.leaderboardBackground, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		if (GetCurrentGameState(game) == GameState::Playing)
		{
			game.uiState.musicMainTheme.setVolume(20);
			game.uiState.musicMainTheme.setPlayingOffset(sf::seconds(0.f));
			game.uiState.musicMainTheme.play();
			game.uiState.musicMainTheme.setLoop(true);
		}
	}

	void InitField (SGame& game)
	{
		// Очистка игрового поля
		for (auto& i : game.field)
		{
			for (int& j : i)
			{
				j = FIELD_CELL_TYPE_NONE;
			}
		}

		AddSnake(game);
		AddWall(game);
		AddApple(game);
	}

	void InitStartNewGame(SGame& game)
	{
		PushGameState(game, GameState::Playing);
		InitGameState(game);
		InitField(game);
	}
	
	void UpdateGame(SGame& game, float currentTime, sf::RenderWindow& window, const sf::Event& event)
	{
		switch (GetCurrentGameState(game))
		{
		case GameState::Playing:
			UpdatePlayingState(event, game, currentTime);
			break;
		case GameState::NameInputMenu:
			UpdateNameInputMenuState(game, event);
			break;
		case GameState::ConfirmationMenu:
			UpdateMenuState(game, event, window, game.uiState.menuState.vTextConfirmationMenuItems);
			break;
		case GameState::GameOver:
			UpdateMenuState(game, event, window, game.uiState.menuState.vTextGameOverMenuItems);
			break;
		case GameState::MainMenu:
			UpdateMenuState(game, event, window, game.uiState.menuState.vTextMainMenuItems);
			break;
		case GameState::PauseMenu:
			UpdateMenuState(game, event, window, game.uiState.menuState.vTextPauseMenuItems);
			break;
		case GameState::Leaderboard:
			UpdateLeaderboardState(game, event);
			break;
		case GameState::Difficulty:
			UpdateMenuState(game, event, window, game.uiState.menuState.vTextDifficultyMenuItems);
			break;
		case GameState::Options:
			// UpdateMenuState(game, event, window, game.uiState.menuState.vTextOptionMenuItems);
			break;
		case GameState::None:
				break;
		default:
			break;
		}

		UpdateUI(game.uiState, game);
	}

	void UpdatePlayingState(const sf::Event& event, SGame& game, float currentTime)
	{
		HandleInput(game.snake);
		MoveSnake(game, currentTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			if (!game.onKeyHold)
			{
				PushGameState(game, GameState::PauseMenu);
				game.onKeyHold = true;
			}
			game.onKeyHold = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			game.onKeyHold = false;
		}
	}

	void UpdateNameInputMenuState(SGame& game, const sf::Event& event)
	{
		if (event.type == sf::Event::TextEntered && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!game.onKeyHold)
			{
				if (event.text.unicode == '' && !game.uiState.menuState.nameInputPlayerName.empty()) 
				{
					game.uiState.menuState.nameInputPlayerName.pop_back();
					game.onKeyHold = true;
				}
				else if (event.text.unicode < 128 && event.text.unicode != 32 && event.text.unicode != '') // Only ASCII-symbols without Space and Backspace
				{
					game.uiState.menuState.nameInputPlayerName += static_cast<char>(event.text.unicode);
					game.onKeyHold = true;
				}
			}				
			game.uiState.menuState.nameInputMenuText.setString("Enter your name: " + game.uiState.menuState.nameInputPlayerName);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!game.onKeyHold)
			{
				if (game.uiState.menuState.nameInputPlayerName.empty())
				{
					game.uiState.menuState.nameInputPlayerName = "XYZ";
				}
				AddRecord(game.uiState.menuState, game.uiState.menuState.nameInputPlayerName, game.uiState.menuState.numScores);
				PushGameState(game, GameState::GameOver);
				game.onKeyHold = true;
			}
		}
		
		if (event.type == sf::Event::KeyReleased)
		{
			game.onKeyHold = false;
		}
	}
	
	void UpdateMenuState(SGame& game, const sf::Event& event, sf::RenderWindow& window, std::vector<sf::Text>& menuItems)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (!game.onKeyHold)
			{
				MoveUp(game.uiState.menuState, menuItems);
			}
			game.onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (!game.onKeyHold)
			{
				MoveDown(game.uiState.menuState, menuItems);
			}
			game.onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!game.onKeyHold)
			{
				switch (GetCurrentGameState(game))  // NOLINT(clang-diagnostic-switch-enum)
				{
				case GameState::MainMenu:
					HandleMainMenuSelection(game.uiState.menuState.selectedItemIndex, game, window);
					break;
				case GameState::PauseMenu:
					HandlePauseMenuSelection(game.uiState.menuState.selectedItemIndex, game);
					break;
				case GameState::ConfirmationMenu:
					HandleConfirmationSelection(game.uiState.menuState.selectedItemIndex, game);
					break;
				case GameState::GameOver:
					HandleGameOverMenuSelection(game.uiState.menuState.selectedItemIndex, game);
					break;
				case GameState::Difficulty:
					HandleDifficultyMenuSelection(game.uiState.menuState.selectedItemIndex, game);
					break;
				case GameState::Options:
					// Options
						break;
				default:
					break;
				}
				game.onKeyHold = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && GetCurrentGameState(game) != GameState::MainMenu)
		{
			if (!game.onKeyHold)
			{
				SwitchGameState(game, GetPreviousGameState(game));
			}
			game.onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && GetCurrentGameState(game) == GameState::MainMenu)
		{
			if (!game.onKeyHold)
			{
				window.close();
			}
			game.onKeyHold = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			game.onKeyHold = false;
		}
	}

	void UpdateLeaderboardState(SGame& game, const sf::Event& event)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			if (!game.onKeyHold)
			{
				SwitchGameState(game,GetPreviousGameState(game));
			}
			game.onKeyHold = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			game.onKeyHold = false;
		}
	}
	
	void HandleMainMenuSelection(unsigned int selectedIndex, SGame& game, sf::RenderWindow& window)
	{
		switch (selectedIndex)
		{
		case 0:  // Start Game
			InitStartNewGame(game);
			break;
		case 1:  // Difficulty
			ResetAllMenuSelection(game.uiState.menuState);
			PushGameState(game, GameState::Difficulty);
			break;
		case 2:  // Leaderboard
			PushGameState(game, GameState::Leaderboard);
			break;
		case 3:  // Options
			///
				break;
		default: // Exit
			window.close();
			break;
		}
	}

	void HandlePauseMenuSelection(unsigned int selectedIndex, SGame& game)
	{
		switch (selectedIndex)  // NOLINT(hicpp-multiway-paths-covered)
		{
		case 0:  // Continue Game
			SwitchGameState(game, GameState::Playing);
			game.uiState.musicMainTheme.play();
			break;
		default:  // Back to main menu
			ResetAllMenuSelection(game.uiState.menuState);
			PushGameState(game, GameState::MainMenu);
			break;
		}
	}

	void HandleConfirmationSelection(unsigned int selectedIndex, SGame& game)
	{
		switch (selectedIndex)  // NOLINT(hicpp-multiway-paths-covered)
		{
		case 0:  // No
			PushGameState(game, GameState::GameOver);
			break;
		default: // Yes
			PushGameState(game, GameState::NameInputMenu);
			break;
		}
	}

	void HandleGameOverMenuSelection(unsigned int selectedIndex, SGame& game)
	{
		switch (selectedIndex)  // NOLINT(hicpp-multiway-paths-covered)
		{
		case 0:  // New Game
			InitStartNewGame(game);
			break;
		default:  // Back to main menu
			ResetAllMenuSelection(game.uiState.menuState);
			PushGameState(game, GameState::MainMenu);
			break;
		}
	}

	void HandleDifficultyMenuSelection(unsigned int selectedIndex, SGame& game)
	{
		// ReSharper disable once CppUnsignedZeroComparison
		if (selectedIndex >= 0 && selectedIndex < game.uiState.menuState.VStringDifficultyMenuItems.size())
		{
			game.snake.movementInterval = game.uiState.menuState.VStringDifficultyMenuItems[selectedIndex].snakeSpeed;
			game.scoresPerApple = game.uiState.menuState.VStringDifficultyMenuItems[selectedIndex].scoresPerApple;
			game.difficultySelected = true;

			SwitchGameState(game, GameState::MainMenu);
		}
	}

	void DrawGame(SGame& game, sf::RenderWindow& window)
	{		
		// Draw Background
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				switch (game.field[i][j])
				{
				case FIELD_CELL_TYPE_NONE:
					game.uiState.noneSprite.setPosition(i * CELL_SIZE + BORDER_SIZE, j * CELL_SIZE + LEADERBOARD_HEIGHT + BORDER_SIZE);
					window.draw(game.uiState.noneSprite);
					break;
				default:
					break;
				}
			}
		}
		
		// Draw Player
		DrawSnake(game.snake, game, window);

		// Draw Food
		for (SApple& apple : game.applesVec)
		{
			DrawApple(apple, game, window);
		}
		
		// Draw Barrier
		for (SWall& wall : game.wallsVec)
		{
			DrawWall(wall, game, window);
		}

		if (GetCurrentGameState(game) == GameState::Leaderboard)
		{
			window.draw(game.uiState.menuState.backgroundLast);
		}

		// Draw UI
		DrawUI(game.uiState, window);
	}


	void PushGameState(SGame& game, GameState state)
	{
		ResetAllMenuSelection(game.uiState.menuState);
		game.gameStateStack.push_back(state);
	}

	void PopGameState(SGame& game)
	{
		if (!game.gameStateStack.empty())
		{
			ResetAllMenuSelection(game.uiState.menuState);
			game.gameStateStack.pop_back();
		}
		else
		{
			ResetAllMenuSelection(game.uiState.menuState);
			game.gameStateStack.push_back(GameState::MainMenu);
		}
	}

	void SwitchGameState(SGame& game, GameState newState)
	{
		if (!game.gameStateStack.empty())
		{
			ResetAllMenuSelection(game.uiState.menuState);
			game.gameStateStack.pop_back();
			game.gameStateStack.push_back(newState);
		}
		else
		{
			PushGameState(game, newState);
		}
	}

	GameState GetCurrentGameState(const SGame& game)
	{
		if (!game.gameStateStack.empty())
		{
			return game.gameStateStack.back();
		}
		else
		{
			return GameState::None;
		}
	}

	GameState GetPreviousGameState(const SGame& game)
	{
		if (game.gameStateStack.size() > 1)
		{
			return game.gameStateStack.end()[-2];
		}
		else
		{
			return GameState::None;
		}
	}
	
	int GetRandomEmptyCell(const SGame& game)
	{
		int emptyCellCount = 0;
		for (const auto& i : game.field)
		{
			for (int j : i)
			{
				if (j == FIELD_CELL_TYPE_NONE)
				{
					emptyCellCount++;
				}
			}
		}
		int targetEmptyCellIndex = rand() % emptyCellCount;
		int emptyCellIndex = 0;
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (game.field[i][j] == FIELD_CELL_TYPE_NONE)
				{
					if (emptyCellIndex == targetEmptyCellIndex)
					{
						return  i * FIELD_SIZE_X + j;
					}
					emptyCellIndex++;
				}
			}
		}
		return -1;
	}

	std::string GetButtonText(const SGame& game, const int modeSelection)
	{
		if (game.gameMode & modeSelection)
		{
			return "On";
		}

		return "Off";
	}

	void ToggleGameMode(SGame& game, const int modeSelection)
	{
		game.gameMode ^= modeSelection;
	}
}

