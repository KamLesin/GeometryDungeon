#include "MadSquare.h"
#include "Bullet.h"
#include "PlayerBullet.h"
#include "GroundAttack.h"

MadSquare::MadSquare() { size = 32; };

void MadSquare::onTick()
{
	cycleProgress++;
	if (health > 0)
	{
		position = position + speed;

		if (cycleProgress % 100 == 0)
		{
			speed = Point(0, -0.03);
			if (sqrt(pow(level->player->position.x - position.x, 2) + pow(level->player->position.y - position.y, 2)) < 10)
			{
				Bullet* b = new Bullet;
				b->position = this->position;
				b->speed = Point(-0.05, 0);
				this->level->addEntity(b);
			}
		}
		if (cycleProgress % 10 == 0)
		{
			if (size == 32)
			{
				size -= 5;
			}
			else
			{
				size += 5;
			}
		}
		if (cycleProgress % 350 == 0)
		{
			GroundAttack* g = new GroundAttack;
			g->position = this->position + Point(-3, 0);
			this->level->addEntity(g);
		}
		if (cycleProgress % 200 == 0)
		{
			speed = Point(0, 0.03);
		}
	}
	if (health <= 0)
	{
		if (cycleProgress % 2 == 0)
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

void MadSquare::onHit(PlayerBullet* b)
{
	this->health -= b->damage;
	if (health > 0)
	{
		level->score += level->magnitude;
	}
}

EntityType MadSquare::getType()
{
	return EntityType::madSquare;
}
