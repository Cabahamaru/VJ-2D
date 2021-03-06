
#ifndef _BALL_INCLUDE
#define _BALL_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Boss.h"
#include "Player.h"
class Ball
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::vec2 getPosition();
	void setPlayer(Player *p);

	void setBoss(Boss* b);

	void resetBall();

	void CollisionWithPlayer();

	void CollisionWithBoss();

private:
	glm::ivec2 tileMapDispl, posBall;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	Player* player;
	Boss* boss;
};


#endif // _BALL_INCLUDE