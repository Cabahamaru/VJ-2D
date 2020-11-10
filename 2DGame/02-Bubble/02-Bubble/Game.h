#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "Menu.h"
#include "credits.h"
#include "Instruccions.h"
#include "GameOver.h"
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

using namespace irrklang;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	void setSpecialKey(int key);
	void newaction(int act);
	int getCurrentRoom();
	void loselife();
	void breakbrick();
	void breakcoin();
	void breakbag();
	void alarm_ring();
	void stop_alarm();
	void nextRoom();
	bool I_AM_GOD();

	void previousRoom();

	void nextLevel();
	
	void catch_key();

	int getlevel();;

private:
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	Menu menu;
	Credits credits;
	Instruccions inst;
	GameOver gameover;
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	int state;
	ISoundEngine* SoundEngine;
	int level;
	bool GOD_MODE;
};


#endif // _GAME_INCLUDE


