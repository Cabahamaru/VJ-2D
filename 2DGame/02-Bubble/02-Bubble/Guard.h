
#ifndef _Guard_INCLUDE
#define _Guard_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"


class Guard
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void setPlayer(Player* p);

	void CollisionWithPlayer();

private:
	glm::ivec2 tileMapDispl, posGuard;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	Player* player;
};


#endif // _Guard_INCLUDE