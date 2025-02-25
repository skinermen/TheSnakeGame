#include "Wall.h"
#include "Game.h"

namespace SnakeGame
{
	void InitWall(SWall& wall, const SGame& game)
	{
		wall.sprite.setTexture(game.uiState.wallTexture);
		SetSpriteSize(wall.sprite, WALL_SIZE, WALL_SIZE);
		wall.sprite.setOrigin(CELL_SIZE / 2.f, CELL_SIZE / 2.f);
	}

	void AddWall(SGame& game)
	{
		// Adding walls around the perimeter
		for (auto& i : game.field)
		{
			i[0] = FIELD_CELL_TYPE_WALL;
			i[FIELD_SIZE_Y - 1] = FIELD_CELL_TYPE_WALL;
		}
		for (int j = 1; j < FIELD_SIZE_Y - 1; j++)
		{
			game.field[0][j] = FIELD_CELL_TYPE_WALL;
			game.field[FIELD_SIZE_X - 1][j] = FIELD_CELL_TYPE_WALL;
		}
	}

	void DrawWall(SWall& wall, const SGame& game, sf::RenderWindow& window)
	{
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				// Check if the cell is a wall
				if (game.field[i][j] == FIELD_CELL_TYPE_WALL)
				{
					wall.sprite.setPosition(i * CELL_SIZE + BORDER_SIZE + CELL_SIZE / 2.f,
											j * CELL_SIZE + LEADERBOARD_HEIGHT + BORDER_SIZE + CELL_SIZE / 2.f);
					window.draw(wall.sprite);
				}
			}
		}
	}
}
