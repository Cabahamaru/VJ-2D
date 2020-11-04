
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "Instruccions.h"
#include <GL/glut.h>

int aux = 0;

Instruccions::Instruccions()
{
}

Instruccions::~Instruccions()
{
}

void Instruccions::init() {
	initShaders();
	currentTime = 0.0f;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	fondo = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	instruccionsImage.loadFromFile("images/instruccions1.png", TEXTURE_PIXEL_FORMAT_RGBA);;
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	ent = true;
}

void Instruccions::update(int deltaTime) {
	currentTime += deltaTime;

	++aux;
	if (aux > 45) {
		if (ent) {
			instruccionsImage.loadFromFile("images/instruccions2.png", TEXTURE_PIXEL_FORMAT_RGBA);
			ent = false;
		}
		else {
			instruccionsImage.loadFromFile("images/instruccions1.png", TEXTURE_PIXEL_FORMAT_RGBA);
			ent = true;
		}
		aux = 0;
	}

	if (Game::instance().getKey(13)) {
		Game::instance().keyReleased(13);
		Game::instance().newaction(3);
	}
}

void Instruccions::render() {
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	fondo->render(instruccionsImage);

}

void Instruccions::initShaders()
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
