#pragma once
class Level;
#include<math.h>
#include<string.h>
#include "Point.h"
#include "Entity.h"
#include "HitableEntity.h"
#include "Player.h"
enum class LevelSurface
{
	air = 0, wall
};
class Level
{
public:
	int height = 0;
	int	width = 0;
	int maxEntities = 0;
	LevelSurface* levelPlane = NULL;
	void readFile();
	LevelSurface getSurfaceAt(int x, int y);
	LevelSurface getSurfaceAt(Point p);
	Entity** entities;
	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);
	Point start = Point(0, 0);
	Player* player;
	int amountOfEntities;
	double score = 0;
	double maximumPoints = 0;
	double magnitude = 10;
};
