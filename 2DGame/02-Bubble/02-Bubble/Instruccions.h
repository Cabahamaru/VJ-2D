#ifndef _INSTRUCCIONS_INCLUDE
#define _INSTRUCCIONS_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Texture.h"
#include "TexturedQuad.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

class Instruccions
{
public:
	Instruccions();
	~Instruccions();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	bool ent;
	Texture instruccionsImage;
	TexturedQuad* fondo;
};
#endif
