#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Ball.h"
#include "Game.h"
#include "Player.h"

bool Start = false;

void Ball::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	spritesheet.loadFromFile("images/tile2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(0);

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x +posBall.x), float(tileMapDispl.y + posBall.y +posBall.y)));

}


void Ball::update(int deltaTime)
{
	sprite->update(deltaTime);
	Start = true;
	/*if (Game::instance().getSpecialKey(GLUT_KEY_F1))
	{
		Start = true;
	}*/
	if (Start) {

		posBall.y -= 2;
		if (map->collisionMoveUp(posBall, glm::ivec2(32, 32), &posBall.y))
		{
			posBall.y += 2;
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));
}

void Ball::render()
{
	sprite->render();
}

void Ball::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Ball::setPosition(const glm::vec2& pos)
{
	posBall = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));
}