#include "Boss.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Ball.h"
#include "Game.h"
#include "Player.h"
#include "scene.h"

enum BossAnims
{
	NORMAL_1, NORMAL_2, NORMAL_3, RAGE_1, RAGE_2, RAGE_3
};


void Boss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	spritesheet.loadFromFile("images/ball.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(NORMAL_1, 8);
	sprite->setAnimationSpeed(NORMAL_2, 8);
	sprite->setAnimationSpeed(NORMAL_3, 8);

	sprite->setAnimationSpeed(RAGE_1, 8);
	sprite->setAnimationSpeed(RAGE_2, 8);
	sprite->setAnimationSpeed(RAGE_3, 8);

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBoss.x), float(tileMapDispl.y + posBoss.y)));

}

void Boss::update(int deltaTime)
{
	sprite->update(deltaTime);

	//sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBoss.x), float(tileMapDispl.y + posBoss.y)));
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