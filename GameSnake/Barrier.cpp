#include "Barrier.h"
#include "Game.h"

namespace SnakeGame
{
	void InitBarrier(SBarrier& barrier, const SGame& game)
	{
		if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE + 20.f, PLAYER_SIZE + 20.f },
				barrier.position, { BARRIER_SIZE, BARRIER_SIZE })
				|| CheckScreenBorders(barrier.position, BARRIER_SIZE, SCREEN_WIDTH - 15.f, SCREEN_HEIGHT - 15.f))
		{
			barrier.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
			
		// Init barrier sprite
		barrier.sprite.setTexture(game.barrierTexture);
		SetSpriteSize(barrier.sprite, BARRIER_SIZE, BARRIER_SIZE);
		SetSpriteRelativeOrigin(barrier.sprite, 0.5f, 0.5f);
	}

	void DrawBarrier(SBarrier& barrier, sf::RenderWindow& window)
	{
		// barrier.sprite.setPosition(barrier.position.x, barrier.position.y);
		// window.draw(barrier.sprite);
	}
}
