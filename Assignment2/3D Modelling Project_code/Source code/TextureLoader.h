#pragma once
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>

using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F 

enum Texture { SKYBOX_LEFT, SKYBOX_FRONT, SKYBOX_RIGHT, SKYBOX_BACK, SKYBOX_TOP, SKYBOX_BOTTOM, 
			   SKYBOX_NIGHT_LEFT, SKYBOX_NIGHT_FRONT, SKYBOX_NIGHT_RIGHT, SKYBOX_NIGHT_BACK, SKYBOX_NIGHT_TOP, SKYBOX_NIGHT_BOTTOM,
			   
				SAND, GRASS, SANDSTONE_BRICK, FLOOR,
			   
				NUM1, NUM2, NUM3, NUM6, NUM7
};

class TextureLoader
{
public:
	TextureLoader(int num);
	~TextureLoader();

	void loadTGA(const char* filename);
	void loadGLSkyboxTextures(const char* filename, Texture tex);
	void loadGLTextures(const char* filename, Texture tex);

public:
	GLuint texId[32];//Set texture mapping to a maximum of 32
};


