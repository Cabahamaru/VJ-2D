#include "BossTransition.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <GL/glut.h>

#define SCREEN_X 32
#define SCREEN_Y 32

int Bosstransitioncontador = 0;

BossTransition::BossTransition()
{

}

BossTransition::~BossTransition()
{

}

void BossTransition::init()
{
	initShaders();
	currentTime = 0.0f;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	fondo = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	imgFondo.loadFromFile("images/intro_boss1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cur1 = 0;

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	if (!text.init("fonts/ARCADEPI.ttf")) {
		cout << "Could not load font!!!" << endl;
	}

}

void BossTransition::update(int deltaTime)
{
	currentTime += deltaTime;
	++Bosstransitioncontador;
	if (Bosstransitioncontador > 30) {
		if (cur1 == 0) {
			imgFondo.loadFromFile("images/intro_boss1.png", TEXTURE_PIXEL_FORMAT_RGBA);
			cur1++;
		}
		else if(cur1 == 1){
			imgFondo.loadFromFile("images/intro_boss2.png", TEXTURE_PIXEL_FORMAT_RGBA);
			cur1++;
		}
		else{
			imgFondo.loadFromFile("images/intro_boss3.png", TEXTURE_PIXEL_FORMAT_RGBA);
			cur1 = 0;
		}
		Bosstransitioncontador = 0;
	}
	if (Game::instance().getKey(13)) {
		Game::instance().keyReleased(13);
		Game::instance().newaction(6);
	}
}

void BossTransition::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	fondo->render(imgFondo);
	text.render("You feel an EVIL presence watching you...", glm::vec2(50, 520), 32, glm::vec4(1, 1, 1, 1));
	text.render("Press ENTER when you're ready...", glm::vec2(140, 620), 32, glm::vec4(1, 1, 1, 1));
}

void BossTransition::initShaders()
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