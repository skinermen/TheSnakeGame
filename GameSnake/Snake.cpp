#include "Snake.h"
#include "Game.h"
#include <vector>

namespace SnakeGame
{
	void InitSnake(SSnake& snake, SGame& game)
	{
		// Init snake sprite
		snake.spriteHead.setTexture(game.snakeTextureHead);
		snake.spriteBody.setTexture(game.snakeTextureBody);
		SetSpriteSize(snake.spriteHead, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE);
		SetSpriteSize(snake.spriteBody, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE);
		snake.spriteHead.setScale(GetSpriteScale(snake.spriteHead, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE));
		snake.spriteBody.setScale(GetSpriteScale(snake.spriteBody, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE));

		// Инициализация змейки
		snake.snakeLength = 4; // Задаем длину змейки
		snake.direction = SnakeDirection::Right; // Начальное направление
		snake.position = { FIELD_SIZE_X / 2, FIELD_SIZE_Y / 2 }; // Центр поля
		snake.lastUpdateTime = 0.f;
		snake.movementInterval = 0.2f; // Интервал движения в секундах
	}

	void AddSnake(SGame& game)
	{
		// Устанавливаем змейку на поле
		for (int i = 0; i < game.snake.snakeLength; i++)
		{
			game.field[game.snake.position.x - i][game.snake.position.y] = game.snake.snakeLength - i;
		}
	}

	void DrawSnake(SSnake& snake, SGame& game, sf::RenderWindow& window)
	{
		// Сначала отрисовываем голову
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (game.field[i][j] == snake.snakeLength) // Условие для головы
				{
					snake.spriteHead.setPosition(i * CELL_SIZE, j * CELL_SIZE);
					window.draw(snake.spriteHead);
				}
			}
		}

		// Затем отрисовываем тело
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (game.field[i][j] > FIELD_CELL_TYPE_NONE && game.field[i][j] < snake.snakeLength)
				{
					snake.spriteBody.setPosition(i * CELL_SIZE, j * CELL_SIZE);
					window.draw(snake.spriteBody);
				}
			}
		}
	}

	void GrowSnake(SGame& game)
	{
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (game.field[i][j] > FIELD_CELL_TYPE_NONE)
				{
					game.field[i][j]++;
				}
			}
		}
	}

	void HandleInput(SSnake& player)
	{
		// Получаем последнее направление, которое было добавлено в очередь
		SnakeDirection currentDirection = player.direction;
		if (!player.directionQueue.empty())
		{
			currentDirection = player.directionQueue.back();
		}

		// Регистрируем нажатия клавиш
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && currentDirection != SnakeDirection::Left)
		{
			if (player.directionQueue.empty() || player.directionQueue.back() != SnakeDirection::Right)
			{
				player.directionQueue.push(SnakeDirection::Right);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currentDirection != SnakeDirection::Down)
		{
			if (player.directionQueue.empty() || player.directionQueue.back() != SnakeDirection::Up)
			{
				player.directionQueue.push(SnakeDirection::Up);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currentDirection != SnakeDirection::Right)
		{
			if (player.directionQueue.empty() || player.directionQueue.back() != SnakeDirection::Left)
			{
				player.directionQueue.push(SnakeDirection::Left);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currentDirection != SnakeDirection::Up)
		{
			if (player.directionQueue.empty() || player.directionQueue.back() != SnakeDirection::Down)
			{
				player.directionQueue.push(SnakeDirection::Down);
			}
		}

		// Ограничиваем размер очереди, если необходимо
		while (player.directionQueue.size() > 3)
		{
			player.directionQueue.pop();
		}
	}
	
	void MoveSnake(SGame& game, float currentTime)
	{
		SSnake& player = game.snake;

		if (GetCurrentGameState(game) != GameState::Playing)
		{
			return;
		}

	    if (currentTime - player.lastUpdateTime >= player.movementInterval)
	    {
	        // Применяем следующее направление из очереди, если есть
	        if (!player.directionQueue.empty())
	        {
	            SnakeDirection nextDirection = player.directionQueue.front();
	            player.directionQueue.pop();

	            // Проверяем, что направление не противоположно текущему
	            if ((player.direction == SnakeDirection::Up && nextDirection != SnakeDirection::Down) ||
	                (player.direction == SnakeDirection::Down && nextDirection != SnakeDirection::Up) ||
	                (player.direction == SnakeDirection::Left && nextDirection != SnakeDirection::Right) ||
	                (player.direction == SnakeDirection::Right && nextDirection != SnakeDirection::Left))
	            {
	                player.direction = nextDirection;
	            }
	        }

	        // Перемещаем голову змейки
	        switch (player.direction)
	    	{
	            case SnakeDirection::Right:
	                player.position.x++;
	                if (player.position.x >= FIELD_SIZE_X) player.position.x = 0;
	                break;
	            case SnakeDirection::Up:
	                player.position.y--;
	                if (player.position.y < 0) player.position.y = FIELD_SIZE_Y - 1;
	                break;
	            case SnakeDirection::Left:
	                player.position.x--;
	                if (player.position.x < 0) player.position.x = FIELD_SIZE_X - 1;
	                break;
	            case SnakeDirection::Down:
	                player.position.y++;
	                if (player.position.y >= FIELD_SIZE_Y) player.position.y = 0;
	                break;
	        }

	        // Проверяем столкновение c собой
	        if (game.field[player.position.x][player.position.y] > FIELD_CELL_TYPE_NONE)
	        {
	            game.gameStateStack.push_back(GameState::GameOver);
	        	game.timeSinceGameOver = 0.f;
	        	PlaySound(game.uiState, game.deathBuffer);
	            return;
	        }

	    	// Проверяем столкновение c собой
	    	if (game.field[player.position.x][player.position.y] == FIELD_CELL_TYPE_WALL)
	    	{
	    		game.gameStateStack.push_back(GameState::GameOver);
	    		game.timeSinceGameOver = 0.f;
	    		PlaySound(game.uiState, game.deathBuffer);
	    		return;
	    	}

	        // Проверяем, съела ли змейка яблоко
	        if (game.field[player.position.x][player.position.y] == FIELD_CELL_TYPE_APPLE)
	        {
	            player.snakeLength++;
	            GrowSnake(game);
	            AddApple(game);
	            PlaySound(game.uiState, game.eatAppleBuffer);
	        }

	        // Обновляем игровое поле
	        game.field[player.position.x][player.position.y] = player.snakeLength + 1;

	        // Уменьшаем время жизни частей тела
	        for (int i = 0; i < FIELD_SIZE_X; i++)
	        {
	            for (int j = 0; j < FIELD_SIZE_Y; j++)
	            {
	                if (game.field[i][j] > FIELD_CELL_TYPE_NONE)
	                {
	                    game.field[i][j]--;
	                }
	            }
	        }

	        // Обновляем время последнего обновления
	        player.lastUpdateTime = currentTime;
	    }
	}
}
