#include "GroundAttack.h"

GroundAttack::GroundAttack() { currentTick = 0; }

bool playerCollision(Point bulletPosition, Point playerPosition)
{
	if (bulletPosition.x < playerPosition.x + 0.25f && bulletPosition.y < playerPosition.y + 0.25f && bulletPosition.x > playerPosition.x - 0.25f && bulletPosition.y > playerPosition.y - 0.25f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GroundAttack::onTick()
{
	if (level->getSurfaceAt(position) != LevelSurface::air)
	{
		this->level->removeEntity(this);
	}
	if (currentTick > 100)
	{
		if (playerCollision(position, level->player->position))
		{
			level->player->onHit(this);
			this->level->removeEntity(this);
		}
	}
	if (currentTick == 200)
	{
		this->level->removeEntity(this);
	}
	currentTick++;
}

EntityType GroundAttack::getType()
{
	return EntityType::groundAttack;
}