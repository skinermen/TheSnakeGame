#include "Player.h"
#include "Game.h"
#include <vector>

namespace ApplesGame
{
	void InitPlayer(SPlayer& player, const SGame& game)
	{
		// Init player state
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::StartPosition;

		// Init player sprite
		player.sprite.setTexture(game.playerTextureSide);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
		player.sprite.setScale(GetSpriteScale(player.sprite, PLAYER_SIZE, PLAYER_SIZE));
	}

	void DrawPlayer(SPlayer& player, SGame& game, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);

		const sf::Vector2f spriteScale = (GetSpriteScale(player.sprite, PLAYER_SIZE, PLAYER_SIZE));

		// Rotate and flip Sprite
		switch (player.direction)
		{
		case PlayerDirection::Up:
		{
			player.sprite.setTexture(game.playerTextureTop);
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Right:
		{
			player.sprite.setTexture(game.playerTextureSide);
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Down:
		{
			player.sprite.setTexture(game.playerTextureTop);
			player.sprite.setScale(spriteScale.x, spriteScale.y);
			player.sprite.setRotation(180.f);
			break;
		}
		case PlayerDirection::Left:
		{
			player.sprite.setTexture(game.playerTextureSide);
			player.sprite.setScale(-spriteScale.x, spriteScale.y);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::StartPosition:
			{
				player.sprite.setTexture(game.playerTextureSide);
				player.sprite.setScale(spriteScale.x, spriteScale.y);
				player.sprite.setRotation(0.f);
				break;
			}
		}
		window.draw(player.sprite);
	}

	void MovePlayer(SGame& game, float deltaTime)
	{
		if (GetCurrentGameState(game) == GameState::Playing)
		{
			// Handle input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				game.player.direction = PlayerDirection::Right;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				game.player.direction = PlayerDirection::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				game.player.direction = PlayerDirection::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				game.player.direction = PlayerDirection::Down;
			}
		}

		// Update player state

		switch (game.player.direction)
		{
		case PlayerDirection::Right:
		{
			game.player.position.x += game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			game.player.position.y -= game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			game.player.position.x -= game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			game.player.position.y += game.player.speed * deltaTime;
			break;
		}
		}
	}

	void FindPlayerCollision(SGame& game)
	{
		// Find player collisions with foods
		int iterator = 0;
		for (SFood& food : game.foodsVec)
		{
			if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
				food.position, FOOD_SIZE))
			{

				if (game.gameMode & MASK_INFINIT_FOODS)
				{
					food.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
				}
				else
				{
					game.foodsVec.erase(game.foodsVec.begin() + iterator);
				}

				++game.numEatenFoods;

				if (game.gameMode & MASK_WITH_ACCELERATION)
				{
					game.player.speed += ACCELERATION;
				}

				PlaySound(game.uiState, game.eatFoodBuffer);
			}
			iterator++;
		}

		// Find player collisions with Barriers
		for (int i = 0; i < NUM_BARRIERS; ++i)
		{
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE},
				game.barriersVec[i].position, { BARRIER_SIZE - 10.f, BARRIER_SIZE - 10.f}))
			{
				game.gameStateStack.push_back(GameState::GameOver);
				game.timeSinceGameOver = 0.f;

				PlaySound(game.uiState, game.deathBuffer);
			}
		}

		// Check screen borders collision
		if (CheckScreenBorders(game.player.position, PLAYER_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT))
		{
			game.gameStateStack.push_back(GameState::GameOver);
			game.timeSinceGameOver = 0.f;

			PlaySound(game.uiState, game.deathBuffer);
		}
	}
}
