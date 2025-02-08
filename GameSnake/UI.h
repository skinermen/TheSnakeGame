#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"

namespace SnakeGame
{
	struct UIState
	{
		bool isGameTextVisible;
		bool isGameOverTextVisible;
		bool isWinnerTextVisible;
		bool isMainMenuTextVisible;
		bool isPauseMenuTextVisible;
		bool isScoreboardVisible;

		sf::Text gameScoreText;
		sf::Text inputText;
		MenuState menuState;

		// Resources
		sf::Sprite noneSprite;
		sf::Texture snakeTextureHead;
		sf::Texture snakeTextureBody;
		sf::Texture appleTexture;
		sf::Texture wallTexture;
		sf::Texture noneTexture;
		// sf::Texture grassTexture;
		sf::Sound sound;
		sf::SoundBuffer eatAppleBuffer;
		sf::SoundBuffer deathBuffer;
		sf::SoundBuffer winnerBuffer;
		sf::Music musicMainTheme;
		sf::Image icon;
	};
	
	void InitTextUI(sf::Text& text, const sf::Font& font, int size, int style, sf::Color color, const std::string& name = "none text");
	void InitUIResources(UIState& uiState);
	void InitUI(UIState& uiState, const sf::Font& font);
	void UpdateUI(UIState& uiState, const struct SGame& game);
	void DrawUI(UIState& uiState, SGame& game, sf::RenderWindow& window);
	void PlaySound(UIState& uiState, const sf::SoundBuffer& buffer);
}