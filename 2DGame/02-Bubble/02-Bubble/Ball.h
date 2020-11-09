
#ifndef _BALL_INCLUDE
#define _BALL_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
//#include "Scene.h"
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

	void CollisionWithPlayer();

private:
	glm::ivec2 tileMapDispl, posBall;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	Player* player;
	//Scene scene;
};


#endif // _BALL_INCLUDE