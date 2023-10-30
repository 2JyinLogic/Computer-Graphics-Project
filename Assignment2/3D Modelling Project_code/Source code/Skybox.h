#pragma once
#include "global.h"
#include "TextureLoader.h"

class Skybox {
public:
	Skybox()=delete;
	Skybox(Skybox& other) = delete;
	explicit Skybox(TextureLoader* textureLoader);
	
	~Skybox();


	// drawSkybox
	void drawSkybox();

	void drawSkyboxNight();


private:
	TextureLoader* texLoader;
};