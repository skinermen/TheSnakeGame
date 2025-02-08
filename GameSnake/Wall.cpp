#include "Wall.h"
#include "Game.h"

namespace SnakeGame
{
	void InitWall(SWall& wall, const SGame& game)
	{
		// Инициализация спрайта стены
		wall.sprite.setTexture(game.uiState.wallTexture);
		SetSpriteSize(wall.sprite, WALL_SIZE, WALL_SIZE);  // Устанавливаем размер спрайта стены
	}

	void AddWall(SGame& game)
	{
		// Добавление стен по периметру
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			game.field[i][0] = FIELD_CELL_TYPE_WALL;
			game.field[i][FIELD_SIZE_Y - 1] = FIELD_CELL_TYPE_WALL;
		}
		for (int j = 1; j < FIELD_SIZE_Y - 1; j++)
		{
			game.field[0][j] = FIELD_CELL_TYPE_WALL;
			game.field[FIELD_SIZE_X - 1][j] = FIELD_CELL_TYPE_WALL;
		}
	}

	void DrawWall(SWall& wall, SGame& game, sf::RenderWindow& window)
	{
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				// Проверяем, является ли клетка стеной
				if (game.field[i][j] == FIELD_CELL_TYPE_WALL)
				{
					// Устанавливаем позицию спрайта стены
					wall.sprite.setPosition(i * CELL_SIZE, j * CELL_SIZE + SCOREBAR_HEIGHT);
					window.draw(wall.sprite);  // Рисуем стену
				}
			}
		}
	}
}
