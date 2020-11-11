#ifndef _BOSSTRANSITION_INCLUDE
#define _BOSSTRANSITION_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Texture.h"
#include "TexturedQuad.h"
#include "Text.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

class BossTransition
{

public:
	BossTransition();
	~BossTransition();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	int cur1;
	Texture imgFondo;
	TexturedQuad* fondo;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Text text;

};


#endif // _LEVELTRANSTION_INCLUDE

