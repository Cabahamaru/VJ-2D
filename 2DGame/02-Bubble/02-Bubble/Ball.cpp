#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Ball.h"
#include "Game.h"
#include "Player.h"
#include "scene.h"

#define INIT_BALL_X_TILES 10
#define INIT_BALL_Y_TILES 9

bool Start = false;
float velocity = 5;
glm::vec2 direction = (glm::vec2(0.6f, -1.f));

void Ball::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	Start = false;
	spritesheet.loadFromFile("images/ball.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1,1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(0);

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));

}


void Ball::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(!Start)
	{
		glm::ivec2 posPlayer = player->getPosition();
		posBall.x = posPlayer.x + 2;
		posBall.y = posPlayer.y - 24;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_F1) || Game::instance().getSpecialKey(GLUT_KEY_UP) || Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		Start = true;
	}
	if (Start) {

		posBall += direction * velocity;

		if (map->collisionMoveUpBall(posBall, glm::ivec2(32, 32), &posBall.y) || map->collisionMoveDownBall(posBall, glm::ivec2(32, 32), &posBall.y))
		{
			direction.y = -direction.y;
		}

		if (map->collisionMoveLeftBall(posBall, glm::ivec2(32, 32)) || map->collisionMoveRightBall(posBall, glm::ivec2(32, 32)))
		{
			direction.x = -direction.x;

		}
		CollisionWithPlayer();
		if(Game::instance().getCurrentRoom() == 4)
			CollisionWithBoss();

		if(posBall.y > 405 && Game::instance().getCurrentRoom() == 4)
		{
			direction.y = -direction.y;
		}
		if(posBall.y >405 && Game::instance().I_AM_GOD())
		{
			direction.y = -direction.y;
		}

		else if (posBall.y > 410) {
			if (Game::instance().getCurrentRoom() == 0)
			{
				Game::instance().loselife();
				Start = false;
			}
			else
			{
				Game::instance().previousRoom();
			}
		}
		else if (posBall.y < 10)
		{
			if (direction.y < 0)
			{
				Game::instance().nextRoom();
			}
				
		}
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));
	}
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
glm::vec2 Ball::getPosition()
{
	return posBall;
}



void Ball::CollisionWithPlayer() 
{
	glm::ivec2 posPlayer = player->getPosition();
	int x0Ball = posBall.x;
	int x1Ball = posBall.x + 23;

	int yBall = posBall.y + 23;

	int x0Player = posPlayer.x;
	int x1Player = posPlayer.x + 48;

	int y0Player = posPlayer.y;
	int y1Player = posPlayer.y + 8;

	if ((x1Ball > x0Player) && (x0Ball < x1Player)) 
	{
		if ((y1Player > yBall) && (yBall > y0Player) && direction.y > 0)
		{
			if(Game::instance().I_AM_GOD())
			{
				direction = glm::vec2(0.0f, -1.0f);
				posBall.y += direction.y * velocity;
			}
			else 
			{
				direction.x = ((posBall.x + 24.f) - (posPlayer.x + 48.f)) / 24.f;
				direction.y = -1.f;
				posBall.y += direction.y * velocity;
				direction = normalize(direction);
			}
		}

	}
}

void Ball::CollisionWithBoss()
{
	glm::ivec2 posBoss = boss->getPosition();
	int x0Ball = posBall.x;
	int x1Ball = posBall.x + 23;

	int yBall = posBall.y;

	int x0Boss = posBoss.x;
	int x1Boss = posBoss.x + 128;

	int y0Boss = posBoss.y + 118;
	int y1Boss = posBoss.y + 128;

	if ((x1Ball > x0Boss) && (x0Ball < x1Boss))
	{
		if ((y1Boss > yBall) && (yBall > y0Boss) && direction.y < 0)
		{
			direction.x = ((posBall.x + 64.f) - (posBoss.x + 128.f)) / 64.f;
			direction.y = -direction.y;
			posBall.y += direction.y * velocity;
			direction = normalize(direction);
			boss->bossHit();
		}

	}
}

void Ball::setPlayer(Player* p) {
	player = p;
}


void Ball::setBoss(Boss* b) {
	boss = b;
}

void Ball::resetBall()
{
	posBall = glm::vec2(INIT_BALL_X_TILES * 32, INIT_BALL_Y_TILES * 32);
	sprite->setPosition(glm::vec2(INIT_BALL_X_TILES * 32, INIT_BALL_Y_TILES * 32));
	Start = false;

}