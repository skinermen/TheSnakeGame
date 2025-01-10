#include "Math.h"
#include <cstdlib>
#include <random>

namespace SnakeGame
{
	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;

		return result;
	}

	bool CheckScreenBorders(Position2D rectPosition, const float rectSize, const int screen_width, const int screen_height)
	{
		return (rectPosition.x - rectSize / 2.f < 0.f || rectPosition.x + rectSize / 2.f > screen_width ||
			rectPosition.y - rectSize / 2.f < 0.f || rectPosition.y + rectSize / 2.f > screen_height);
	}

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2OPosition, Vector2D rect2Size)
	{
		float dx = (float)fabs(rect1Position.x - rect2OPosition.x);
		float dy = (float)fabs(rect1Position.y - rect2OPosition.y);
		return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
			dy <= (rect1Size.y + rect2Size.y) / 2.f);
	}

	bool IsCirclesCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius)
	{
		float squareDistance = (circle1Position.x - circle2Position.x) *
			(circle1Position.x - circle2Position.x) +
			(circle1Position.y - circle2Position.y) * (circle1Position.y - circle2Position.y);
		float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius) / 4;
		return (squareDistance <= squareRadiusSum);
	}

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

	sf::Vector2f GetSpriteScale(sf::Sprite& sprite, float desiredSizeX, float desiredSizeY)
	{
		sf::Vector2u textureSize = sprite.getTexture()->getSize();
		sf::Vector2f spriteScale = { desiredSizeX / textureSize.x, desiredSizeY / textureSize.y };
		return spriteScale;
	}

	sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return {
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y,
		};
	}

	int GetRandomInt(const int &min, const int &max)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(min, max);
		return dist(gen);
	}

// 	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
// {
// 	sf::FloatRect totalRect;
// 	// Calculate total height/width of all texts
// 	for (auto it = items.begin(); it != items.end(); ++it)
// 	{
// 		sf::FloatRect itemRect = (*it)->getGlobalBounds();
//
// 		if (orientation == Orientation::Horizontal)
// 		{
// 			totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
// 			totalRect.height = std::max(totalRect.height, itemRect.height);
// 		}
// 		else
// 		{
// 			totalRect.width = std::max(totalRect.width, itemRect.width);
// 			totalRect.height += itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
// 		}
// 	}
//
// 	totalRect.left = position.x - origin.x * totalRect.width;
// 	totalRect.top = position.y - origin.y * totalRect.height;
// 	sf::Vector2f currentPos = { totalRect.left, totalRect.top };
// 	
// 	for (auto it = items.begin(); it != items.end(); ++it)
// 	{
// 		sf::FloatRect itemRect = (*it)->getGlobalBounds();
// 		sf::Vector2f itemOrigin;
//
// 		if (orientation == Orientation::Horizontal)
// 		{
// 			itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
// 			itemOrigin.x = 0.f;
// 			currentPos.y = totalRect.top + itemOrigin.y * totalRect.height;
// 		}
// 		else
// 		{
// 			itemOrigin.y = 0.f;
// 			itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
// 			currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
// 		}
// 		
// 		(*it)->setOrigin(GetTextOrigin()Origin(**it, itemOrigin));
// 		(*it)->setPosition(currentPos);
// 		window.draw(**it);
//
// 		if (orientation == Orientation::Horizontal)
// 		{
// 			currentPos.x += itemRect.width + spacing;
// 		}
// 		else
// 		{
// 			currentPos.y += itemRect.height + spacing;
// 		}
//
// 		
// 	}
// }
//
// bool IsPointInRect(Vector2D point, Vector2D rectTL, Vector2D rectBR)
// {
// 	if (point.x < rectTL.x || point.x > rectBR.x)
// 	{
// 		return false;
// 	}
// 	if (point.y < rectTL.y || point.y > rectBR.y)
// 	{
// 		return false;
// 	}
// 	return true;
// }
}




