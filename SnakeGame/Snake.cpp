#include "Snake.h"
#include "Game.h"
#include <vector>

namespace SnakeGame
{
	void InitSnake(SSnake& snake, const SGame& game)
	{
		// Init snake sprite
		snake.spriteHead.setTexture(game.uiState.snakeTextureHead);
		snake.spriteBody.setTexture(game.uiState.snakeTextureBody);
		SetSpriteSize(snake.spriteHead, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE);
		SetSpriteSize(snake.spriteBody, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE);
		snake.spriteHead.setScale(GetSpriteScale(snake.spriteHead, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE));
		snake.spriteHead.setOrigin(SNAKE_SEGMENT_SIZE / 2.f, SNAKE_SEGMENT_SIZE / 2.f);
		snake.spriteBody.setScale(GetSpriteScale(snake.spriteBody, SNAKE_SEGMENT_SIZE, SNAKE_SEGMENT_SIZE));
		snake.spriteBody.setOrigin(SNAKE_SEGMENT_SIZE / 2.f, SNAKE_SEGMENT_SIZE / 2.f);

		// Initialization of a snake
		snake.snakeLength = 4; // We set the length of the snake
		snake.direction = SnakeDirection::Right; // Initial direction
		snake.position = { FIELD_SIZE_X / 2, FIELD_SIZE_Y / 2 }; // The center of the field
		snake.lastUpdateTime = 0.f;
	}

	void AddSnake(SGame& game)
	{
		// Install the snake on the field
		for (int i = 0; i < game.snake.snakeLength; i++)
		{
			game.field[game.snake.position.x - i][game.snake.position.y] = game.snake.snakeLength - i;
		}
	}

	void DrawSnake(SSnake& snake, const SGame& game, sf::RenderWindow& window)
	{
		// First, draw the head
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (game.field[i][j] == snake.snakeLength) // Condition for the head
				{
					snake.spriteHead.setPosition
					(i * CELL_SIZE + BORDER_SIZE + CELL_SIZE / 2.f,
					 j * CELL_SIZE + LEADERBOARD_HEIGHT + BORDER_SIZE + CELL_SIZE / 2.f);
					window.draw(snake.spriteHead);
				}
			}
		}

		// Then we draw the body
		for (int i = 0; i < FIELD_SIZE_X; i++)
		{
			for (int j = 0; j < FIELD_SIZE_Y; j++)
			{
				if (game.field[i][j] > FIELD_CELL_TYPE_NONE && game.field[i][j] < snake.snakeLength)
				{
					snake.spriteBody.setPosition
					(i * CELL_SIZE + BORDER_SIZE + CELL_SIZE / 2.f,
					 j * CELL_SIZE + LEADERBOARD_HEIGHT + BORDER_SIZE + CELL_SIZE / 2.f);
					window.draw(snake.spriteBody);
				}
			}
		}
	}

	void GrowSnake(SGame& game)
	{
		for (auto& i : game.field)
		{
			for (int& j : i)
			{
				if (j > FIELD_CELL_TYPE_NONE)
				{
					j++;
				}
			}
		}
	}

	void HandleInput(SSnake& player)
	{
		// We get the last direction that was added to the queue
		SnakeDirection currentDirection = player.direction;
		if (!player.directionQueue.empty())
		{
			currentDirection = player.directionQueue.back();
		}

		// Recording keystrokes
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

		// Limit the size of the queue if necessary
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

		if (game.isGameStarting)
		{
			if (game.gameStartTime == 0.f)
			{
				game.gameStartTime = currentTime;
			}
			if (currentTime - game.gameStartTime < PAUSE_LENGTH)
			{
				return;
			}
			game.isGameStarting = false;
		}

	    if (currentTime - player.lastUpdateTime >= player.movementInterval)
	    {
	        // Use the following direction from the queue, if there is
	        if (!player.directionQueue.empty())
	        {
	            SnakeDirection nextDirection = player.directionQueue.front();
	            player.directionQueue.pop();

	            // We check that the direction is not opposite to the current
	            if ((player.direction == SnakeDirection::Up && nextDirection != SnakeDirection::Down) ||
	                (player.direction == SnakeDirection::Down && nextDirection != SnakeDirection::Up) ||
	                (player.direction == SnakeDirection::Left && nextDirection != SnakeDirection::Right) ||
	                (player.direction == SnakeDirection::Right && nextDirection != SnakeDirection::Left))
	            {
	                player.direction = nextDirection;
	            }
	        }

	        // We move the snakes
	        switch (player.direction)
	    	{
	            case SnakeDirection::Right:
	                player.position.x++;
	                if (player.position.x >= FIELD_SIZE_X) player.position.x = 0;
	        		player.spriteHead.setRotation(0);
	                break;
	            case SnakeDirection::Up:
	                player.position.y--;
	                if (player.position.y < 0) player.position.y = FIELD_SIZE_Y - 1;
	        		player.spriteHead.setRotation(270);
	                break;
	            case SnakeDirection::Left:
	                player.position.x--;
	                if (player.position.x < 0) player.position.x = FIELD_SIZE_X - 1;
	        		player.spriteHead.setRotation(180);
	                break;
	            case SnakeDirection::Down:
	                player.position.y++;
	                if (player.position.y >= FIELD_SIZE_Y) player.position.y = 0;
	        		player.spriteHead.setRotation(90);
	                break;
		    }

	    	// Check the collision with a wall || We check the collision with ourselves
	    	if (game.field[player.position.x][player.position.y] == FIELD_CELL_TYPE_WALL ||
	    		game.field[player.position.x][player.position.y] > FIELD_CELL_TYPE_NONE)
	    	{
	    		game.timeSinceGameOver = 0.f;
	    		if (IsNewRecord(game.uiState.menuState.VLeaderboardItems, game.uiState.menuState.numScores))
	    		{
	    			SwitchGameState(game, GameState::ConfirmationMenu);
	    		}
			    else
			    {
				    SwitchGameState(game, GameState::GameOver);
			    }
	    		PlaySound(game.uiState, game.uiState.deathBuffer);
	    		return;
	    	}

	        // Check if the snake has eaten an apple
	        if (game.field[player.position.x][player.position.y] == FIELD_CELL_TYPE_APPLE)
	        {
	            player.snakeLength++;
	        	game.numEatenApples += 1;
	        	game.uiState.menuState.numScores += game.scoresPerApple;
	            GrowSnake(game);
	            AddApple(game);
	            PlaySound(game.uiState, game.uiState.eatAppleBuffer);
	        }

	        // We update the game field
	        game.field[player.position.x][player.position.y] = player.snakeLength + 1;

	        // Reduce the life of the body parts
	        for (auto& i : game.field)
	        {
	            for (int& j : i)
	            {
	                if (j > FIELD_CELL_TYPE_NONE)
	                {
		                j--;
	                }
	            }
	        }

	        // We update the time of the last update
	        player.lastUpdateTime = currentTime;
	    }
	}
}
