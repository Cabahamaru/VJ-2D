#include "Boss.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Ball.h"
#include "Game.h"
#include "Player.h"
#include "scene.h"


int counter = 0;
bool statenormal = true;
bool staterage = false;
int bossdirection = 2;

int current = 0;
enum BossAnims
{
	NORMAL_1, NORMAL_2, NORMAL_3, RAGE_1, RAGE_2, RAGE_3
};


void Boss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	spritesheet.loadFromFile("images/boss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(128, 128), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(NORMAL_1, 8);
	sprite->addKeyframe(NORMAL_1, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(NORMAL_2, 8);
	sprite->addKeyframe(NORMAL_2, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(NORMAL_3, 8);
	sprite->addKeyframe(NORMAL_3, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(RAGE_1, 8);
	sprite->addKeyframe(RAGE_1, glm::vec2(0.0f, 0.5f));

	sprite->setAnimationSpeed(RAGE_2, 8);
	sprite->addKeyframe(RAGE_2, glm::vec2(0.25f, 0.5f));

	sprite->setAnimationSpeed(RAGE_3, 8);
	sprite->addKeyframe(RAGE_3, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBoss.x), float(tileMapDispl.y + posBoss.y)));

}

void Boss::update(int deltaTime)
{
	sprite->update(deltaTime);
	++counter;
	if (counter > 30) {

		if(statenormal)
		{
			if(current == 0)
			{
				sprite->changeAnimation(1);
				current++;
			}
			else if(current == 1)
			{
				sprite->changeAnimation(2);
				current++;
			}
			else if (current == 2)
			{
				sprite->changeAnimation(0);
				current = 0;
			}
		}
		else if (staterage)
		{
			if (current == 3)
			{
				sprite->changeAnimation(4);
				current++;
			}
			else if (current == 4)
			{
				sprite->changeAnimation(5);
				current++;
			}
			else if (current == 5)
			{
				sprite->changeAnimation(3);
				current = 3;
			}
		}
		counter = 0;
	}
	posBoss.x += bossdirection;
	if(map->collisionMoveLeft(posBoss, glm::ivec2(128, 128)))
	{
		bossdirection = -bossdirection;
	}
	if (map->collisionMoveRight(posBoss, glm::ivec2(128, 128)))
	{
		bossdirection = -bossdirection;
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBoss.x), float(tileMapDispl.y + posBoss.y)));
}

void Boss::render()
{
	sprite->render();
}

void Boss::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Boss::setPosition(const glm::vec2& pos)
{
	posBoss = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBoss.x), float(tileMapDispl.y + posBoss.y)));
}
glm::vec2 Boss::getPosition()
{
	return posBoss;
}

void Boss::setPlayer(Player* p) {
	player = p;
}