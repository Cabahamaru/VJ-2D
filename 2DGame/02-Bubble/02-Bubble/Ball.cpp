#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Ball.h"
#include "Game.h"
#include "Player.h"
#include "scene.h"

bool Start = false;
float velocity = 5;
glm::vec2 direction = (glm::vec2(0.6f, -1.f));

void Ball::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

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

		else if (map->collisionMoveLeftBall(posBall, glm::ivec2(32, 32)) || map->collisionMoveRightBall(posBall, glm::ivec2(32, 32)))
		{
			direction.x = -direction.x;

		}
		else CollisionWithPlayer();

		if (posBall.y > 425) {
			if (Game::instance().getCurrentRoom() == 0)
			{
				if (Game::instance().getlevel() == 0) Game::instance().loselife();
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
			direction.x = ((posBall.x + 24.f) - (posPlayer.x + 48.f)) / 24.f;
			direction.y = -1.f;
			posBall.y += direction.y * velocity;
			direction = normalize(direction);

		}

	}
}

void Ball::setPlayer(Player* p) {
	player = p;
}