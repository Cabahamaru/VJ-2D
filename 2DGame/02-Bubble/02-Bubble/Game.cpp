#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <irrKlang.h>
#include <iostream>

using namespace irrklang;

void Game::init()
{ 
	bPlay = true;
	state = 3;
	level = 0;
	money = 0;
	points = 0;
	SoundEngine = createIrrKlangDevice();
	if (!SoundEngine)
	{
		printf("Could not startup engine\n");
	}
	SoundEngine->setSoundVolume(0.5f);
	SoundEngine->play2D("sounds/avengers-theme-8-bit.wav", true);
	
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	menu.init();
}

bool Game::update(int deltaTime)
{
	if (state == 3) menu.update(deltaTime);
	else if (state == 0) scene.update(deltaTime);
	else if (state == 1) inst.update(deltaTime);
	else if (state == 2) credits.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (state == 3) menu.render();
	else if (state == 0) scene.render();
	else if (state == 1) inst.render();
	else if (state == 2) credits.render();
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

	state = act;
	if (act == 3) {
		menu.init();
	}
	else if (act == 0) {
		scene.setSound(SoundEngine);
		scene.init();
	}
	else if (act == 1) {
		inst.init();
	}
	else {
		credits.init();
	}
}

int Game::getCurrentRoom() {
	return scene.getRoom();
}

void Game::loselife() {

}

int Game::getlevel()
{
	return level;

}
int Game::getpoints() {

	return points;
}

void Game::breakbrick() {
	points += 100;
	SoundEngine->setSoundVolume(0.1f);
	SoundEngine->play2D("sounds/block_break.mp3", false);
}

void Game::alarm_ring() {
	SoundEngine->setSoundVolume(0.1f);
	SoundEngine->play2D("sounds/alarm.mp3", false);
}

void Game::catch_key() {
	SoundEngine->setSoundVolume(0.3f);
	SoundEngine->play2D("sounds/key.mp3", false);
}





