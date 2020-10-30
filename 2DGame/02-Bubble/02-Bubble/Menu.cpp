#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Menu.h"
#include "Game.h"
#include <GL/glut.h>

#define SCREEN_X 32
#define SCREEN_Y 32

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

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

}

void Menu::update(int deltaTime)
{
	currentTime += deltaTime;
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