#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Texture.h"
#include "TexturedQuad.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

class Credits
{
public:
	Credits();
	~Credits();

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
	Texture creditsImage;
	TexturedQuad* fondo;
};
#endif
