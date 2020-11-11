#include "Shoot.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Ball.h"
#include "Game.h"
#include "Player.h"
#include "scene.h"


int counterShot = 0;
int currentShot = 0;
glm::vec2 shotdirection = (glm::vec2(0.0f, 0.0f));

enum ShotAnims
{
	SHOT_1, SHOT_2, SHOT_3, SHOT_4, SHOT_5, SHOT_6, SHOT_7, SHOT_8
};

void Shoot::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	shootSpeed = 0;
	spritesheet.loadFromFile("images/shot.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(0.125,1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(SHOT_1, 8);
	sprite->addKeyframe(SHOT_1, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(SHOT_2, 8);
	sprite->addKeyframe(SHOT_2, glm::vec2(0.125f, 0.f));

	sprite->setAnimationSpeed(SHOT_3, 8);
	sprite->addKeyframe(SHOT_3, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(SHOT_4, 8);
	sprite->addKeyframe(SHOT_4, glm::vec2(0.375f, 0.0f));

	sprite->setAnimationSpeed(SHOT_5, 8);
	sprite->addKeyframe(SHOT_5, glm::vec2(0.5f, 0.0f));

	sprite->setAnimationSpeed(SHOT_6, 8);
	sprite->addKeyframe(SHOT_6, glm::vec2(0.625f, 0.0f));

	sprite->setAnimationSpeed(SHOT_7, 8);
	sprite->addKeyframe(SHOT_7, glm::vec2(0.75f, 0.0f));

	sprite->setAnimationSpeed(SHOT_8, 8);
	sprite->addKeyframe(SHOT_8, glm::vec2(0.875f, 0.0f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posShot.x), float(tileMapDispl.y + posShot.y)));
}

void Shoot::update(int deltaTime)
{
	shootSpeed = 1;
	sprite->update(deltaTime);
	++counterShot;
	if (counterShot > 30) {
			if (currentShot == 0)
			{
				sprite->changeAnimation(1);
				currentShot++;
			}
			else if (currentShot == 1)
			{
				sprite->changeAnimation(2);
				currentShot++;
			}
			else if (currentShot == 2)
			{
				sprite->changeAnimation(3);
				currentShot++;
			}
			else if (currentShot == 3)
			{
				sprite->changeAnimation(0);
				currentShot = 0;
			}
		counterShot = 0;
	}
	posShot.x += shotdirection.x * shootSpeed;
	posShot.y += shotdirection.y * shootSpeed;
	if(hitPlayer())
	{
		shootSpeed = 0;
		sprite->changeAnimation(4);
		sprite->changeAnimation(5);
		sprite->changeAnimation(6);
		sprite->changeAnimation(7);
		posShot.x = -200;
		Game::instance().loselife();
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posShot.x), float(tileMapDispl.y + posShot.y)));
}

void Shoot::render()
{
	sprite->render();
}

void Shoot::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Shoot::setPosition(const glm::vec2& pos)
{
	posShot = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posShot.x), float(tileMapDispl.y + posShot.y)));
}
glm::vec2 Shoot::getPosition()
{
	return posShot;
}

void Shoot::setPlayer(Player* p) {
	player = p;
}

void Shoot::setShotdirection(glm::vec2 posPlayer)
{
	shotdirection.x = (posPlayer.x -posShot.x)/ (posPlayer.x - posShot.x);
	shotdirection.y = (posPlayer.y -posShot.y)/ (posPlayer.y - posShot.y);
	if (posPlayer.x < posShot.x)
		shotdirection.x = -shotdirection.x;
}
void Shoot::setShotSpeed(int s)
{
	shootSpeed = 1;
}

bool Shoot::hitPlayer()
{
	glm::ivec2 posPlayer = player->getPosition();
	int x0Shot = posShot.x;
	int x1Shot = posShot.x + 23;

	int y0Shot = posShot.y;
	int y1Shot = posShot.y + 23;

	int x0Player = posPlayer.x;
	int x1Player = posPlayer.x + 47;

	int y0Player = posPlayer.y;
	int y1Player = posPlayer.y + 32;
	if ((x1Shot > x0Player) && (x0Shot < x1Player)) 
	{
		if ((y1Player > y0Shot) && (y1Shot > y0Player)) 
		{
			return true;
		}
	}
	return false;
}
