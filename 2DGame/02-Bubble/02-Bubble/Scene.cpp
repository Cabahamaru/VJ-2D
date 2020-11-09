#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <GL/glut.h>
#include <GL/freeglut.h>


#define SCREEN_X 32
#define SCREEN_Y 32

#define INIT_PLAYER_X_TILES 10
#define INIT_PLAYER_Y_TILES 10

#define INIT_BALL_X_TILES 10
#define INIT_BALL_Y_TILES 9


Scene::Scene()
{
	map = NULL;
	player = NULL;
	ball = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (ball != NULL)
		delete ball;
}


void Scene::init()
{
	Alarm = false;
	initShaders();

	points = 0;
	lives = 3;
	money = 0;

	soundEngine->stopAllSounds();

	glm::vec2 geom[2] = { glm::vec2(130.f, 0.f), glm::vec2(130 + 180.f, 0 + 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	stats = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	imgStats.loadFromFile("images/stats.png", TEXTURE_PIXEL_FORMAT_RGBA);
    imgStats.setMagFilter(GL_NEAREST);
	
	glm::vec2 geom2[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 0 + 480.f) };
	glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	bg = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);
	imgBg.loadFromFile("images/background.png", TEXTURE_PIXEL_FORMAT_RGBA);
	
	
	if(Game::instance().getlevel() == 0)
	{
		map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		map1 = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, -410), texProgram);
		map2 = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, -820), texProgram);
		map3 = TileMap::createTileMap("levels/level04.txt", glm::vec2(SCREEN_X, -1230), texProgram);
		map->setShaderProgram(texProgram);
		map1->setShaderProgram(texProgram);
		map2->setShaderProgram(texProgram);
		map3->setShaderProgram(texProgram);
	}

	//map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	//map1 = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, -410 ), texProgram);
	//map->setShaderProgram(texProgram);
	//map1->setShaderProgram(texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH +150 - 1), float(SCREEN_HEIGHT- 1), 0.f);
	
	ball = new Ball();
	ball->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	ball->setPosition(glm::vec2(INIT_BALL_X_TILES * map->getTileSize(), INIT_BALL_Y_TILES * map->getTileSize()));
	ball->setTileMap(map);
	ball->setPlayer(player);
	currentTime = 0.0f;

	guard = new Guard();
	guard->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	guard->setPlayer(player);

	if (!text.init("fonts/emulogic.ttf")) {
		cout << "Could not load font!!!" << endl;
	}

}


void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	ball->update(deltaTime);

	if(map->getAlarmStatus() == true)
	{
		guard->update(deltaTime);
	}
	
}


void Scene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	bg->render(imgBg);

	map->render();
	map1->render();
	map2->render();
	map3->render();

	player->render();
	ball->render();
	if (map->getAlarmStatus() == true)
	{
		guard->render();
	}
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(480.f, 0.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	stats->render(imgStats);

	std::string livesStr = std::to_string(lives);
	text.render(livesStr, glm::vec2(850, 410), 28, glm::vec4(1, 1, 1, 1));

	std::string pointsStr = std::to_string(points);
	text.render(pointsStr, glm::vec2(790, 240), 24, glm::vec4(1, 1, 1, 1));

	std::string moneyStr = std::to_string(money);
	text.render(moneyStr, glm::vec2(790, 100), 24, glm::vec4(1, 1, 1, 1));

	std::string roomStr = std::to_string(room);
	text.render(roomStr, glm::vec2(790, 600), 24, glm::vec4(1, 1, 1, 1));

}


void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

int Scene::getRoom() {
	return room;
}

void Scene::nextRoom()
{
	room++;
	if(room == 1)
	{
		map->moveTileMap(glm::vec2(32, 592));
		map1->moveTileMap(glm::vec2(32, 32));
		map2->moveTileMap(glm::vec2(32, -410));
		map3->moveTileMap(glm::vec2(32, -820));
		player->setTileMap(map1);
		ball->setTileMap(map1);
		ball->setPosition(glm::ivec2(ball->getPosition().x, 400));
	}
	if(room == 2)
	{
		map->moveTileMap(glm::vec2(32, 1184));
		map1->moveTileMap(glm::vec2(32, 592));
		map2->moveTileMap(glm::vec2(32, 32));
		map3->moveTileMap(glm::vec2(32, -410));
		player->setTileMap(map2);
		ball->setTileMap(map2);
		ball->setPosition(glm::ivec2(ball->getPosition().x, 400));
	
	}
	if (room == 3)
	{
		map->moveTileMap(glm::vec2(32, 1776));
		map1->moveTileMap(glm::vec2(32, 1184));
		map2->moveTileMap(glm::vec2(32, 592));
		map3->moveTileMap(glm::vec2(32, 32));
		player->setTileMap(map3);
		ball->setTileMap(map3);
		ball->setPosition(glm::ivec2(ball->getPosition().x, 400));
	}
}
void Scene::previousRoom()
{
	room--;
	if (room == 0)
	{
		map->moveTileMap(glm::vec2(32, 32));
		map1->moveTileMap(glm::vec2(32, -410));
		map2->moveTileMap(glm::vec2(32, -820));
		player->setTileMap(map);
		ball->setTileMap(map);
		ball->setPosition(glm::ivec2(ball->getPosition().x, -0));
	}
	if (room == 1)
	{
		map->moveTileMap(glm::vec2(32, 592));
		map1->moveTileMap(glm::vec2(32, 32));
		map2->moveTileMap(glm::vec2(32, -410));
		player->setTileMap(map1);
		ball->setTileMap(map1);
		ball->setPosition(glm::ivec2(ball->getPosition().x, -0));
	}
	if (room == 2)
	{
		map->moveTileMap(glm::vec2(32, 1184));
		map1->moveTileMap(glm::vec2(32, 592));
		map2->moveTileMap(glm::vec2(32, 32));
		map3->moveTileMap(glm::vec2(32, -410));
		player->setTileMap(map2);
		ball->setTileMap(map2);
		ball->setPosition(glm::ivec2(ball->getPosition().x, -0));
	}
	
}

void Scene::setSound(ISoundEngine* s) {
	
	soundEngine = s;
}

void Scene::loselife() {
	if (lives > 0) {
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		ball->setPosition(glm::vec2(INIT_BALL_X_TILES * map->getTileSize(), INIT_BALL_Y_TILES * map->getTileSize()));
		guard->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		map->setAlarmStatus(false);
		--lives;
	}
	else {

		Game::instance().newaction(4);
	}
}

void Scene::addpoints(int x) {
	points += x;
}

void Scene::addmoney(int x) {
	money += x;
}