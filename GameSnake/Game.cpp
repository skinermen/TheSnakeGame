#include "Game.h"
#include <cassert>
#include <random>

namespace SnakeGame
{
	void InitGame(SGame& game, sf::RenderWindow& window)
	{
		assert(game.snakeTextureHead.loadFromFile(RESOURCES_PATH + "\\snake.png"));
		assert(game.snakeTextureBody.loadFromFile(RESOURCES_PATH + "\\Snake_Body.png"));
		assert(game.foodTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.barrierTexture.loadFromFile(RESOURCES_PATH + "\\wall.png"));
		assert(game.noneTexture.loadFromFile(RESOURCES_PATH + "\\none.png"));
		// assert(game.grassTexture.loadFromFile(RESOURCES_PATH + "\\Grass.png"));
		assert(game.scoreboardTexture.loadFromFile(RESOURCES_PATH + "\\Scoreboard.png"));
		assert(game.menuTexture.loadFromFile(RESOURCES_PATH + "\\Menu.png"));
		assert(game.icon.loadFromFile(RESOURCES_PATH + "\\Icon.png"));
		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts/Roboto-Regular.ttf"));
		assert(game.eatFoodBuffer.loadFromFile(RESOURCES_PATH + "\\MushroomEat.wav"));
		assert(game.deathBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(game.winnerBuffer.loadFromFile(RESOURCES_PATH + "\\Winner.wav"));
		assert(game.musicMainTheme.openFromFile(RESOURCES_PATH + "\\FrenchMainMusic.wav"));

		game.noneSprite.setTexture(game.noneTexture);
		
		window.setIcon(32, 32, game.icon.getPixelsPtr());
		SwitchGameState(game, GameState::MainMenu);
		InitGameState(game);
		InitUI(game.uiState, game.font);
		ClearField(game);
	}

	void InitGameState(SGame& game)
	{
		// Set default values
		game.numFoods = NUM_FOOD;
		game.numEatenFoods = 0;
		game.timeSinceGameOver = 0.f;

		// Init Player
		InitPlayer(game.player, game);
		
		// Init Barriers
		if (!game.barriersVec.empty())
		{
			game.barriersVec.clear();
		}

		for (int i = 0; i < NUM_BARRIERS; i++)
		{
			SBarrier barrier;
			InitBarrier(barrier, game);
			game.barriersVec.emplace_back(barrier);
		}
		
		// Init Foods
		if (!game.foodsVec.empty())
		{
			game.foodsVec.clear();
		}
		
		for (int i = 0; i < game.numFoods; i++)
		{
			SFood food;
			InitFood(food, game);
			game.foodsVec.emplace_back(food);
		}
		
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

	void InitGameOverState(SGame& game)
	{
		game.timeSinceGameOver = 0.f;
	}

	void ClearField(SGame& game)
	{
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				game.field[i][j] = FIELD_CELL_TYPE_NONE;
			}
		}
		for (int i = 0; i < game.player.snakeLength; i++)
		{
			game.field[game.player.position.x - i][game.player.position.y] = game.player.snakeLength - i;
		}
		AddApple(game);
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

	// void DrawField(SGame& game, SFood& food, SPlayer& player, sf::RenderWindow& window)
	// {
	// 	for (int i = 0; i < FIELD_SIZE_X; i++)
	// 	{
	// 		for (int j = 0; j < FIELD_SIZE_Y; j++)
	// 		{
	// 			switch (game.field[i][j])
				// {
				// case FIELD_CELL_TYPE_NONE:
				// 	game.noneSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
				// 	window.draw(game.noneSprite);
				// 	break;
				// case FIELD_CELL_TYPE_APPLE:
				// 	food.sprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
				// 	window.draw(food.sprite);
				// 	break;
				// case FIELD_CELL_TYPE_PLAYER:
				// 	player.sprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
				// 	window.draw(player.sprite);
	// 			}
	// 		}
	// 	}
	// }
	
	void UpdateMainMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			SwitchGameState(game, GameState::Playing);
			InitGameState(game);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		{
			SwitchGameState(game, GameState::Scoreboard);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if (!game.onKeyHold1)
			{
				ToggleGameMode(game, MASK_INFINIT_FOODS);
				GetButtonText(game, MASK_INFINIT_FOODS);
			}
			game.onKeyHold1 = true;
		}

		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num1)
		{
			game.onKeyHold1 = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			if (!game.onKeyHold2)
			{
				ToggleGameMode(game, MASK_WITH_ACCELERATION);
				GetButtonText(game, MASK_WITH_ACCELERATION);
			}
			game.onKeyHold2 = true;
		}

		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num2)
		{
			game.onKeyHold2 = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!game.onKeyEsc)
			{
				window.close();
			}
			game.onKeyEsc = true;
		}

		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			game.onKeyEsc = false;
		}
		
	}

	void UpdateQuitMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			SwitchGameState(game,GameState::MainMenu);
			game.onKeyEsc = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			SwitchGameState(game, GameState::Playing);
			game.onKeyEsc = false;
			InitGameState(game);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			game.onKeyEsc = false;
			window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!game.onKeyEsc)
			{
				game.gameStateStack.pop_back();
				game.onKeyEsc = false;
				if (game.isPlayMusic)
				{
					game.musicMainTheme.play();
				}
			}
			game.onKeyEsc = true;
		}
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			game.onKeyEsc = false;
		}
	}

	void UpdateGameOverState(SGame& game, sf::RenderWindow& window, float deltaTime)
	{
		game.timeSinceGameOver += deltaTime;
		game.musicMainTheme.stop();
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			SwitchGameState(game, GameState::Playing);
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
		HandleInput(game.player);
		MovePlayer(game, currentTime);
		FindPlayerCollision(game);

		if (!(game.gameMode & MASK_INFINIT_FOODS) && game.numEatenFoods == game.numFoods)
		{
			SwitchGameState(game, GameState::Winner);
			PlaySound(game.uiState, game.winnerBuffer);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!game.onKeyEsc)
			{
				game.gameStateStack.push_back(GameState::QuitMenu);
				game.musicMainTheme.pause();
				game.onKeyEsc = true;
			}
			game.onKeyEsc = true;
		}
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			game.onKeyEsc = false;
		}
	}

	void UpdateScoreboardState(SGame& game, sf::Event& event)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!game.onKeyEsc)
			{
				SwitchGameState(game,GameState::MainMenu);
			}
			game.onKeyEsc = true;
		}

		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			game.onKeyEsc = false;
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
		switch (oldState)
		{
		case GameState::Playing:
		{
			ShutdownPlayingState(game);
			break;
		}
		case GameState::GameOver:
		{
			ShutdownGameOverState(game);
			break;
		}
		}

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

	void HandleInput(const sf::Event& event, sf::RenderWindow& window, SGame& game)
	{
		
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

	void ShutdownPlayingState(SGame& game)
	{
		
	}

	void ShutdownGameOverState(SGame& game)
	{
		
	}

	void DrawGame(SGame& game, sf::RenderWindow& window)
	{
		// Draw Background Game Zone
		// if (GetCurrentGameState(game) == GameState::Playing || GetCurrentGameState(game) == GameState::GameOver ||
		// 	GetCurrentGameState(game) == GameState::Winner)
		// {
		// 	window.draw(game.backgroundGameZone);
		// }
		// if (GetPreviousGameState(game) == GameState::Playing || GetPreviousGameState(game) == GameState::GameOver ||
		// 	GetPreviousGameState(game) == GameState::Winner)
		// {
		// 	window.draw(game.backgroundGameZone);
		// }
		
		// Draw Background
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				switch (game.field[i][j])
				{
				case FIELD_CELL_TYPE_NONE:
					game.noneSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
					window.draw(game.noneSprite);
					break;
				}
			}
		}
		
		// Draw Player
		DrawPlayer(game.player, game, window);

		// Draw Food
		for (SFood& food : game.foodsVec)
		{
			DrawFood(food, game, window);
		}

		// Draw Barrier
		for (SBarrier& barrier : game.barriersVec)
		{
			DrawBarrier(barrier, window);
		}

		if (GetCurrentGameState(game) == GameState::Scoreboard)
		{
			window.draw(game.backgroundLast);
		}

		// Draw UI
		DrawUI(game.uiState, game, window);
	}

	void DeinitializeGame(SGame& game)
	{

	}
}

