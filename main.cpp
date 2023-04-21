#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Player.h"
#include "Level.h"
#include "View.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Renderer* renderer, int x, int y, const char* text, SDL_Texture* tex)
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text)
	{
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_RenderCopy(renderer, tex, &s, &d);
		x += 8;
		text++;
	}
}


// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) 
{
	SDL_Rect dest;
	dest.x = x - sprite->w /2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
}

void RenderTexture(SDL_Renderer* renderer, SDL_Texture* tex, double angle, Point p, int w, int h) 
{
	SDL_Rect dest;
	dest.x = p.x - w / 2;
	dest.y = p.y - h / 2;
	dest.w = w;
	dest.h = h;
	SDL_RenderCopyEx(renderer, tex, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}

// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) 
{
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
}

// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) 
{
	for(int i = 0; i < l; i++) 
	{
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	}
}

// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) 
{
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
}

SDL_Texture* readTexture(char* file, SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP(file);
	if (surface == NULL)
	{
		printf("SDL_LoadBMP error: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}
	return SDL_CreateTextureFromSurface(renderer, surface);
}

//determines the grade for score
SDL_Texture* whatGrade(double score, double maxScore, SDL_Texture* gradeS, SDL_Texture* gradeA, SDL_Texture* gradeB, SDL_Texture* gradeC, SDL_Texture* gradeD)
{
	double division = score / maxScore;
	if (division >= 1)
	{
		return gradeS;
	}
	else if (division >= 0.75)
	{
		return gradeA;
	}
	else if (division >= 0.50)
	{
		return gradeB;
	}
	else if (division >= 0.25)
	{
		return gradeC;
	}
	else
	{
		return gradeD;
	}
}

//shows the player movement by spinning specialObject
int playerMovement(int isPMoving, int* angle)
{
	if (isPMoving == 1)
	{
		*angle += 5;
		int temp = *angle;
		return temp;
	}
}

int main(int argc, char** argv) {
	int t1, t2, quit, frames, rc, menu;
	double delta, worldTime, fpsTimer, fps;
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Player player1;

	// changable parameters
	t1 = SDL_GetTicks();
	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	menu = 1;
	int worldTicks = 0;
	int spin = 0;
	int movingEnemy = 32;
	int lastTick = 0;
	int tickStamp = 0;
	Level level1;
	level1.readFile();
	player1.position = level1.start;
	View view1;
	view1.center = Point(0, 0);
	view1.scale = 64;
	view1.height = SCREEN_HEIGHT;
	view1.width = SCREEN_WIDTH;
	player1.level = &level1;
	char text[128];
	char score[32];
	level1.player = &player1;
	Point healthBar = Point(SCREEN_WIDTH - 160, SCREEN_HEIGHT - 80);
	Point healthState = Point(SCREEN_WIDTH - 60 + player1.health, SCREEN_HEIGHT - 80);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (rc != 0) 
	{
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 70, 0, 255, 0);
	SDL_SetWindowTitle(window, "GeometryDungeon");

	//all textures
	SDL_Texture* playerTexture = readTexture("./player1.bmp", renderer);
	SDL_Texture* wallTexture = readTexture("./wall.bmp", renderer);
	SDL_Texture* airTexture = readTexture("./air.bmp", renderer);
	SDL_Texture* madSquareTexture = readTexture("./madSquare.bmp", renderer);
	SDL_Texture* madTriangleTexture = readTexture("./madTriangle.bmp", renderer);
	SDL_Texture* madHexagonTexture = readTexture("./madHexagon.bmp", renderer);
	SDL_Texture* enemyBulletTexture = readTexture("./enemyBullet.bmp", renderer);
	SDL_Texture* charset = readTexture("./cs8x8.bmp", renderer);
	SDL_Texture* playerBulletTexture = readTexture("./playerBullet.bmp", renderer);
	SDL_Texture* healthBarFrame = readTexture("./healthBar.bmp", renderer);
	SDL_Texture* currentHealth = readTexture("./health.bmp", renderer);
	SDL_Texture* gameOver = readTexture("./game_over.bmp", renderer);
	SDL_Texture* gradeS = readTexture("./grade_S.bmp", renderer);
	SDL_Texture* gradeA = readTexture("./grade_A.bmp", renderer);
	SDL_Texture* gradeB = readTexture("./grade_B.bmp", renderer);
	SDL_Texture* gradeC = readTexture("./grade_C.bmp", renderer);
	SDL_Texture* gradeD = readTexture("./grade_D.bmp", renderer);
	SDL_Texture* playerMoving = readTexture("./playerMovement.bmp", renderer);
	SDL_Texture* youWon = readTexture("./youWon.bmp", renderer);
	SDL_Texture* groundAttack = readTexture("./groundAttack.bmp", renderer);

	SDL_Texture* currentGrade;
	SDL_Texture* lastGrade = gradeD;

	while (!quit)
	{
		t2 = SDL_GetTicks();
		delta = (t2 - t1) * 0.001;
		t1 = t2;
		worldTime += delta;
		fpsTimer += delta;
		if (fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		}
		if (level1.amountOfEntities == 0)
		{
			RenderTexture(renderer, whatGrade(level1.score, level1.maximumPoints, gradeS, gradeA, gradeB, gradeC, gradeD), 0, Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100), 64, 64);
			RenderTexture(renderer, youWon, 0, Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 256, 128);
			sprintf(text, "Press \"Esc\" to quit or Press \"n\" to start a new game");
			DrawString(renderer, SCREEN_WIDTH / 2 - 196, (SCREEN_HEIGHT / 2) + 80, text, charset);
			SDL_RenderPresent(renderer);
		}
		else if (player1.health > 0)
		{
			if (t2 > 10 + lastTick)
			{
				worldTicks++;
				player1.onTick();
				for (int entityNumber = 0; entityNumber < level1.maxEntities; entityNumber++)
				{
					Entity* entity = level1.entities[entityNumber];
					if (entity == NULL)
					{
						continue;
					}
					entity->onTick();
				}
				lastTick = t2;
			}
			else
			{
				continue;
			}
			
			view1.center = player1.position;
			SDL_RenderClear(renderer);

			//rendering level
			for (int y = 0; y < level1.height; y++)
			{
				for (int x = 0; x < level1.width; x++)
				{
					switch (level1.getSurfaceAt(x, y))
					{
					case LevelSurface::air:
						RenderTexture(renderer, airTexture, 0, view1.worldToScreen(Point(x, y)), 64, 64);
						break;
					case LevelSurface::wall:
						RenderTexture(renderer, wallTexture, 0, view1.worldToScreen(Point(x, y)), 64, 64);
						break;
					}
				}
			}
		
			// rendering player
			if (player1.remainingInvicibility)
			{
				if (player1.remainingInvicibility % 20 < 10)
				{
					RenderTexture(renderer, playerTexture, player1.angle, view1.worldToScreen(player1.position), 29, 38);
					RenderTexture(renderer, playerMoving, playerMovement(player1.playerMoving, &spin), view1.worldToScreen(player1.position), 18, 18);
				}
			}
			else
			{
				RenderTexture(renderer, playerTexture, player1.angle, view1.worldToScreen(player1.position), 29, 38);
				RenderTexture(renderer, playerMoving, playerMovement(player1.playerMoving, &spin), view1.worldToScreen(player1.position), 18, 18);
			}
			// rendering entities
			for (int entityNumber = 0; entityNumber < level1.maxEntities; entityNumber++)
			{
				Entity* entity = level1.entities[entityNumber];
				if (entity == NULL)
				{
					continue;
				}
				switch (entity->getType())
				{
				case EntityType::bullet:
					RenderTexture(renderer, enemyBulletTexture, 0, view1.worldToScreen(entity->position), 8, 8);
					break;
				case EntityType::bigBullet:
					RenderTexture(renderer, enemyBulletTexture, 0, view1.worldToScreen(entity->position), 16, 16);
					break;
				case EntityType::superBullet:
					RenderTexture(renderer, enemyBulletTexture, 0, view1.worldToScreen(entity->position), 24, 24);
					break;
				case EntityType::madSquare:
					RenderTexture(renderer, madSquareTexture, 0, view1.worldToScreen(entity->position), entity->size, entity->size);
					break;
				case EntityType::madTriangle:
					RenderTexture(renderer, madTriangleTexture, 0, view1.worldToScreen(entity->position), entity->size, entity->size);
					break;
				case EntityType::madHexagon:
					RenderTexture(renderer, madHexagonTexture, 0, view1.worldToScreen(entity->position), entity->size, entity->size);
					break;
				case EntityType::playerBullet:
					RenderTexture(renderer, playerBulletTexture, 0, view1.worldToScreen(entity->position), 8, 8);
					break;
				case EntityType::groundAttack:
					if (entity->currentTick < 90)
					{
						if (entity->currentTick % 30 < 15)
						{
							RenderTexture(renderer, groundAttack, 0, view1.worldToScreen(entity->position), 24, 24);
						}
					}
					else
					{
						RenderTexture(renderer, groundAttack, 0, view1.worldToScreen(entity->position), 24, 24);
					}
					break;
				default:
					break;
				}

			}
			// rendering healthBar
			double moveHealthBar = 0.5 * (100 - player1.health);
			Point healthState = Point(480 - moveHealthBar, 400);
			RenderTexture(renderer, healthBarFrame, 0, healthBar, 112, 30);
			RenderTexture(renderer, currentHealth, 0, healthState, player1.health, 17);

			sprintf(text, "time elapsed: %.1lf s | %.0lf frames / s | X: %lf Y: %lf", worldTime, fps, player1.position.x, player1.position.y);
			sprintf(score, "SCORE: %.0lf", level1.score);
			DrawString(renderer, 0, 0, text, charset);

			//rendering proper grade
			currentGrade = whatGrade(level1.score, level1.maximumPoints, gradeS, gradeA, gradeB, gradeC, gradeD);
			if (currentGrade != lastGrade)
			{
				tickStamp = worldTicks;
			}
			if (worldTicks - tickStamp < 100)
			{
				RenderTexture(renderer, lastGrade, 0, Point(40, 350), 64 * (100 - (worldTicks - tickStamp)) / 100, 64 * (100 - (worldTicks - tickStamp)) / 100);
			}
			else
			{
				RenderTexture(renderer, currentGrade, 0, Point(40, 350), 64, 64);
			}
			lastGrade = currentGrade;

			//score in number
			DrawString(renderer, 10, 400, score, charset);
			SDL_RenderPresent(renderer);
		}
		else
		{
			RenderTexture(renderer, whatGrade(level1.score, level1.maximumPoints, gradeS, gradeA, gradeB, gradeC, gradeD), 0, Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100), 64, 64);
			RenderTexture(renderer, gameOver, 0, Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 256, 256);
			sprintf(text, "Press \"Esc\" to quit or Press \"n\" to start a new game");
			DrawString(renderer, SCREEN_WIDTH / 2 - 196, (SCREEN_HEIGHT / 2) + 80, text, charset);
			SDL_RenderPresent(renderer);
		}
		//pressing buttons (only for action buttons, arrows movement is implemented in other way)
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = 1;
					}
					if (event.key.keysym.sym == SDLK_n) 
					{
						level1.readFile();
						player1.position = level1.start;
						player1.health = 100;
						worldTime = 0;
						level1.score = 0;
					}
					if (event.key.keysym.sym == SDLK_SPACE)
					{
						player1.shoot();
					}
					if (event.key.keysym.sym == SDLK_m)
					{
						menu = 1;
					}
					break;
				case SDL_KEYUP:

					break;
				case SDL_QUIT:
					quit = 1;
					break;
				}
			}
		frames++;
		}
	// freeing all surfaces
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
	}

