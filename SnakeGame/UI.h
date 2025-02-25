#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"

namespace SnakeGame
{
	struct UIState
	{
		bool isPlayingTextVisible;
		bool isMainMenuTextVisible;
		bool isPauseMenuTextVisible;
		bool isNameInputMenuTextVisible;
		bool isConfirmationMenuTextVisible;
		bool isGameOverMenuTextVisible;
		bool isDifficultyMenuTextVisible;
		bool isScoreboardMenuVisible;
		bool isOptionsMenuTextVisible;

		sf::RectangleShape playingRectangle;
		sf::Text playingScoreText;
		sf::Text playingInputText;
		SMenuState menuState;

		// Resources
		sf::Sprite noneSprite;
		sf::Texture snakeTextureHead;
		sf::Texture snakeTextureBody;
		sf::Texture appleTexture;
		sf::Texture wallTexture;
		sf::Texture noneTexture;
		sf::Sound sound;
		sf::SoundBuffer eatAppleBuffer;
		sf::SoundBuffer deathBuffer;
		sf::SoundBuffer pressEnterBuffer;
		sf::SoundBuffer selectMenuBuffer;
		sf::Music musicMainTheme;
		sf::Image icon;
	};
	
	void InitTextUI(sf::Text& text, const sf::Font& font, int size, int style, sf::Color color, const std::string& name = "none");
	void InitRectangleUI(sf::RectangleShape& rectangle, float sizeX, float sizeY, sf::Color fillColor, sf::Color outlineColor, float outlineThickness);
	void InitUIResources(UIState& uiState);
	void InitUI(UIState& uiState);
	void UpdateUI(UIState& uiState, const SGame& game);
	void DrawUI(UIState& uiState, sf::RenderWindow& window);
	void PlaySound(UIState& uiState, const sf::SoundBuffer& buffer);
	void InitPlayMusic(UIState& uiState);
	void OnPlayMusic(UIState& uiState, bool isPlay);
}