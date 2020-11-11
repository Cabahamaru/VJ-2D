#ifndef _SHOOT_INCLUDE
#define _SHOOT_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"

class Shoot
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::vec2 getPosition();
	void setPlayer(Player* p);

	void setShotdirection(glm::vec2 posPlayer);

	void setShotSpeed(int s);

	bool hitPlayer();
	

private:
	glm::ivec2 tileMapDispl, posShot;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	Player* player;
	int shootSpeed;
};
#endif // _SHOOT_INCLUDE
