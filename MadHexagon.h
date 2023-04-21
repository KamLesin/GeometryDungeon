#pragma once
#include "Entity.h"
#include "HitableEntity.h"
class MadHexagon:public Entity, public HitableEntity
{
public:
	void onTick();
	EntityType getType();
	void onHit(PlayerBullet* b);
	int shootAfter = 50;
	double health = 60;
	MadHexagon();
};
