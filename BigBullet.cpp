#include "BigBullet.h"

bool hitsPlayer2(Point bulletPosition, Point playerPosition)
{
	if (bulletPosition.x < playerPosition.x + 0.15f && bulletPosition.y < playerPosition.y + 0.15f && bulletPosition.x > playerPosition.x - 0.15f && bulletPosition.y > playerPosition.y - 0.15f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// actions happening every tick
void BigBullet::onTick()
{
	position = position + speed;

	//colisions
	if (level->getSurfaceAt(position) != LevelSurface::air)
	{
		this->level->removeEntity(this);
	}
	if (hitsPlayer2(position, level->player->position))
	{
		level->player->onHit((Bullet*)this);
		this->level->removeEntity(this);
	}
}

// enum number
EntityType BigBullet::getType()
{
	return EntityType::bigBullet;
}