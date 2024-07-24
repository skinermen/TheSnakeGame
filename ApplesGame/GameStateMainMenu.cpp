// #include "GameStateMainMenu.h"
// #include "Game.h"
// #include <assert.h>
//
// namespace ApplesGame
// {
// 	void InitGameStateMainMenu(GameStateMainMenuData& data, SGame& game)
// 	{
// 		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
// 		
// 		InitTextUI(data.mainMenuTextStartGame, data.font, 72, 1, sf::Color::Green, "Press the SPACE\nto start the game");
// 		data.mainMenuTextStartGame.setOrigin(GetItemOrigin(data.mainMenuTextStartGame, { 0.5f, 0.5f }));
// 		InitTextUI(data.mainMenuTextInsructions, data.font, 24, 3, sf::Color::Green, "Use the keys 1, 2 to select the game mode");
// 		InitTextUI(data.mainMenuGameModeUnlimitedFoods, data.font, 24, 1, sf::Color::White);
// 		InitTextUI(data.mainMenuGameModeAcceleration, data.font, 24, 1, sf::Color::White);
// 	}
//
// 	void HandleGameStateMainMenuWindowEvent(SGame& game, sf::Event& event, sf::RenderWindow& window)
// 	{
// 		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
// 		{
// 			SwitchGameState(game, GameStateType::Playing);
// 			InitGameState(game);
// 		}
// 		
// 		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
// 		{
// 			if (!game.onKeyHold1)
// 			{
// 				ToggleGameMode(game, MASK_INFINIT_FOODS);
// 				GetButtonText(game, MASK_INFINIT_FOODS);
// 			}
// 			game.onKeyHold1 = true;
// 		}
//
// 		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num1)
// 		{
// 			game.onKeyHold1 = false;
// 		}
//
// 		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
// 		{
// 			if (!game.onKeyHold2)
// 			{
// 				ToggleGameMode(game, MASK_WITH_ACCELERATION);
// 				GetButtonText(game, MASK_WITH_ACCELERATION);
// 			}
// 			game.onKeyHold2 = true;
// 		}
//
// 		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num2)
// 		{
// 			game.onKeyHold2 = false;
// 		}
// 		
// 		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
// 		{
// 			window.close();
// 		}
// 	}
//
// 	void UpdateGameStateMainMenu(GameStateMainMenuData& data, SGame& game, float timeDelta)
// 	{
// 		data.mainMenuGameModeUnlimitedFoods.setString("Unlimited mushrooms: " + GetButtonText(game, MASK_INFINIT_FOODS));
// 		data.mainMenuGameModeAcceleration.setString("Acceleration of movement: " + GetButtonText(game, MASK_WITH_ACCELERATION));
// 	}
//
// 	void DrawGameStateMainMenu(GameStateMainMenuData& data, SGame& game, sf::RenderWindow& window)
// 	{
// 		if (GetCurrentGameState(game) == GameStateType::MainMenu)
// 		{
// 			game.backgroundLast = game.backgroundMenu;
// 			window.draw(game.backgroundMenu);
// 		}
// 			
// 		data.mainMenuTextStartGame.setPosition(window.getSize().x / 2.f, 100.f);
// 		window.draw(data.mainMenuTextStartGame);
// 			
// 		data.mainMenuTextInsructions.setPosition(10.f, window.getSize().y - 100.f);
// 		window.draw(data.mainMenuTextInsructions);
//
// 		data.mainMenuGameModeUnlimitedFoods.setPosition(10.f, window.getSize().y - 75.f);
// 		window.draw(data.mainMenuGameModeUnlimitedFoods);
//
// 		data.mainMenuGameModeAcceleration.setPosition(10.f, window.getSize().y - 50.f);
// 		window.draw(data.mainMenuGameModeAcceleration);
// 	}
//
// }
