#include "Bullet.h"

bool hitsPlayer(Point bulletPosition, Point playerPosition)
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

// actions happening every tick
void Bullet::onTick()
{
	position = position + speed;

	//colisions
	if (level->getSurfaceAt(position) != LevelSurface::air)
	{
		this->level->removeEntity(this);
	}
	if (hitsPlayer(position, level->player->position))
	{
		level->player->onHit(this);
		this->level->removeEntity(this);
	}
}

// enum number
EntityType Bullet::getType()
{
	return EntityType::bullet;
}

