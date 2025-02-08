#include "Apple.h"
#include "Game.h"

namespace SnakeGame
{
	void InitApple(SApple& apple, const SGame& game)
	{
		// Init apple sprite
		apple.sprite.setTexture(game.uiState.appleTexture);
		SetSpriteSize(apple.sprite, FOOD_SIZE, FOOD_SIZE);
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

	void DrawApple(SApple& apple, SGame& game, sf::RenderWindow& window)
	{
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				switch (game.field[i][j])
				{
				case FIELD_CELL_TYPE_APPLE:
					apple.sprite.setPosition(i * CELL_SIZE, j * CELL_SIZE + SCOREBAR_HEIGHT);
					window.draw(apple.sprite);
					break;
				}
			}
		}
	}
}