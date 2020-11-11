#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <irrKlang.h>
#include <iostream>

using namespace irrklang;

void Game::init()
{ 
	bPlay = true;
	GOD_MODE = false;
	state = 3;
	level = 0;
	SoundEngine = createIrrKlangDevice();
	if (!SoundEngine)
	{
		printf("Could not startup engine\n");
	}
	SoundEngine->setSoundVolume(0.5f);
	SoundEngine->play2D("sounds/avengers-theme-8-bit.mp3", true);
	
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	menu.init();
}

bool Game::update(int deltaTime)
{
	if (state == 3) menu.update(deltaTime);
	else if (state == 0) scene.update(deltaTime);
	else if (state == 1) inst.update(deltaTime);
	else if (state == 2) credits.update(deltaTime);
	else if (state == 4) gameover.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (state == 3) menu.render();
	else if (state == 0) scene.render();
	else if (state == 1) inst.render();
	else if (state == 2) credits.render();
	else if (state == 4) gameover.render();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		if (state != 3) {
			init();
			//newaction(3);
		}
		else bPlay = false;
	if (getSpecialKey(GLUT_KEY_F5)) GOD_MODE = !GOD_MODE;
	if (key == 'g') GOD_MODE = !GOD_MODE;
	if (GOD_MODE && key == 'k') scene.GOD_get_key();
	if (GOD_MODE && key == 'b') scene.GOD_break_bricks();
	if (GOD_MODE && key == 'n') scene.GOD_next_room();
	if (GOD_MODE && key == 'p') scene.GOD_previous_room();
	if (GOD_MODE && key == 'l') nextLevel();
	if (GOD_MODE && key == 'j') previousLevel();
	if (GOD_MODE && key == 'm') scene.GOD_get_money();

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
	if (act == 3) { //pantalla de menu
		menu.init();
	}
	else if (act == 0) { //jugar
		scene.setSound(SoundEngine);
		scene.init();
	}
	else if (act == 1) { //pantalla de instrucciones
		inst.init();
	}
	else if (act == 2) { //pantalla de creditos
		credits.init();
	}
	else if (act == 4) { //pantalla de game over
		SoundEngine->stopAllSounds();
		gameover.init();
	}
}

int Game::getCurrentRoom() {
	return scene.getRoom();
}

void Game::loselife() {
	if (!GOD_MODE) {
		SoundEngine->setSoundVolume(0.1f);
		SoundEngine->play2D("sounds/lose_life.mp3", false);
		scene.loselife();
	}
}

int Game::getlevel()
{
	return level;
}

void Game::breakhardbrick() {
	SoundEngine->setSoundVolume(0.1f);
	SoundEngine->play2D("sounds/block_break.mp3", false);
}

void Game::breakbrick() {
	scene.addpoints(100);
	SoundEngine->setSoundVolume(0.1f);
	SoundEngine->play2D("sounds/block_break.mp3", false);
}

void Game::breakcoin() {
	scene.addmoney(100);
	SoundEngine->setSoundVolume(0.1f);
	if (!GOD_MODE) SoundEngine->play2D("sounds/coin.mp3", false);
	if (level == 0 && scene.getmoney() == 2800) nextLevel();
}

void Game::breakbag() {
	scene.addmoney(200);
	SoundEngine->setSoundVolume(0.2f);
	if (!GOD_MODE) SoundEngine->play2D("sounds/bagcoins.mp3", false);
	if (level == 0 && scene.getmoney() == 2800) nextLevel();
}

void Game::alarm_ring() {
	SoundEngine->setSoundVolume(0.1f);
	SoundEngine->play2D("sounds/alarm.mp3", false);
}

void Game::stop_alarm() {
	SoundEngine->stopAllSounds();
}

void Game::catch_key() {
	SoundEngine->setSoundVolume(0.3f);
	SoundEngine->play2D("sounds/key.mp3", false);
}

void Game::nextRoom()
{
	scene.nextRoom();
}
void Game::previousRoom()
{
	scene.previousRoom();
}
void Game::nextLevel()
{	
	if (level == 2) {
		//there is no next level
	}
	else {
		++level;
		scene.nextLevel();
	}
}

void Game::previousLevel()
{
	if (level == 0) {
		//there is no previous level
	}
	else {
		--level;
		scene.nextLevel();
	}
}

bool Game::I_AM_GOD() {
	return GOD_MODE;
}





