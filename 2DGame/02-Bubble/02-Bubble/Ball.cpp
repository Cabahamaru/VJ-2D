#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Ball.h"
#include "Game.h"
#include "Player.h"

bool Start = false;
int yaux = -2;
int xaux = -2;

float velocity = 4;
glm::vec2 direction = (glm::vec2(0.6f, -1.f));

void Ball::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	spritesheet.loadFromFile("images/ball.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1,1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(0);

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));

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

		posBall += direction * velocity;

		if (map->collisionMoveUpBall(posBall, glm::ivec2(32, 32), &posBall.y) || map->collisionMoveDownBall(posBall, glm::ivec2(32, 32), &posBall.y))
		{
			direction.y = -direction.y;
		}
		else if (map->collisionMoveLeftBall(posBall, glm::ivec2(32, 32)) || map->collisionMoveRightBall(posBall, glm::ivec2(32, 32)))
		{
			direction.x = -direction.x;

		}
		else CollisionWithPlayer();


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

void Ball::CollisionWithPlayer() 
{
	glm::ivec2 posPlayer = player->getPosition();
	int x0Ball = posBall.x;
	int x1Ball = posBall.x + 32;

	int yBall = posBall.y + 16;

	int x0Player = posPlayer.x;
	int x1Player = posPlayer.x + 32;

	int y0Player = posPlayer.y;
	int y1Player = posPlayer.y + 16;

	if ((x1Ball > x0Player) && (x0Ball < x1Player)) 
	{
		if ((y1Player > yBall) && (yBall > y0Player)) 
		{
			direction.x = ((posBall.x + 12.f) - (posPlayer.x + 24.f)) / 12.f;
			direction.y = -1.f;
			posBall.y += direction.y * velocity;
			direction = normalize(direction);
		}

	}
}

void Ball::setPlayer(Player* p) {
	player = p;
}