#pragma once
#include "SFML/Graphics.hpp"

namespace ApplesGame
{
    struct SGame;
    struct GameStateMainMenuData
    {
        sf::Font font;

        bool isMainMenuTextVisible;

        sf::Text mainMenuTextStartGame;
        sf::Text mainMenuTextInsructions;
        sf::Text mainMenuGameModeUnlimitedFoods;
        sf::Text mainMenuGameModeAcceleration;
    };

    void InitGameStateMainMenu(GameStateMainMenuData& data, SGame& game);
    void HandleGameStateMainMenuWindowEvent(SGame& game, sf::Event& event, sf::RenderWindow& window);
    void UpdateGameStateMainMenu(GameStateMainMenuData& data, SGame& game, float timeDelta);
    void DrawGameStateMainMenu(GameStateMainMenuData& data, SGame& game, sf::RenderWindow& window);
}
