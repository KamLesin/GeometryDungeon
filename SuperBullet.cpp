#include "SuperBullet.h"
#include "Bullet.h"

bool hitsPlayer3(Point bulletPosition, Point playerPosition)
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
void SuperBullet::onTick()
{
	position = position + speed;
	if (fabs(position.x - startingPos.x) + fabs(position.y - startingPos.y) >= 3)
	{
		blowUp();
		this->level->removeEntity(this);
	}
	//colisions
	if (level->getSurfaceAt(position) != LevelSurface::air)
	{
		this->level->removeEntity(this);
	}
	if (hitsPlayer3(position, level->player->position))
	{
		level->player->onHit((Bullet*)this);
		this->level->removeEntity(this);
	}
}

void SuperBullet::blowUp()
{
	Bullet* a = new Bullet;
	Bullet* b = new Bullet;
	Bullet* c = new Bullet;
	Bullet* d = new Bullet;
	Bullet* e = new Bullet;
	Bullet* f = new Bullet;
	Bullet* g = new Bullet;
	Bullet* h = new Bullet;
	a->position = this->position;
	b->position = this->position;
	c->position = this->position;
	d->position = this->position;
	e->position = this->position;
	f->position = this->position;
	g->position = this->position;
	h->position = this->position;
	a->speed = Point(0, -0.02);
	b->speed = Point(0.02 / sqrt(2), -0.02 / sqrt(2));
	c->speed = Point(0.02, 0);
	d->speed = Point(0.02 / sqrt(2), 0.02 / sqrt(2));
	e->speed = Point(0, 0.02);
	f->speed = Point(-0.02 / sqrt(2), 0.02 / sqrt(2));
	g->speed = Point(-0.02, 0);
	h->speed = Point(-0.02 / sqrt(2), -0.02 / sqrt(2));
	this->level->addEntity(a);
	this->level->addEntity(b);
	this->level->addEntity(c);
	this->level->addEntity(d);
	this->level->addEntity(e);
	this->level->addEntity(f);
	this->level->addEntity(g);
	this->level->addEntity(h);
}

// enum number
EntityType SuperBullet::getType()
{
	return EntityType::superBullet;
}