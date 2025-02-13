// ReSharper disable CppClangTidyClangDiagnosticCoveredSwitchDefault
#include "Game.h"
#include <cassert>
#include <random>

namespace SnakeGame
{
	void InitGame(SGame& game, sf::RenderWindow& window)
	{
		InitUI(game.uiState, game.uiState.menuState.font);
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
		game.uiState.menuState.backgroundScoreboard.setTexture(game.uiState.menuState.scoreboardTexture);
		SetSpriteSize(game.uiState.menuState.backgroundScoreboard, SCREEN_WIDTH, SCREEN_HEIGHT);
		
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
		case GameState::GameOver:
			UpdateMenuState(game, event, window, game.uiState.menuState.vTextGameOverMenuItems);
			break;
		case GameState::MainMenu:
			UpdateMenuState(game, event, window, game.uiState.menuState.vTextMainMenuItems);
			break;
		case GameState::PauseMenu:
			UpdateMenuState(game, event, window, game.uiState.menuState.vTextPauseMenuItems);
			break;
		case GameState::Scoreboard:
			UpdateScoreboardState(game, event);
			break;
		case GameState::Difficulty:  // NOLINT(bugprone-branch-clone)
			// UpdateMenuState(game, event, window, game.uiState.menuState.vTextDifficultyMenuItems);
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
				if (GetCurrentGameState(game) == GameState::MainMenu)
				{
					HandleMainMenuSelection(game.uiState.menuState.selectedItemIndex, game, window);
				}
				if (GetCurrentGameState(game) == GameState::PauseMenu)
				{
					HandlePauseMenuSelection(game.uiState.menuState.selectedItemIndex, game);
				}
				if (GetCurrentGameState(game) == GameState::GameOver)
				{
					HandleGameOverMenuSelection(game.uiState.menuState.selectedItemIndex, game);
				}
				if (GetCurrentGameState(game) == GameState::Difficulty)
				{
					// Difficulty
				}
				if (GetCurrentGameState(game) == GameState::Options)
				{
					// Options
				}
			}
			game.onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && (GetCurrentGameState(game) != GameState::MainMenu))
		{
			SwitchGameState(game, GetPreviousGameState(game));
			game.uiState.musicMainTheme.play();
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			game.onKeyHold = false;
		}
	}

	void UpdateScoreboardState(SGame& game, const sf::Event& event)
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
			ResetMenuSelection(game.uiState.menuState, game.uiState.menuState.vTextMainMenuItems);
			break;
		case 1:  // Difficulty
			///
				break;
		case 2:  // Scoreboard
			PushGameState(game, GameState::Scoreboard);
			ResetMenuSelection(game.uiState.menuState, game.uiState.menuState.vTextMainMenuItems);
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
			ResetMenuSelection(game.uiState.menuState, game.uiState.menuState.vTextPauseMenuItems);
			game.uiState.musicMainTheme.play();
			break;
		default:  // Back to main menu
			PushGameState(game, GameState::MainMenu);
			ResetMenuSelection(game.uiState.menuState, game.uiState.menuState.vTextPauseMenuItems);
			break;
		}
	}

	void HandleGameOverMenuSelection(unsigned int selectedIndex, SGame& game)
	{
		switch (selectedIndex)  // NOLINT(hicpp-multiway-paths-covered)
		{
		case 0:  // New Game
			InitStartNewGame(game);
			ResetMenuSelection(game.uiState.menuState, game.uiState.menuState.vTextGameOverMenuItems);
			break;
		default:  // Back to main menu
			PushGameState(game, GameState::MainMenu);
			ResetMenuSelection(game.uiState.menuState, game.uiState.menuState.vTextGameOverMenuItems);
			break;
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
					game.uiState.noneSprite.setPosition(i * CELL_SIZE + BORDER_SIZE, j * CELL_SIZE + SCOREBOARD_HEIGHT + BORDER_SIZE);
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

		if (GetCurrentGameState(game) == GameState::Scoreboard)
		{
			window.draw(game.uiState.menuState.backgroundLast);
		}

		// Draw UI
		DrawUI(game.uiState, window);
	}


	void PushGameState(SGame& game, GameState state)
	{
		game.gameStateStack.push_back(state);
	}

	void PopGameState(SGame& game)
	{
		if (!game.gameStateStack.empty())
		{
			game.gameStateStack.pop_back();
		}
		else
		{
			game.gameStateStack.push_back(GameState::MainMenu);
		}
	}

	void SwitchGameState(SGame& game, GameState newState)
	{
		if (!game.gameStateStack.empty())
		{
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

