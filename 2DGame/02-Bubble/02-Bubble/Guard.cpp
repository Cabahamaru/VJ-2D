#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Ball.h"
#include "Game.h"
#include "Player.h"
#include "Guard.h"

void Guard::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/guard.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(0);

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	posGuard.x = 32;
	posGuard.y = 400;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGuard.x), float(tileMapDispl.y + posGuard.y)));
}

void Guard::update(int deltaTime)
{
	sprite->update(deltaTime);
	glm::ivec2 posPlayer = player->getPosition();

	if (posPlayer.x > posGuard.x)
	{
		posGuard.x += 1;
	}
	if (posPlayer.x < posGuard.x)
	{
		posGuard.x -= 1;
	}
	if (posPlayer.y > posGuard.y)
	{
		posGuard.y += 1;
	}
	if (posPlayer.y < posGuard.y)
	{
		posGuard.y -= 1;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGuard.x), float(tileMapDispl.y + posGuard.y)));

}

void Guard::render()
{
	sprite->render();
}

void Guard::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Guard::setPosition(const glm::vec2& pos)
{
	posGuard = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGuard.x), float(tileMapDispl.y + posGuard.y)));
}

void Guard::setPlayer(Player* p) {
	player = p;
}