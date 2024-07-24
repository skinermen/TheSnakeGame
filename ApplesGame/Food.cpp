#include "Food.h"
#include "Game.h"

namespace ApplesGame
{
	void InitFood(SFood& food, const SGame& game)
	{
		for (int i = 0; i < NUM_BARRIERS; ++i)
		{
			if (IsRectanglesCollide(food.position, { FOOD_SIZE, FOOD_SIZE },
				game.barriersVec[i].position, { BARRIER_SIZE + 10.f, BARRIER_SIZE + 10.f })
				|| CheckScreenBorders(food.position, FOOD_SIZE, GAME_ZONE_WIDTH - 15.f, GAME_ZONE_HEIGHT - 15.f)
				|| IsRectanglesCollide(game.player.position, { PLAYER_SIZE + 20.f, PLAYER_SIZE + 20.f },
				food.position, { FOOD_SIZE, FOOD_SIZE }))
			{
				food.position = GetRandomPositionInScreen(GAME_ZONE_WIDTH, GAME_ZONE_HEIGHT);
			}
		}

		// Init food sprite
		food.sprite.setTexture(game.foodTexture);
		SetSpriteSize(food.sprite, FOOD_SIZE, FOOD_SIZE);
		SetSpriteRelativeOrigin(food.sprite, 0.5f, 0.5f);
	}

	void DrawFood(SFood& food, sf::RenderWindow& window)
	{
		food.sprite.setPosition(food.position.x, food.position.y);
		window.draw(food.sprite);
	}
}