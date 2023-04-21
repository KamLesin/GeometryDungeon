#pragma once
#include "Entity.h"
#include "Level.h"

class GroundAttack: public Entity
{
public:
	void onTick();
	EntityType getType();
	double damage = 20;
	GroundAttack();
};

