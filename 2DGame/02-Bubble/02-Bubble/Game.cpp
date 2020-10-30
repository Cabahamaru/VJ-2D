#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	//scene.init();
	menu.init();
}

bool Game::update(int deltaTime)
{
	//scene.update(deltaTime);
	menu.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//scene.render();
	menu.render();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

void Game::setSpecialKey(int key) {
	specialKeyReleased(key);
}

void Game::newaction(int act)
{

	estado = act;
	if (act == 3) {
		menu.init();
	}
	else if (act == 0) {
		scene.init();
	}
	else if (act == 1) {

	}
	else {
		//glClearColor(1.f, 1.f, 1.f, 1.0f);
	}
}





