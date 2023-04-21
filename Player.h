#pragma once
#include<string.h>
#include "Point.h"
class Level;
class Bullet;
class GroundAttack;

class Player
{
public:
	Point position;
	double movningSpeed = 0.04;
	double health = 100;
	double tempHealth = health;
	double bulletSpeed = 0.07;
	double angle = 0;
	Level* level;
	void onTick();
	void shoot();
	void onHit(Bullet* b);
	void onHit(GroundAttack* g);
	int remainingInvicibility = 0;
	int playerMoving = 0;
};
