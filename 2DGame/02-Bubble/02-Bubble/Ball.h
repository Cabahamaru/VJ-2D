
#ifndef _BALL_INCLUDE
#define _BALL_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
class Ball
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	void CollisionWithPlayer();

private:
	glm::ivec2 tileMapDispl, posBall;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	Player* player;
};


#endif // _BALL_INCLUDE