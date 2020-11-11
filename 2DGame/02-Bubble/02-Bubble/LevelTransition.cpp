#include "LevelTransition.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <GL/glut.h>
#include "Scene.h"

#define SCREEN_X 32
#define SCREEN_Y 32

int leveltransitioncontador = 0;

LevelTransition::LevelTransition()
{

}

LevelTransition::~LevelTransition()
{

}

void LevelTransition::init()
{
	initShaders();
	currentTime = 0.0f;
	accion = 0;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	fondo = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	imgFondo.loadFromFile("images/next_level1.png", TEXTURE_PIXEL_FORMAT_RGBA);

	glm::vec2 geom2[2] = { glm::vec2(475.f, 0.f), glm::vec2(475.f + 180.f, 0 + 480.f) };
	glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	stats = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);
	imgStats.loadFromFile("images/stats.png", TEXTURE_PIXEL_FORMAT_RGBA);
	imgStats.setMagFilter(GL_NEAREST);
	/*glm::vec2 geom2[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 480.f) };
	glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	fondo2 = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);
	imgFondo2.loadFromFile("images/next_level2.png", TEXTURE_PIXEL_FORMAT_RGBA);*/
	cur1 = true;

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	if (!text.init("fonts/ARCADEPI.ttf")) {
		cout << "Could not load font!!!" << endl;
	}

}

void LevelTransition::update(int deltaTime)
{
	currentTime += deltaTime;
	++leveltransitioncontador;
	if (leveltransitioncontador > 30) {
		if (cur1) {
			imgFondo.loadFromFile("images/next_level2.png", TEXTURE_PIXEL_FORMAT_RGBA);
			cur1 = false;
		}
		else {
			imgFondo.loadFromFile("images/next_level1.png", TEXTURE_PIXEL_FORMAT_RGBA);
			cur1 = true;
		}
		leveltransitioncontador = 0;
	}
	if (Game::instance().getKey(13)) {
		Game::instance().keyReleased(13);
		Game::instance().newaction(5);
	}
}

void LevelTransition::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	fondo->render(imgFondo);
	stats->render(imgStats);

	int money = scene.getmoney();
	int points = scene.getpoints();
	int room = scene.getRoom();
	int lives = scene.getlives();

	std::string livesStr = std::to_string(lives);
	text.render(livesStr, glm::vec2(850, 410), 32, glm::vec4(1, 1, 1, 1));

	std::string pointsStr = std::to_string(points);
	text.render(pointsStr, glm::vec2(790, 240), 28, glm::vec4(1, 1, 1, 1));

	std::string moneyStr = std::to_string(money);
	text.render(moneyStr, glm::vec2(790, 100), 28, glm::vec4(1, 1, 1, 1));

	std::string roomStr = std::to_string(room + 1);
	text.render(roomStr, glm::vec2(850, 710), 32, glm::vec4(1, 1, 1, 1));

	int bank = Game::instance().getlevel() + 1;
	std::string bankStr = std::to_string(bank);
	text.render(bankStr, glm::vec2(850, 520), 32, glm::vec4(1, 1, 1, 1));
}
void LevelTransition::setScene(Scene s)
{
	scene = s;
}

void LevelTransition::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}