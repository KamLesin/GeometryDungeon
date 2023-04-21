#pragma once
#include "Point.h"
class Level;
class playerBullet;
// enumeration to assign numbers to all entities
enum class EntityType
{
	bullet = 0, madSquare, madTriangle, madHexagon, playerBullet, groundAttack, bigBullet, superBullet
};
class Entity
{
public:
	// parts of every entity (exept their own specific parts)
	Point position;
	double health;
	virtual void onTick() = 0;
	virtual EntityType getType() = 0;
	Level* level;
	int size;
	int currentTick;
};
