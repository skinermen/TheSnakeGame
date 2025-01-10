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

	// typedef Vector2D Position2D;

	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight);
	bool CheckScreenBorders(Position2D rectPosition, const float rectSize, const int screen_width, const int screen_height);
	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size,
		Position2D rect2OPosition, Vector2D rect2Size);
	bool IsCirclesCollide(Position2D circle1Position, float circle1Radius,
		Position2D circle2Position, float circle2Radius);
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
	sf::Vector2f GetSpriteScale(sf::Sprite& sprite, float desiredSizeX, float desiredSizeY);
	sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition);
	int GetRandomInt(const int &min, const int &max);
}