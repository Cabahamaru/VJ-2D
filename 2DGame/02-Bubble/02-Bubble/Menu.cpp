#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Menu.h"
#include "Game.h"
#include <GL/glut.h>

#define SCREEN_X 32
#define SCREEN_Y 32

int contador = 0;

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::init()
{
	initShaders();
	currentTime = 0.0f;
	accion = 0;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	fondo = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	imgFondo.loadFromFile("images/mainmenu.png", TEXTURE_PIXEL_FORMAT_RGBA);

	glm::vec2 geom2[2] = { glm::vec2(0.f, 0.f), glm::vec2(32.f, 32.f) };
	glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);
	imgCursor.loadFromFile("images/cursor1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cur1 = true;

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

}

void Menu::update(int deltaTime)
{
	currentTime += deltaTime;
	++contador;
	if (contador > 30) {
		if (cur1) {
			imgCursor.loadFromFile("images/cursor2.png", TEXTURE_PIXEL_FORMAT_RGBA);
			cur1 = false;
		}
		else {
			imgCursor.loadFromFile("images/cursor1.png", TEXTURE_PIXEL_FORMAT_RGBA);
			cur1 = true;
		}
		contador = 0;
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		Game::instance().setSpecialKey(GLUT_KEY_DOWN);
		accion += 1;
		accion = accion % 3;

	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		Game::instance().setSpecialKey(GLUT_KEY_UP);
		accion -= 1;
		if (accion < 0) accion = 2;
		accion = accion % 3;
	}
	if (accion == 0) {
		glm::vec2 geom2[2] = { glm::vec2(420.f, 318.f), glm::vec2(420 + 32.f, 318 + 32.f) };
		glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);
	}

	else if (accion == 1) {
		glm::vec2 geom2[2] = { glm::vec2(585.f, 365.f), glm::vec2(585 + 32.f, 365 + 32.f) };
		glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);
	}

	else if (accion == 2) {
		glm::vec2 geom2[2] = { glm::vec2(485.f, 415.f), glm::vec2(485 + 32.f, 415 + 32.f) };
		glm::vec2 texCoords2[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
		cursor = TexturedQuad::createTexturedQuad(geom2, texCoords2, texProgram);
	}

	if (Game::instance().getKey(13)) {
		Game::instance().keyReleased(13);
		Game::instance().newaction(accion);
	}
}

void Menu::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	fondo->render(imgFondo);
	cursor->render(imgCursor);
}

void Menu::initShaders()
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