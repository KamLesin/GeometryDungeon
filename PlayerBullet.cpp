#include "PlayerBullet.h"
#include "Level.h"

bool hitsEnemy(Point bulletPosition, Point enemyPosition)
{
	if (bulletPosition.x < enemyPosition.x + 0.25f && bulletPosition.y < enemyPosition.y + 0.25f && bulletPosition.x > enemyPosition.x - 0.25f && bulletPosition.y > enemyPosition.y - 0.25f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// actions happening every tick
void PlayerBullet::onTick()
{
	position = position + speed;
	//colisions
	if (level->getSurfaceAt(position) != LevelSurface::air)
	{
		this->level->removeEntity(this);
	}
	for (int i = 0; i < level->maxEntities; i++)
	{
		if (level->entities[i])
		{
			if (level->entities[i]->getType() == EntityType::madSquare || level->entities[i]->getType() == EntityType::madTriangle || level->entities[i]->getType() == EntityType::madHexagon)
			{
				if (hitsEnemy(position, level->entities[i]->position))
				{
					if (level->player->health != level->player->tempHealth)
					{
						level->magnitude = 10;
					}
					dynamic_cast<HitableEntity*>(level->entities[i])->onHit(this);
					if (level->player->health == level->player->tempHealth)
					{
						level->magnitude += 10;
					}
					this->level->removeEntity(this);
					level->player->tempHealth = level->player->health;
					break;
				}
			}
		}
	}
}

// enum number
EntityType PlayerBullet::getType()
{
	return EntityType::playerBullet;
}
