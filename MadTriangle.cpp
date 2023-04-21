#include "MadTriangle.h"
#include "Bullet.h"
#include "Level.h"
#include "PlayerBullet.h"
#include "BigBullet.h"

MadTriangle::MadTriangle() { size = 32; };

void MadTriangle::onTick()
{
	shootAfter--;
	if (health > 0)
	{
		if ((shootAfter == 10 || shootAfter == 20) && sqrt(pow(level->player->position.x - position.x, 2) + pow(level->player->position.y - position.y, 2)) < 8)
		{
			Bullet* b = new Bullet;
			b->position = this->position;
			b->speed = Point(0, -0.055);
			this->level->addEntity(b);
		}
		else if(shootAfter == 30 && sqrt(pow(level->player->position.x - position.x, 2) + pow(level->player->position.y - position.y, 2)) < 8)
		{
			BigBullet* b = new BigBullet;
			b->position = this->position;
			b->speed = Point(0, -0.055);
			this->level->addEntity(b);
		}
		if (shootAfter == 0)
		{
			shootAfter = 100;
		}
	}
	if (health <= 0)
	{
		if (shootAfter % 2 == 0)
		{
			size--;
		}
		if (size == 0)
		{
			this->level->removeEntity(this);
			level->amountOfEntities -= 1;
		}
	}
}
void MadTriangle::onHit(PlayerBullet* b)
{
	this->health -= b->damage;
	if (health > 0)
	{
		level->score += level->magnitude;
	}
}
EntityType MadTriangle::getType()
{
	return EntityType::madTriangle;
}
