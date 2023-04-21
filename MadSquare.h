#pragma once
class MadSquare;
#include "Entity.h"
#include "HitableEntity.h"
class MadSquare:public Entity, public HitableEntity
{
public:
	void onTick();
	EntityType getType();
	void onHit(PlayerBullet* b);
	int cycleProgress = 0;
	Point speed = Point(0, 0.03);
	int health = 40;
	MadSquare();
};
