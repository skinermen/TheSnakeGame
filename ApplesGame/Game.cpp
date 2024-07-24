#include "Game.h"
#include <cassert>
#include <random>

namespace ApplesGame
{
	void InitGame(SGame& game, sf::RenderWindow& window)
	{
		assert(game.playerTextureSide.loadFromFile(RESOURCES_PATH + "\\HedgehogSide.png"));
		assert(game.playerTextureTop.loadFromFile(RESOURCES_PATH + "\\HedgehogTop.png"));
		assert(game.foodTexture.loadFromFile(RESOURCES_PATH + "\\Mushroom.png"));
		assert(game.barrierTexture.loadFromFile(RESOURCES_PATH + "\\Toadstool.png"));
		assert(game.grassTexture.loadFromFile(RESOURCES_PATH + "\\Grass.png"));
		assert(game.menuTexture.loadFromFile(RESOURCES_PATH + "\\Menu.png"));
		assert(game.icon.loadFromFile(RESOURCES_PATH + "\\Icon.png"));
		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts/Roboto-Regular.ttf"));
		assert(game.eatFoodBuffer.loadFromFile(RESOURCES_PATH + "\\MushroomEat.wav"));
		assert(game.deathBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(game.winnerBuffer.loadFromFile(RESOURCES_PATH + "\\Winner.wav"));
		assert(game.musicMainTheme.openFromFile(RESOURCES_PATH + "\\FrenchMainMusic.wav"));
		
		window.setIcon(32, 32, game.icon.getPixelsPtr());
		SwitchGameState(game, GameState::MainMenu);
		InitGameState(game);
		InitUI(game.uiState, game.font);
	}

	void InitGameState(SGame& game)
	{
		// Set default values
		game.numFoods = GetRandomInt(NUM_FOOD_MIN, NUM_FOOD_MAX);
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
		game.backgroundMenu.setTexture(game.menuTexture);
		
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

	void UpdateMainMenuState(const sf::Event& event, sf::RenderWindow& window, SGame& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			SwitchGameState(game, GameState::Playing);
			InitGameState(game);
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
			window.close();
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

	void UpdatePlayingState(const sf::Event& event, SGame& game, float deltaTime)
	{
		MovePlayer(game, deltaTime);
		FindPlayerCollision(game);

		if (!(game.gameMode & MASK_INFINIT_FOODS) && game.numEatenFoods == game.numFoods)
		{
			SwitchGameState(game, GameState::Winner);
			PlaySound(game.uiState, game.winnerBuffer);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		{
			if (!game.onKeyHoldTab)
			{
				game.isScreenLeaderboard = true;
			}
			game.onKeyHoldTab = true;
		}
		
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Tab)
		{
			game.isScreenLeaderboard = false;
			game.onKeyHoldTab = false;
		}
	}

	void UpdateGame(SGame& game, float deltaTime, sf::RenderWindow& window, sf::Event event)
	{
		GameState gameState = game.gameStateStack.back();
		
		switch (gameState)
		{
		case ApplesGame::GameState::Playing:
			UpdatePlayingState(event, game, deltaTime);
			break;
		case ApplesGame::GameState::GameOver:
			UpdateGameOverState(game, window, deltaTime);
			break;
		case ApplesGame::GameState::Winner:
			UpdateGameOverState(game, window, deltaTime);
			break;
		case ApplesGame::GameState::MainMenu:
			UpdateMainMenuState(event, window, game);
			break;
		case ApplesGame::GameState::QuitMenu:
			UpdateQuitMenuState(event, window, game);
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
		case ApplesGame::GameState::Playing:
			{
				InitGameState(game);
				break;
			}
		case ApplesGame::GameState::GameOver:
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
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape &&
			(GetCurrentGameState(game) == GameState::Playing || GetCurrentGameState(game) == GameState::QuitMenu))
		{
			if (!game.onKeyEsc)
			{
				game.gameStateStack.push_back(GameState::QuitMenu);
				game.musicMainTheme.pause();
				game.onKeyEsc = true;
			}
			else if (game.onKeyEsc && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				game.gameStateStack.pop_back();
				game.onKeyEsc = false;
				if (game.isPlayMusic)
				{
					game.musicMainTheme.play();
				}
			}
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

	void ShutdownPlayingState(SGame& game)
	{
		
	}

	void ShutdownGameOverState(SGame& game)
	{
		
	}

	void DrawGame(SGame& game, sf::RenderWindow& window)
	{
		// Draw Background Game Zone
		if (GetCurrentGameState(game) == GameState::Playing || GetCurrentGameState(game) == GameState::GameOver ||
			GetCurrentGameState(game) == GameState::Winner)
		{
			window.draw(game.backgroundGameZone);
		}
		if (GetPreviousGameState(game) == GameState::Playing || GetPreviousGameState(game) == GameState::GameOver ||
			GetPreviousGameState(game) == GameState::Winner)
		{
			window.draw(game.backgroundGameZone);
		}
		
		// Draw Player
		DrawPlayer(game.player, game, window);

		// Draw Food
		for (SFood& food : game.foodsVec)
		{
			DrawFood(food, window);
		}

		// Draw Barrier
		for (SBarrier& barrier : game.barriersVec)
		{
			DrawBarrier(barrier, window);
		}

		// Draw UI
		DrawUI(game.uiState, game, window);
	}

	void DeinitializeGame(SGame& game)
	{

	}
}

