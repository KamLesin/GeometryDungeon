#pragma once
class BigBullet;
#include "Entity.h"
#include "Level.h"
#include "View.h"
class BigBullet :public Entity
{
public:
	void onTick();
	EntityType getType();
	Point speed; // bullet speed
	double damage = 20;
};

