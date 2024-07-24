#include "Barrier.h"
#include "Game.h"

namespace ApplesGame
{
	void InitBarrier(SBarrier& barrier, const SGame& game)
	{
		if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE + 20.f, PLAYER_SIZE + 20.f },
				barrier.position, { BARRIER_SIZE, BARRIER_SIZE })
				|| CheckScreenBorders(barrier.position, BARRIER_SIZE, GAME_ZONE_WIDTH - 15.f, GAME_ZONE_HEIGHT - 15.f))
		{
			barrier.position = GetRandomPositionInScreen(GAME_ZONE_WIDTH, GAME_ZONE_HEIGHT);
		}
			
		// Init barrier sprite
		barrier.sprite.setTexture(game.barrierTexture);
		SetSpriteSize(barrier.sprite, BARRIER_SIZE, BARRIER_SIZE);
		SetSpriteRelativeOrigin(barrier.sprite, 0.5f, 0.5f);
	}

	void DrawBarrier(SBarrier& barrier, sf::RenderWindow& window)
	{
		barrier.sprite.setPosition(barrier.position.x, barrier.position.y);
		window.draw(barrier.sprite);
	}
}
