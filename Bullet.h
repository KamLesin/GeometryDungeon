#pragma once
class Bullet;
#include "Entity.h"
#include "Level.h"
#include "View.h"
class Bullet :public Entity
{
public:
	void onTick();
	EntityType getType();
	Point speed; // bullet speed
	double damage = 10;
};
