#include "Food.h"
#include "Game.h"

namespace SnakeGame
{
	void InitFood(SFood& food, const SGame& game)
	{
		// for (int i = 0; i < NUM_BARRIERS; ++i)
		// {
		// 	if (IsRectanglesCollide(food.position, { FOOD_SIZE, FOOD_SIZE },
		// 		game.barriersVec[i].position, { BARRIER_SIZE + 10.f, BARRIER_SIZE + 10.f })
		// 		|| CheckScreenBorders(food.position, FOOD_SIZE, SCREEN_WIDTH - 15.f, SCREEN_HEIGHT - 15.f)
		// 		|| IsRectanglesCollide(game.player.position, { PLAYER_SIZE + 20.f, PLAYER_SIZE + 20.f },
		// 		food.position, { FOOD_SIZE, FOOD_SIZE }))
		// 	{
		// 		food.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		// 	}
		// }

		// Init food sprite
		food.sprite.setTexture(game.foodTexture);
		SetSpriteSize(food.sprite, FOOD_SIZE, FOOD_SIZE);
		// SetSpriteRelativeOrigin(food.sprite, 0.5f, 0.5f);
	}

	void AddApple(SGame& game)
	{
		int applePos = GetRandomEmptyCell(game);
		if (applePos != -1)
		{
			//
		}
		game.field[applePos / FIELD_SIZE_X][applePos % FIELD_SIZE_X] = FIELD_CELL_TYPE_APPLE;
	}

	void DrawFood(SFood& food, SGame& game, sf::RenderWindow& window)
	{
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				switch (game.field[i][j])
				{
				case FIELD_CELL_TYPE_APPLE:
					food.sprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
					window.draw(food.sprite);
					break;
				}
			}
		}
		// food.sprite.setPosition(food.position.x, food.position.y);
		// window.draw(food.sprite);
	}
}