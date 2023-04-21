#pragma once
class PlayerBullet;
#include "Entity.h"
class PlayerBullet :public Entity
{
public:
	void onTick();
	EntityType getType();
	Point speed; // bullet speed
	int damage = 10;
};
