#include "Player.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "PlayerBullet.h"
#include "Bullet.h"
#include "GroundAttack.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

// player moving using keys(arrows)
void Player::onTick()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	int directionX = 0;
	int directionY = 0;
	if (state[SDL_SCANCODE_UP])
	{
		directionY -= 1;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		directionY += 1;
	}
	if (state[SDL_SCANCODE_LEFT])
	{
		directionX -= 1;
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		directionX += 1;
	}
	if (directionY == -1 && directionX == 0)
	{
		this->angle = 0;
	}
	else if (directionY == -1 && directionX == 1)
	{
		this->angle = 45;
	}
	else if (directionY == 0 && directionX == 1)
	{
		this->angle = 90;
	}
	else if (directionY == 1 && directionX == 1)
	{
		this->angle = 135;
	}
	else if (directionY == 1 && directionX == 0)
	{
		this->angle = 180;
	}
	else if (directionY == 1 && directionX == -1)
	{
		this->angle = 225;
	}
	else if (directionY == 0 && directionX == -1)
	{
		this->angle = 270;
	}
	else if (directionY == -1 && directionX == -1)
	{
		this->angle = 315;
	}
	if (directionX != 0 || directionY != 0)
	{
		playerMoving = 1;
		Point destinationPoint;
		destinationPoint = Point(directionX * movningSpeed / sqrt(pow(directionX, 2) + pow(directionY, 2)) + position.x, directionY* movningSpeed / sqrt(pow(directionX, 2) + pow(directionY, 2)) + position.y);
		if (level->getSurfaceAt(destinationPoint + Point(0.25, 0.25)) == LevelSurface::air && level->getSurfaceAt(destinationPoint + Point(-0.25, -0.25)) == LevelSurface::air && level->getSurfaceAt(destinationPoint + Point(-0.25, 0.25)) == LevelSurface::air && level->getSurfaceAt(destinationPoint + Point(0.25, -0.25)) == LevelSurface::air)
		{
			this->position.x += directionX * movningSpeed / sqrt(pow(directionX, 2) + pow(directionY, 2));
			this->position.y += directionY * movningSpeed / sqrt(pow(directionX, 2) + pow(directionY, 2));
		}
	}
	else
	{
		playerMoving = 0;
	}
	if (remainingInvicibility)
	{
		remainingInvicibility--;
	}
}

void Player::shoot()
{
	PlayerBullet* b = new PlayerBullet;
	b->position = this->position;
	b->speed.x = sin(angle * M_PI / 180) * bulletSpeed;
	b->speed.y = -1 * cos(angle * M_PI / 180) * bulletSpeed;
	this->level->addEntity(b);
}

void Player::onHit(Bullet* b)
{
	if (!remainingInvicibility)
	{
		this->health -= b->damage;
		level->score -= 10;
		remainingInvicibility = 100;
	}
}

void Player::onHit(GroundAttack* g)
{
	if (!remainingInvicibility)
	{
		this->health -= g->damage;
		level->score -= 10;
		remainingInvicibility = 100;
	}
}
