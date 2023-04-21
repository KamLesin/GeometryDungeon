#include "MadHexagon.h"
#include "Bullet.h"
#include "Level.h"
#include "PlayerBullet.h" 
#include "SuperBullet.h"

MadHexagon::MadHexagon() { size = 48; };

void MadHexagon::onTick()
{
	shootAfter--;
	if (health > 0)
	{
		if (shootAfter == 10 && sqrt(pow(level->player->position.x - position.x, 2) + pow(level->player->position.y - position.y, 2)) < 5)
		{
			Bullet* a = new Bullet;
			SuperBullet* b = new SuperBullet;
			Bullet* c = new Bullet;
			a->position = this->position;
			a->speed = Point(0.045 / sqrt(2), -0.045 / sqrt(2));
			b->position = this->position;
			b->startingPos = this->position;
			b->speed = Point(0.045, 0);
			c->position = this->position;
			c->speed = Point(0.045 / sqrt(2), 0.045 / sqrt(2));
			this->level->addEntity(a);
			this->level->addEntity(b);
			this->level->addEntity(c);
		}
		if (shootAfter == 0)
		{
			shootAfter = 50;
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

void MadHexagon::onHit(PlayerBullet* b)
{
	this->health -= b->damage;
	if (health > 0)
	{
		level->score += level->magnitude;
	}
}

EntityType MadHexagon::getType()
{
	return EntityType::madHexagon;
}
