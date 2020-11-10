
#ifndef _BOSS_INCLUDE
#define _BOSS_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
class Boss
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::vec2 getPosition();
	void setPlayer(Player* p);

	void setbossdirection(int d);

private:
	glm::ivec2 tileMapDispl, posBoss;
	int startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	Player* player;
};
#endif // _BOSS_INCLUDE
