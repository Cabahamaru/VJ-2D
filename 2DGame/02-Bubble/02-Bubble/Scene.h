#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Ball.h"
#include "Boss.h"
#include "Guard.h"
#include "Shoot.h"
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
	void previousRoom();
	void loselife();
	void addpoints(int x);
	void addmoney(int x);
	int getlives();
	int getpoints();
	int getmoney();
	void GOD_get_key();
	void GOD_break_bricks();
	void GOD_get_money();

	void nextLevel();

	void GOD_next_room();

	void GOD_previous_room();

private:
	void initShaders();

private:
	TileMap *map;
	TileMap* map1;
	TileMap* map2;
	TileMap* map3;
	TileMap* map4boss;
	Player *player;
	Ball *ball;
	Guard* guard;
	Boss* boss;
	Shoot* shot;
	ShaderProgram texProgram;
	ISoundEngine* soundEngine;
	float currentTime;
	glm::mat4 projection;
	TexturedQuad* stats, * bg, * sc_bg, * nextlevel1 , *nextlevel2;
	Texture imgStats, imgBg, imgScBg, imgnextlevel1 , imgnextlevel2;
	bool Alarm;
	unsigned char* strpoints;

	int room = 0;
	int money = 0;
	int lives = 4;
	int points = 0;
	bool leveltransition = false;
	Text text;

};


#endif // _SCENE_INCLUDE

