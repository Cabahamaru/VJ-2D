#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"




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
	room = 0;
	initShaders();

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
		map->setShaderProgram(texProgram);
		map1->setShaderProgram(texProgram);
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
}


void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	ball->update(deltaTime);
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
	player->render();
	ball->render();

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(480.f, 0.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	stats->render(imgStats);
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

	if(room = 1)
	{
	
	}


}


