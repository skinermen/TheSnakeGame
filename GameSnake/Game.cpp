#include "Game.h"
#include <cassert>
#include <random>

namespace SnakeGame
{
	void InitGame(SGame& game, sf::RenderWindow& window)
	{
		assert(game.snakeTextureHead.loadFromFile(RESOURCES_PATH + "\\snake.png"));
		assert(game.snakeTextureBody.loadFromFile(RESOURCES_PATH + "\\Snake_Body.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.wallTexture.loadFromFile(RESOURCES_PATH + "\\wall.png"));
		assert(game.noneTexture.loadFromFile(RESOURCES_PATH + "\\none.png"));
		// assert(game.grassTexture.loadFromFile(RESOURCES_PATH + "\\Grass.png"));
		assert(game.scoreboardTexture.loadFromFile(RESOURCES_PATH + "\\Scoreboard.png"));
		assert(game.menuTexture.loadFromFile(RESOURCES_PATH + "\\Menu.png"));
		assert(game.icon.loadFromFile(RESOURCES_PATH + "\\Icon.png"));
		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts/Roboto-Regular.ttf"));
		assert(game.eatAppleBuffer.loadFromFile(RESOURCES_PATH + "\\MushroomEat.wav"));
		assert(game.deathBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(game.winnerBuffer.loadFromFile(RESOURCES_PATH + "\\Winner.wav"));
		assert(game.musicMainTheme.openFromFile(RESOURCES_PATH + "\\FrenchMainMusic.wav"));

		game.noneSprite.setTexture(game.noneTexture);
		
		window.setIcon(32, 32, game.icon.getPixelsPtr());
		SwitchGameState(game, GameState::MainMenu);
		InitGameState(game);
		InitUI(game.uiState, game.font);
		InitField(game);
	}

	void InitGameState(SGame& game)
	{
		// Set default values
		game.numEatenApples = 0;
		game.numScores = 0;
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
		
		game.backgroundGameZone.setTexture(game.grassTexture);
		SetSpriteSize(game.backgroundGameZone, SCREEN_WIDTH, SCREEN_HEIGHT);
		game.backgroundMenu.setTexture(game.menuTexture);
		SetSpriteSize(game.backgroundMenu, SCREEN_WIDTH, SCREEN_HEIGHT);
		game.backgroundScoreboard.setTexture(game.scoreboardTexture);
		SetSpriteSize(game.backgroundScoreboard, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		if (GetCurrentGameState(game) == GameState::Playing)
		{
			game.musicMainTheme.setVolume(20);
			game.musicMainTheme.setPlayingOffset(sf::seconds(0.f));
			game.musicMainTheme.play();
			game.musicMainTheme.setLoop(true);
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

	void InitGameOverState(SGame& game)
	{
		game.timeSinceGameOver = 0.f;
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
	
	void UpdateMainMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (!game.onKeyHold)
			{
				moveUp(game.uiState);
			}
			game.onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (!game.onKeyHold)
			{
				moveDown(game.uiState);
			}
			game.onKeyHold = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			int selectedIndex = getSelectedItemIndex(game.uiState);
			HandleMenuSelection(selectedIndex, game, game.uiState, window);  // Функция для обработки выбора пункта меню
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

	void HandleMenuSelection(int selectedIndex, SGame& game, UIState& uiState, sf::RenderWindow& window)
	{
		switch (selectedIndex)
		{
		case 0:  // "Начать игру"
			SwitchGameState(game, GameState::Playing);
			InitField(game);
			InitGameState(game);
			break;
		case 1:  // "Уровень сложности"
			// Здесь можно открыть подменю выбора сложности
				break;
		case 2:  // "Таблица рекордов"
			SwitchGameState(game, GameState::Scoreboard);
			break;
		case 3:  // "Настройки"
			// Здесь можно открыть меню настроек
				break;
		case 4:  // "Выход"
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
			SwitchGameState(game, GameState::Playing);
			game.onKeyHold = false;
			InitField(game);
			InitGameState(game);
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
					game.musicMainTheme.play();
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
		game.timeSinceGameOver += deltaTime;
		game.musicMainTheme.stop();
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			SwitchGameState(game, GameState::Playing);
			InitField(game);
			InitGameState(game);
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
				game.musicMainTheme.pause();
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
			UpdateMainMenuState(event, window, game);
			break;
		case SnakeGame::GameState::QuitMenu:
			UpdateQuitMenuState(event, window, game);
			break;
		case SnakeGame::GameState::Scoreboard:
			UpdateScoreboardState(game, event);
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

		SwitchGameStateInternal(game, oldState, state);
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

		SwitchGameStateInternal(game, oldState, state);
	}

	void SwitchGameState(SGame& game, GameState newState)
	{
		if (game.gameStateStack.size() > 0)
		{
			GameState oldState = game.gameStateStack.back();
			game.gameStateStack.pop_back();
			game.gameStateStack.push_back(newState);
			SwitchGameStateInternal(game, oldState, newState);
		}
		else
		{
			PushGameState(game, newState);
		}
	}

	void SwitchGameStateInternal(SGame& game, GameState oldState, GameState newState)
	{
		switch (newState)
		{
		case SnakeGame::GameState::Playing:
			{
				InitGameState(game);
				break;
			}
		case SnakeGame::GameState::GameOver:
			{
				InitGameOverState(game);
				break;
			}
		default:
			break;
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
					game.noneSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE + SCOREBAR_HEIGHT);
					window.draw(game.noneSprite);
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
			window.draw(game.backgroundLast);
		}

		// Draw UI
		DrawUI(game.uiState, game, window);
	}
}

