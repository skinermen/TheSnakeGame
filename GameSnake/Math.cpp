#include "Math.h"
#include <random>

namespace SnakeGame
{
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, float desiredSizeX, float desiredSizeY)
	{
		sf::Vector2u textureSize = sprite.getTexture()->getSize();
		sf::Vector2f spriteScale = { desiredSizeX / textureSize.x, desiredSizeY / textureSize.y };
		return spriteScale;
	}

	sf::Vector2f GetTextOrigin(const sf::Text& text)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return
		{
			textSize.width / 2.f,
			textSize.height / 2.f,
		};
	}

	int GetRandomInt(const int &min, const int &max)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution dist(min, max);
		return dist(gen);
	}
}




