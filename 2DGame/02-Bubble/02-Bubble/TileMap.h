#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);
	~TileMap();

	void render() const;
	void free();
	
	int getTileSize() const { return tileSize; }

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;

	bool collisionMoveLeftBall(const glm::ivec2& pos, const glm::ivec2& size) ;
	bool collisionMoveRightBall(const glm::ivec2& pos, const glm::ivec2& size) ;
	bool collisionMoveDownBall(const glm::ivec2& pos, const glm::ivec2& size, int* posY) ;
	bool collisionMoveUpBall(const glm::ivec2& pos, const glm::ivec2& size, int* posY) ;

	bool BreakMoney(int y, int x);

	bool ColissionWithKey(int y, int x);
	bool ColissionWithAlarm(int y, int x);
	bool ColissionWithMoney(int y, int x);
	bool BreakBrick(int y, int x);
	void GOD_break_bricks();

	void GOD_break_key();

	void GOD_get_money();

	void setShaderProgram(ShaderProgram program);

	bool getAlarmStatus();
	void setAlarmStatus(bool b);

	void moveTileMap(const glm::vec2& minCoords);

	bool checkRoomChange(const glm::vec2& ballpos);


	
private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int *map;
	ShaderProgram texProgram;
	bool Alarm;

};


#endif // _TILE_MAP_INCLUDE


