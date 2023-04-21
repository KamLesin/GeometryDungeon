#pragma once
class SuperBullet;
#include "Entity.h"
#include "Level.h"
#include "View.h"

class SuperBullet :public Entity
{
public:
	void onTick();
	EntityType getType();
	void blowUp();
	Point speed; // bullet speed
	Point startingPos;
	double damage = 20;
};