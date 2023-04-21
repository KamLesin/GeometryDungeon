#pragma once
#include "Entity.h"
#include "HitableEntity.h"
class MadTriangle:public Entity, public HitableEntity
{
public:
	void onTick();
	EntityType getType();
	void onHit(PlayerBullet* b);
	int shootAfter = 100;
	double health = 30;
	MadTriangle();
};
