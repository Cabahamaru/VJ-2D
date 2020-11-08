#ifndef _GAMEOVER_INCLUDE
#define _GAMEOVER_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Texture.h"
#include "TexturedQuad.h"
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

using namespace irrklang;

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

class GameOver
{

public:
	GameOver();
	~GameOver();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	int accion;
	bool cur1;
	Texture imgFondo, imgCursor;
	TexturedQuad* fondo, * cursor;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

	ISoundEngine* SoundEngine;

};


#endif

