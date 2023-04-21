#include "Level.h"
#include "MadSquare.h"
#include "MadTriangle.h"
#include "MadHexagon.h"
#include "Bullet.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

// reading specific file of type level, every level consists of: xAxis and yAxis size, maximum amount of entities, starting point for player (x , y) and board written in numbers
// (0 - 4) depending on enum in earlier class (entity)
void Level::readFile()
{
	int c;
	FILE* file = fopen("level1.txt", "r");
	fscanf(file, "%d", &height);
	fscanf(file, "%d", &width);
	fscanf(file, "%d", &maxEntities);
	fscanf(file, "%lf", &start.x);
	fscanf(file, "%lf", &start.y);
	levelPlane = new LevelSurface [height * width];
	entities = new Entity * [maxEntities];
	amountOfEntities = 0;

	//scanning the board
	for (int i = 0; (fscanf(file, "%d", &c)) != EOF; i++)
	{
		if (c == 1)
		{
			levelPlane[i] = LevelSurface::wall;
		}
		else if (c == 0)
		{
			levelPlane[i] = LevelSurface::air;
		}
		else if (c == 2)
		{
			levelPlane[i] = LevelSurface::air;
			MadSquare* square = new MadSquare;
			entities[amountOfEntities] = square;
			square->position = Point(i % width, i / width);
			square->level = this;
			amountOfEntities++;
			maximumPoints += square->health;
		}
		else if (c == 3)
		{
			levelPlane[i] = LevelSurface::air;
			MadTriangle* triangle = new MadTriangle;
			entities[amountOfEntities] = triangle;
			triangle->position = Point(i % width, i / width);
			triangle->level = this;
			amountOfEntities++;
			maximumPoints += triangle->health;
		}
		else if (c == 4)
		{
			levelPlane[i] = LevelSurface::air;
			MadHexagon* hexagon = new MadHexagon;
			entities[amountOfEntities] = hexagon;
			hexagon->position = Point(i % width, i / width);
			hexagon->level = this;
			amountOfEntities++;
			maximumPoints += hexagon->health;
		}
	}
	fclose(file);
	for (int i = amountOfEntities; i < maxEntities; i++)
	{
		entities[i] = NULL;
	}
}

//y to x index
LevelSurface Level::getSurfaceAt(int x, int y)
{
	return levelPlane[x + y * width];
}

//determines the place of "block"
LevelSurface Level::getSurfaceAt(Point p)
{
	return getSurfaceAt(round(p.x), round(p.y));
}

//ads entity
void Level::addEntity(Entity* entity)
{
	for (int i = 0; i < maxEntities; i++)
	{
		if (entities[i] == NULL)
		{
			entities[i] = entity;
			entity->level = this;
			return;
		}
	}
}

//removes entity
void Level::removeEntity(Entity* entity)
{
	for (int i = 0; i < maxEntities; i++)
	{
		if (entities[i] == entity)
		{
			entities[i] = NULL;
			return;
		}
	}
}



