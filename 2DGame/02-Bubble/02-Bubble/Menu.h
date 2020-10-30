#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Texture.h"
#include "TexturedQuad.h"
//#include "Text.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

class Menu
{

public:
	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void nextLevel();

private:
	int accion;
	//Text texto;
	Texture imgFondo, imgCursor;
	TexturedQuad *fondo, *cursor;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _MENU_INCLUDE

