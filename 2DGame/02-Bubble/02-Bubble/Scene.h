#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Ball.h"
#include "Texture.h"
#include "TexturedQuad.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	int getRoom();

private:
	void initShaders();

private:
	TileMap *map;
	TileMap* map1;
	TileMap* map2;
	TileMap* map3;
	Player *player;
	Ball *ball;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	TexturedQuad* stats, *bg;
	Texture imgStats, imgBg;

	int room;

};


#endif // _SCENE_INCLUDE

