#include "Game.h"
#include <cassert>
#include <random>

namespace SnakeGame
{
	void InitGame(SGame& game, sf::RenderWindow& window)
	{
		InitUI(game.uiState, game.uiState.menuState.font);
		SwitchGameState(game, GameState::MainMenu);
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
		
		// game.uiState.backgroundGameZone.setTexture(game.uiState.grassTexture);
		// SetSpriteSize(game.uiState.backgroundGameZone, SCREEN_WIDTH, SCREEN_HEIGHT);
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
			game.isPlayMusic = true;
		}
	}

	void InitField (SGame& game)
	{
		// Очистка игрового поля
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				game.field[i][j] = FIELD_CELL_TYPE_NONE;
			}
		}

		AddSnake(game);
		AddWall(game);
		AddApple(game);
	}

	void InitStartNewGame(SGame& game)
	{
		SwitchGameState(game, GameState::Playing);
		InitGameState(game);
		InitField(game);
	}

	int GetRandomEmptyCell(const SGame& game)
	{
		int emptyCellCount = 0;
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (game.field[i][j] == FIELD_CELL_TYPE_NONE)
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
	
	void UpdateMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (!game.onKeyHold)
			{
				moveUp(game.uiState.menuState);
			}
			game.onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (!game.onKeyHold)
			{
				moveDown(game.uiState.menuState);
			}
			game.onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			int selectedIndex = getSelectedItemIndex(game.uiState.menuState);
			if (GetCurrentGameState(game) == GameState::MainMenu)
			{
				HandleMainMenuSelection(selectedIndex, game, window);
			}
			if (GetCurrentGameState(game) == GameState::Difficulty)
			{
				////
			}
			if (GetCurrentGameState(game) == GameState::Options)
			{
				////
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			game.onKeyHold = false;
		}
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		// {
		// 	if (!game.onKeyHold1)
		// 	{
		// 		ToggleGameMode(game, MASK_INFINIT_FOODS);
		// 		GetButtonText(game, MASK_INFINIT_FOODS);
		// 	}
		// 	game.onKeyHold1 = true;
		// }		
	}

	void HandleMainMenuSelection(int selectedIndex, SGame& game, sf::RenderWindow& window)
	{
		switch (selectedIndex)
		{
		case 0:  // Start Game
			InitStartNewGame(game);
			break;
		case 1:  // Difficulty
			///
				break;
		case 2:  // Scoreboard
			SwitchGameState(game, GameState::Scoreboard);
			break;
		case 3:  // Options
			///
				break;
		case 4: // Exit
			window.close();
			break;
		default:
			break;
		}
	}

	void UpdateQuitMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			SwitchGameState(game,GameState::MainMenu);
			game.onKeyHold = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			InitStartNewGame(game);
			game.onKeyHold = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			game.onKeyHold = false;
			window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!game.onKeyHold)
			{
				game.gameStateStack.pop_back();
				game.onKeyHold = false;
				if (game.isPlayMusic)
				{
					game.uiState.musicMainTheme.play();
				}
			}
			game.onKeyHold = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			game.onKeyHold = false;
		}
	}

	void UpdateGameOverState(SGame& game, sf::RenderWindow& window, float deltaTime)
	{
		game.timeSinceGameOver += deltaTime; // Надо выяснить где считается deltaTime
		game.uiState.musicMainTheme.stop();
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			InitStartNewGame(game);
		}
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			SwitchGameState(game, GameState::MainMenu);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}

	void UpdatePlayingState(const sf::Event& event, SGame& game, float currentTime)
	{
		HandleInput(game.snake);
		MoveSnake(game, currentTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!game.onKeyHold)
			{
				game.gameStateStack.push_back(GameState::QuitMenu);
				game.uiState.musicMainTheme.pause();
				game.onKeyHold = true;
			}
			game.onKeyHold = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			game.onKeyHold = false;
		}
	}

	void UpdateScoreboardState(SGame& game, sf::Event& event)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!game.onKeyHold)
			{
				SwitchGameState(game,GameState::MainMenu);
			}
			game.onKeyHold = true;
		}

		else if (event.type == sf::Event::KeyReleased)
		{
			game.onKeyHold = false;
		}
	}

	void UpdateGame(SGame& game, float currentTime, sf::RenderWindow& window, sf::Event event)
	{
		GameState gameState = game.gameStateStack.back();
		
		switch (gameState)
		{
		case SnakeGame::GameState::Playing:
			UpdatePlayingState(event, game, currentTime);
			break;
		case SnakeGame::GameState::GameOver:
			UpdateGameOverState(game, window, currentTime);
			break;
		case SnakeGame::GameState::Winner:
			UpdateGameOverState(game, window, currentTime);
			break;
		case SnakeGame::GameState::MainMenu:
			UpdateMenuState(event, window, game);
			break;
		case SnakeGame::GameState::QuitMenu:
			UpdateQuitMenuState(event, window, game);
			break;
		case SnakeGame::GameState::Scoreboard:
			UpdateScoreboardState(game, event);
			break;
		case SnakeGame::GameState::Difficulty:
			UpdateMenuState(event, window, game);
			break;
		case SnakeGame::GameState::Options:
			UpdateMenuState(event, window, game);
			break;
		default:
			break;
		}

		UpdateUI(game.uiState, game);
	}

	void PushGameState(SGame& game, GameState state)
	{
		GameState oldState = GameState::None;
		if (game.gameStateStack.size() > 0)
		{
			oldState = game.gameStateStack.back();
		}
		
		game.gameStateStack.push_back(state);
	}

	void PopGameState(SGame& game)
	{
		GameState oldState = GameState::None;
		if (game.gameStateStack.size() > 0)
		{
			oldState = game.gameStateStack.back();
		}

		game.gameStateStack.pop_back();
		GameState state = GameState::None;
		if (game.gameStateStack.size() > 0)
		{
			state = game.gameStateStack.back();
		}
	}

	void SwitchGameState(SGame& game, GameState newState)
	{
		if (game.gameStateStack.size() > 0)
		{
			GameState oldState = game.gameStateStack.back();
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
		if (game.gameStateStack.size() > 0)
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

	void ToggleGameMode(SGame& game, const int modeSelection)
	{
		game.gameMode ^= modeSelection;
	}

	std::string GetButtonText(const SGame& game, const int modeSelection)
	{
		if (game.gameMode & modeSelection)
		{
			return "On";
		}

		return "Off";
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
					game.uiState.noneSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE + SCOREBAR_HEIGHT);
					window.draw(game.uiState.noneSprite);
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
		DrawUI(game.uiState, game, window);
	}
}

