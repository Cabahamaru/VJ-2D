#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Ball.h"
#include "Guard.h"
#include "Text.h"
#include "Texture.h"
#include "TexturedQuad.h"
#include <irrKlang.h>


using namespace irrklang;

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
	void setSound(ISoundEngine* s);

	void nextRoom();

private:
	void initShaders();

private:
	TileMap *map;
	TileMap* map1;
	TileMap* map2;
	TileMap* map3;
	Player *player;
	Ball *ball;
	Guard* guard;
	ShaderProgram texProgram;
	ISoundEngine* soundEngine;
	float currentTime;
	glm::mat4 projection;
	//Text text;
	TexturedQuad* stats, *bg;
	Texture imgStats, imgBg;
	bool Alarm;
	unsigned char* strpoints;

	int room;
	Text* text;

};


#endif // _SCENE_INCLUDE

