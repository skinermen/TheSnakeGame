#include "Player.h"
#include "Game.h"
#include <vector>

namespace SnakeGame
{
	void InitPlayer(SPlayer& player, SGame& game)
	{
		// Init player state
		// player.position = { FIELD_SIZE_X / 2, FIELD_SIZE_Y / 2};
		// player.direction = PlayerDirection::StartPosition;

		// Init player sprite
		player.spriteHead.setTexture(game.snakeTextureHead);
		player.spriteBody.setTexture(game.snakeTextureBody);
		SetSpriteSize(player.spriteHead, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteSize(player.spriteBody, PLAYER_SIZE, PLAYER_SIZE);
		player.spriteHead.setScale(GetSpriteScale(player.spriteHead, PLAYER_SIZE, PLAYER_SIZE));
		player.spriteBody.setScale(GetSpriteScale(player.spriteBody, PLAYER_SIZE, PLAYER_SIZE));
		// game.field[game.player.position.x][game.player.position.y] = game.player.snakeLength + 1;
		
		// Очистка игрового поля
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				game.field[i][j] = FIELD_CELL_TYPE_NONE;
			}
		}

		// Инициализация игрока
		player.snakeLength = 4; // Задаем длину змейки
		player.direction = PlayerDirection::Right; // Начальное направление
		player.position = { FIELD_SIZE_X / 2, FIELD_SIZE_Y / 2 }; // Центр поля
		player.lastUpdateTime = 0.f;
		player.movementInterval = 0.2f; // Интервал движения в секундах

		// Устанавливаем змейку на поле
		for (int i = 0; i < player.snakeLength; i++)
		{
			game.field[player.position.x - i][player.position.y] = player.snakeLength - i;
		}

		AddApple(game);
	}

	void DrawPlayer(SPlayer& player, SGame& game, sf::RenderWindow& window)
	{
		// Сначала отрисовываем голову
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (game.field[i][j] == player.snakeLength) // Условие для головы
				{
					player.spriteHead.setPosition(i * CELL_SIZE, j * CELL_SIZE);
					window.draw(player.spriteHead);
				}
			}
		}

		// Затем отрисовываем тело
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (game.field[i][j] > FIELD_CELL_TYPE_NONE && game.field[i][j] < player.snakeLength)
				{
					player.spriteBody.setPosition(i * CELL_SIZE, j * CELL_SIZE);
					window.draw(player.spriteBody);
				}
			}
		}

		// const sf::Vector2f spriteScale = (GetSpriteScale(player.spriteHead, PLAYER_SIZE, PLAYER_SIZE));

		// Rotate and flip Sprite
		// switch (player.direction)
		// {
		// case PlayerDirection::Up:
		// {
		// 	player.spriteHead.setTexture(game.snakeTextureHead);
		// 	player.spriteHead.setScale(spriteScale.x, spriteScale.y);
		// 	player.spriteHead.setRotation(-90.f);
		// 	break;
		// }
		// case PlayerDirection::Right:
		// {
		// 	player.spriteHead.setTexture(game.snakeTextureHead);
		// 	player.spriteHead.setScale(spriteScale.x, spriteScale.y);
		// 	player.spriteHead.setRotation(0.f);
		// 	break;
		// }
		// case PlayerDirection::Down:
		// {
		// 	player.spriteHead.setTexture(game.snakeTextureHead);
		// 	player.spriteHead.setScale(spriteScale.x, -spriteScale.y);
		// 	player.spriteHead.setRotation(90.f);
		// 	break;
		// }
		// case PlayerDirection::Left:
		// {
		// 	player.spriteHead.setTexture(game.snakeTextureHead);
		// 	player.spriteHead.setScale(-spriteScale.x, spriteScale.y);
		// 	player.spriteHead.setRotation(0.f);
		// 	break;
		// }
		// case PlayerDirection::StartPosition:
		// 	{
		// 		player.spriteHead.setTexture(game.snakeTextureHead);
		// 		player.spriteHead.setScale(spriteScale.x, spriteScale.y);
		// 		player.spriteHead.setRotation(0.f);
		// 		break;
		// 	}
		// }
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

	void HandleInput(SPlayer& player)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (player.directionQueue.size() < 2 && player.direction != PlayerDirection::Left)
			{
				player.directionQueue.push(PlayerDirection::Right);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (player.directionQueue.size() < 2 && player.direction != PlayerDirection::Down)
			{
				player.directionQueue.push(PlayerDirection::Up);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (player.directionQueue.size() < 2 && player.direction != PlayerDirection::Right)
			{
				player.directionQueue.push(PlayerDirection::Left);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (player.directionQueue.size() < 2 && player.direction != PlayerDirection::Up)
			{
				player.directionQueue.push(PlayerDirection::Down);
			}
		}
	} ////?????
	
	void MovePlayer(SGame& game, float currentTime)
	{
		SPlayer& player = game.player;

		if (GetCurrentGameState(game) == GameState::Playing)
		{
			// Обработка очереди направлений
			if (!player.directionQueue.empty())
		 {
		     PlayerDirection nextDirection = player.directionQueue.front();
		     player.directionQueue.pop();
		      if ((player.direction == PlayerDirection::Up && nextDirection != PlayerDirection::Down) ||
		          (player.direction == PlayerDirection::Down && nextDirection != PlayerDirection::Up) ||
		           (player.direction == PlayerDirection::Left && nextDirection != PlayerDirection::Right) ||
		           (player.direction == PlayerDirection::Right && nextDirection != PlayerDirection::Left))
		      {
		           player.direction = nextDirection;
		        }
		    }
	   }

		// Движение змейки, как и раньше
	 switch (player.direction)
	 {
	 case PlayerDirection::Right:
	     if (currentTime - player.lastUpdateTime >= player.movementInterval)
	     {
		        player.position.x++;
		       if (player.position.x > FIELD_SIZE_X - 1) player.position.x = 0;
		        player.lastUpdateTime = currentTime;
		    }
		   break;
		case PlayerDirection::Up:
		    if (currentTime - player.lastUpdateTime >= player.movementInterval)
	     {
	         player.position.y--;
		     if (player.position.y < 0) player.position.y = FIELD_SIZE_Y - 1;
		       player.lastUpdateTime = currentTime;
	     }
	      break;
	   case PlayerDirection::Left:
	      if (currentTime - player.lastUpdateTime >= player.movementInterval)
	       {
	           player.position.x--;
	           if (player.position.x < 0) player.position.x = FIELD_SIZE_X - 1;
	           player.lastUpdateTime = currentTime;
	       }
	       break;
	   case PlayerDirection::Down:
	     if (currentTime - player.lastUpdateTime >= player.movementInterval)
	     {
	           player.position.y++;
	           if (player.position.y > FIELD_SIZE_Y - 1) player.position.y = 0;
	            player.lastUpdateTime = currentTime;
	       }
	        break;
	  }

    	// Проверяем, что находится на новой позиции головы ПЕРЕД обновлением поля
    	if (game.field[game.player.position.x][game.player.position.y] > FIELD_CELL_TYPE_NONE)
    	{
    		// Если змейка врезается в себя, игра окончена
    		game.gameStateStack.push_back(GameState::GameOver);
    		return;
    	}
    	else if (game.field[game.player.position.x][game.player.position.y] == FIELD_CELL_TYPE_APPLE)
    	{
    		// Увеличиваем длину змейки и добавляем новое яблоко
    		game.player.snakeLength++;
    		GrowSnake(game);
    		AddApple(game);
    		PlaySound(game.uiState, game.eatFoodBuffer);
    	}

        // Обновляем поле: добавляем новую голову
        game.field[game.player.position.x][game.player.position.y] = game.player.snakeLength + 1;

        // Уменьшаем "время жизни" каждой части тела змейки
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

        // Обновляем время последнего перемещения
        game.player.lastUpdateTime = currentTime;
    }


	void FindPlayerCollision(SGame& game)
	{
		// Find player collisions with foods
		int iterator = 0;
		// for (SFood& food : game.foodsVec)
		// {
			// if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
			// 	food.position, FOOD_SIZE))
			// {
			//
			// 	if (game.gameMode & MASK_INFINIT_FOODS)
			// 	{
			// 		food.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
			// 	}
			// 	else
			// 	{
			// 		game.foodsVec.erase(game.foodsVec.begin() + iterator);
			// 	}
			//
			// 	++game.numEatenFoods;
			//
			// 	if (game.gameMode & MASK_WITH_ACCELERATION)
			// 	{
			// 		// game.player.speed += ACCELERATION;
			// 	}
			//
			// 	PlaySound(game.uiState, game.eatFoodBuffer);
			// }
			// iterator++;
		// }

		// Find player collisions with Barriers
		// for (int i = 0; i < NUM_BARRIERS; ++i)
		// {
		// 	if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE},
		// 		game.barriersVec[i].position, { BARRIER_SIZE - 10.f, BARRIER_SIZE - 10.f}))
		// 	{
		// 		game.gameStateStack.push_back(GameState::GameOver);
		// 		game.timeSinceGameOver = 0.f;
		//
		// 		PlaySound(game.uiState, game.deathBuffer);
		// 	}
		// }

		// Check screen borders collision
		// if (CheckScreenBorders(game.player.position, PLAYER_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT))
		// {
		// 	game.gameStateStack.push_back(GameState::GameOver);
		// 	game.timeSinceGameOver = 0.f;
		//
		// 	PlaySound(game.uiState, game.deathBuffer);
		// }
	}
}
