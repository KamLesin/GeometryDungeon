#pragma once
class PlayerBullet;
class Level;
#include "Point.h"
class HitableEntity
{
public:
	virtual void onHit(PlayerBullet* b) = 0;
	Point position2;
};

