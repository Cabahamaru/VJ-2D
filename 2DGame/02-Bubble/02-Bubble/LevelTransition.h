#ifndef _LEVELTRANSTION_INCLUDE
#define _LEVELTRANSTION_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Texture.h"
#include "TexturedQuad.h"
#include "Text.h"
#include "Scene.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

class LevelTransition
{

public:
	LevelTransition();
	~LevelTransition();

	void init();
	void update(int deltaTime);
	void render();

	void setScene(Scene s);

private:
	void initShaders();

private:
	int accion;
	bool cur1;
	Texture imgFondo, imgFondo2, imgStats;
	TexturedQuad* fondo, *fondo2, *stats;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Text text;
	Scene scene;

};


#endif // _LEVELTRANSTION_INCLUDE

