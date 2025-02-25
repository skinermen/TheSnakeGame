#pragma once
#include <SFML/Graphics.hpp>

namespace sf
{
	class Sprite;
}

namespace SnakeGame
{
	struct Vector2D
	{
		float x = 0;
		float y = 0;
	};
	
	struct Position2D
	{
		int x = 0;
		int y = 0;
	};
	
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, float desiredSizeX, float desiredSizeY);
	sf::Vector2f GetTextOrigin(const sf::Text& text);
	int GetRandomInt(const int &min, const int &max);
}