#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"

#define SCREEN_X 32
#define SCREEN_Y 32

using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	
	map = new int[mapSize.x * mapSize.y];
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			fin.get(tile);
			if (tile == ' ')
				map[j * mapSize.x + i] = 0;
			else if (tile == 'a')
				map[j * mapSize.x + i] = 10;
			else
				map[j*mapSize.x+i] = tile - int('0');
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();
	
	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	halfTexel = glm::vec2(0.25f / tilesheet.width(), 0.25f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if(tile != 0)
			{
				bool aux = true;
				if (tile == 10) {
					nTiles++;
					posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize/2);
					texCoordTile[0] = glm::vec2(0.75f,0.0f);
					texCoordTile[1] = glm::vec2(1.f, 0.125f);
					aux = true;
				}
				else if (tile == 1) {
					nTiles++;
					posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize/2);
					texCoordTile[0] = glm::vec2(0.0f, 0.0f);
					texCoordTile[1] = glm::vec2(0.25f, 0.125f) ;
					aux = false;

					vertices.push_back(posTile.x); vertices.push_back(posTile.y);
					vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
					vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
					vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
					vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize/2);
					vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
					// Second triangle
					vertices.push_back(posTile.x); vertices.push_back(posTile.y);
					vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
					vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize/2);
					vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
					vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize/2);
					vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);


				}
				else {
					// Non-empty tile
					nTiles++;
					posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize/2);
					texCoordTile[0] = glm::vec2(float((tile - 1) % 2) / tilesheetSize.x, float((tile - 1) / 2) / tilesheetSize.y);
					texCoordTile[1] = texCoordTile[0] + tileTexSize;
					aux = true;
				}
				//texCoordTile[0] += halfTexel;
				//texCoordTile[1] -= halfTexel;
				// First triangle
				if(aux){
					vertices.push_back(posTile.x); vertices.push_back(posTile.y);
					vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
					vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
					vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
					vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize/2);
					vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
					// Second triangle
					vertices.push_back(posTile.x); vertices.push_back(posTile.y);
					vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
					vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize/2);
					vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
					vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize/2);
					vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
				}
				
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = pos.x / tileSize;
	y0 = pos.y / (tileSize/2);
	y1 = (pos.y + size.y - 1) / (tileSize/2);
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x+x] == 10)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / (tileSize/2);
	y1 = (pos.y + size.y - 1) / (tileSize/2);
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x+x] == 10)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;
	
	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / (tileSize/2);
	for(int x=x0; x<=x1; x++)
	{
		if(map[y*mapSize.x+x] == 10)
		{
			return true;
		}
	}
	
	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = (pos.x) / tileSize;
	x1 = (pos.x  + size.x - 1) / tileSize;
	y = ((pos.y) / (tileSize/2));
	for (int x = x0; x <= x1; x++)
	{
		if(map[y * mapSize.x + x] == 10)
		{
			if (*posY + tileSize * y + size.y >= 4)
			{
				return true;
			}
		}
		
	}

	return false;
}


bool TileMap::collisionMoveLeftBall(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x, y0, y1;

	x = pos.x / tileSize;
	y0 = (pos.y +4)/ (tileSize/2);
	y1 = (pos.y -4 + size.y - 1) / (tileSize/2);
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] == 10)
			return true;
		if (map[y * mapSize.x + x] == 1)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 2)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 3)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 4)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 5 || map[y * mapSize.x + x] == 7)
		{
			return ColissionWithKey(y, x);
		}
	}

	return false;
}

bool TileMap::collisionMoveRightBall(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x, y0, y1;

	x = (pos.x + size.x - 1) / tileSize;
	y0 = (pos.y + 4) / (tileSize/2);
	y1 = (pos.y - 4 + size.y - 1) / (tileSize/2);
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] == 10)
			return true;
		if (map[y * mapSize.x + x] == 1) 
		{
			return BreakBrick(y, x);
		}
		
		if (map[y * mapSize.x + x] == 2)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 3)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 4)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 5 || map[y * mapSize.x + x] == 7)
		{
			return ColissionWithKey(y, x);
		}
			
	}

	return false;
}

bool TileMap::collisionMoveDownBall(const glm::ivec2& pos, const glm::ivec2& size, int* posY)
{
	int x0, x1, y;

	x0 = (pos.x +4) / tileSize;
	x1 = ( (pos.x -4) + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / (tileSize/2);
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] == 1)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 10)
		{
			return true;
		}
		if (map[y * mapSize.x + x] == 2)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 3)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 4)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 5 || map[y * mapSize.x + x] == 7)
		{
			return ColissionWithKey(y, x);
		}

	}

	return false;
}

bool TileMap::collisionMoveUpBall(const glm::ivec2& pos, const glm::ivec2& size, int* posY)
{
	int x0, x1, y;

	x0 = (pos.x + 4) / tileSize;
	x1 = (pos.x - 4 + size.x - 1) / tileSize;
	y = ((pos.y) / (tileSize / 2));
	int yaux = ((pos.y) / (tileSize));
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] == 1)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 10)
		{
			return true;
		}
		if (map[y * mapSize.x + x] == 2)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 3)
		{
			return BreakBrick(y, x);
		}
		if (map[y * mapSize.x + x] == 4)
		{
			return BreakBrick(y, x);
		}
		
		if (map[y * mapSize.x + x] == 5 || map[y * mapSize.x + x] == 7)
		{
			return ColissionWithKey(y, x);
		}

	}

	return false;
}

bool TileMap::BreakBrick(int y, int x)
{
	map[y * mapSize.x + x] = 0;
	prepareArrays(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	return true;
}

bool TileMap::ColissionWithKey(int y, int x)
{
	if (map[y * mapSize.x + x] == 5)
	{
		map[(y + 1) * mapSize.x + x] = 0;
	}
	else if (map[y * mapSize.x + x] == 7)
	{
		map[(y - 1) * mapSize.x + x] = 0;
	}
	map[y * mapSize.x + x] = 0;
	map[7] = 0;
	map[8] = 0;
	map[9] = 0;
	map[10] = 0;
	prepareArrays(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	return true;

}


void TileMap::setShaderProgram(ShaderProgram program) {
	texProgram = program;
}



























