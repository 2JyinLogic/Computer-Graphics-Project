
#include "Skybox.h"

Skybox::Skybox(TextureLoader* textureLoader)
{
	this->texLoader = textureLoader;
}

Skybox::~Skybox()
{

}

void Skybox::drawSkybox()
{
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);

	////////////////////// LEFT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1000, 0, 1000);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1000, 0, -1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 1000, -1000);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 1000, 1000);
	glEnd();

	////////////////////// FRONT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1000, 0, -1000);
	glTexCoord2f(0.0, 0.0); glVertex3f(1000, 0, -1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(1000, 1000, -1000);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 1000, -1000);
	glEnd();

	////////////////////// RIGHT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0, -1000);
	glTexCoord2f(0.0, 0.0); glVertex3f(1000, 0, 1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(1000, 1000, 1000);
	glTexCoord2f(1.0, 1.0); glVertex3f(1000, 1000, -1000);
	glEnd();


	////////////////////// REAR WALL ////////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_BACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0, 1000);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1000, 0, 1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 1000, 1000);
	glTexCoord2f(1.0, 1.0); glVertex3f(1000, 1000, 1000);
	glEnd();

	/////////////////////// TOP //////////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_TOP]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 1000, -1000);
	glTexCoord2f(1.0, 0.0); glVertex3f(1000, 1000, -1000);
	glTexCoord2f(0.0, 0.0); glVertex3f(1000, 1000, 1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 1000, 1000);
	glEnd();

	/////////////////////// FLOOR //////////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_BOTTOM]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1000, 0, 1000);
	glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0, 1000);
	glTexCoord2f(1.0, 1.0); glVertex3f(1000, 0, -1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 0, -1000);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Skybox::drawSkyboxNight() 
{
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);

	////////////////////// LEFT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_NIGHT_LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1000, 0, 1000);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1000, 0, -1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 1000, -1000);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 1000, 1000);
	glEnd();

	////////////////////// FRONT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_NIGHT_FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1000, 0, -1000);
	glTexCoord2f(0.0, 0.0); glVertex3f(1000, 0, -1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(1000, 1000, -1000);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 1000, -1000);
	glEnd();

	////////////////////// RIGHT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_NIGHT_RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0, -1000);
	glTexCoord2f(0.0, 0.0); glVertex3f(1000, 0, 1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(1000, 1000, 1000);
	glTexCoord2f(1.0, 1.0); glVertex3f(1000, 1000, -1000);
	glEnd();


	////////////////////// REAR WALL ////////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_NIGHT_BACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0, 1000);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1000, 0, 1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 1000, 1000);
	glTexCoord2f(1.0, 1.0); glVertex3f(1000, 1000, 1000);
	glEnd();

	/////////////////////// TOP //////////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_NIGHT_TOP]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 1000, -1000);
	glTexCoord2f(1.0, 0.0); glVertex3f(1000, 1000, -1000);
	glTexCoord2f(0.0, 0.0); glVertex3f(1000, 1000, 1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 1000, 1000);
	glEnd();

	/////////////////////// FLOOR //////////////////////////
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SKYBOX_NIGHT_BOTTOM]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1000, 0, 1000);
	glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0, 1000);
	glTexCoord2f(1.0, 1.0); glVertex3f(1000, 0, -1000);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 0, -1000);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
