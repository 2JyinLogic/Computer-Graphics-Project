#include "StaticObject.h"

#include "TextureLoader.h"
#include "MoveObject.h"

void drawCube()
{
	static GLfloat v_cube[8][3] =
	{
		// Standard rectangle
		{ 0.0, 0.0, 0.0 }, //0
		{ 0.0, 0.0, 1.0 }, //1
		{ 1.0, 0.0, 1.0 }, //2
		{ 1.0, 0.0, 0.0 }, //3
		{ 0.0, 1.0, 0.0 }, //4
		{ 0.0, 1.0, 1.0 }, //5
		{ 1.0, 1.0, 1.0 }, //6
		{ 1.0, 1.0, 0.0 }  //7

	};

	static GLubyte quadIndices[6][4] =
	{
		{ 0, 1, 2, 3 }, //bottom
		{ 4, 5, 6, 7 }, //top
		{ 5, 1, 2, 6 }, //front
		{ 0, 4, 7, 3 }, // back is clockwise
		{ 2, 3, 7, 6 }, //right
		{ 1, 5, 4, 0 }  //left is clockwise
	};

	glBegin(GL_QUADS);
	for (GLint i = 0; i < 6; i++)
	{
		getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
			v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
			v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);

		glVertex3fv(&v_cube[quadIndices[i][0]][0]); glTexCoord2f(0, 1);
		glVertex3fv(&v_cube[quadIndices[i][1]][0]); glTexCoord2f(0, 0);
		glVertex3fv(&v_cube[quadIndices[i][2]][0]); glTexCoord2f(1, 0);
		glVertex3fv(&v_cube[quadIndices[i][3]][0]); glTexCoord2f(1, 1);
	}
	glEnd();
}


/* StaticObject **********************************************************/
StaticObject::StaticObject(TextureLoader* loader) 
{
	texLoader = loader;
}

StaticObject::~StaticObject() 
{

}

/* Ground **********************************************************/

Ground::Ground(TextureLoader* loader) :StaticObject(loader) 
{
}
Ground::~Ground() 
{
}


// Drawing the Earth
void Ground::drawGround() {
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SAND]);

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	for (int x = -4000; x <= 4000; x += 200) {
		for (int z = -4000; z <= 4000; z += 200) {
			glTexCoord2f(0.0, 0.0); glVertex3f(x, 0, z);
			glTexCoord2f(0.0, 1.0); glVertex3f(x, 0, z + 200);
			glTexCoord2f(1.0, 1.0); glVertex3f(x + 200, 0, z + 200);
			glTexCoord2f(1.0, 0.0); glVertex3f(x + 200, 0, z);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


/* Floor **********************************************************/


MFloor::MFloor(TextureLoader* loader):
	StaticObject(loader)
{

}
MFloor::~MFloor()
{

}


// Drawing the floor
void MFloor::drawFloor(int min, int max, int inc, Texture tex) {
	//const int MIN = -75, MAX = 75, INC = 15;

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[tex]);

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	for (int x = min; x < max; x += inc) {
		for (int z = min; z < max; z += inc) {
			glTexCoord2f(0.0, 0.0); glVertex3f(x, 0, z);
			glTexCoord2f(0.0, 1.0); glVertex3f(x, 0, z + inc);
			glTexCoord2f(1.0, 1.0); glVertex3f(x + inc, 0, z + inc);
			glTexCoord2f(1.0, 0.0); glVertex3f(x + inc, 0, z);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


/* Door **********************************************************/
Door::Door(TextureLoader* loader): 
	StaticObject(loader)
{
	texLoader = loader;
}
Door::~Door() {}

//Drawing Door
void Door::drawDoor() {
	glTranslatef(0.15, 0, 0); // Location of the door
	glRotatef(this->angle, 0, 1, 0); //Determines the opening and closing orientation of the door y-axis direction
	glTranslatef(-0.15, 0, 0);

	//The yellow part of the middle of the door corresponds to the matrix
	glPushMatrix();
	glColor4fv(gold);
	glScalef(0.15, 0.5, 0.04);
	glutSolidCube(1);
	glPopMatrix();

	//The entire door panel section
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	glColor4f(0.15, 0.15, 0.15, 1);
	glScalef(0.3, 1, 0.02);
	glutSolidCube(1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glPopMatrix();

	glColor4f(1, 1, 1, 1);
}

// Mobile doors
void Door::moveDoors(Cammera & cam) {
	const float DETECT_X_LOWER = -20, DETECT_X_UPPER = 60;//Door opening x-axis perception range
	const float DETECT_Z_LOWER = -120, DETECT_Z_UPPER = -80;//Door opening z-axis perception range
	const float OPEN_ANGLE = 80, CLOSED_ANGLE = 0; //Angle of the switch

	if (opening) {
		angle += 1;
		if (angle >= OPEN_ANGLE) {
			opening = false;
			open = true;
		}
	}
	else if (closing) {
		angle -= 1;
		if (angle <= CLOSED_ANGLE) {
			closing = false;
			open = false;
		}
	}
	else if (cam.x > DETECT_X_LOWER && cam.x < DETECT_X_UPPER && cam.z > DETECT_Z_LOWER && cam.z < DETECT_Z_UPPER) {
		if (!open) {
			 opening = true;
		}
	}
	else if (open) {
		closing = true;
	}
};

/* Warehouse  *************************************************/
Warehouse::Warehouse(TextureLoader* loader) :
	StaticObject(loader),
	doorState(loader)
{

}

Warehouse::~Warehouse()
{

}

// Drawing the warehouse
void Warehouse::drawWarehouse(bool reversed) 
{
	// xz is the plane, y is up and down
	
	Vertex v[20];

	// Bottom Corners
	v[0] = { 0, 0, 0 };
	v[1] = { 0, 0, 3 };
	v[2] = { 3, 0, 3 };
	v[3] = { 3, 0, 0 };

	// Roof Corners
	v[4] = { 1, 2, 1 };
	v[5] = { 1, 2, 2 };  //top
	v[6] = { 2, 2, 2 }; // top
	v[7] = { 2, 2, 1 };

	// Front Face Bottom
	v[8] = { 1.2, 0, 0 };
	v[9] = { 1.8, 0, 0 };

	// Front Face Mid
	v[10] = { 1.2, 1, 0.5 };
	v[11] = { 1.8, 1, 0.5 };
	v[12] = { 0.5, 1, 0.5 };
	v[13] = { 2.5, 1, 0.5 };

	// Front Face Top
	v[14] = { 1.2, 2, 1 };
	v[15] = { 1.8, 2, 1 };

	// Entrance Bottom
	v[16] = { 1.2, 0, -0.25 };
	v[17] = { 1.8, 0, -0.25 };

	// Entrance Roof
	v[18] = { 1.2, 1, -0.25 };
	v[19] = { 1.8, 1, -0.25 };


	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[SANDSTONE_BRICK]);

	glBegin(GL_QUADS);


	// left face
	normal(&v[0], &v[4], &v[5], reversed);
	glTexCoord2f(3, 0); glVertex3f(v[0].x, v[0].y, v[0].z);
	glTexCoord2f(2, 2); glVertex3f(v[4].x, v[4].y, v[4].z);
	glTexCoord2f(1, 2); glVertex3f(v[5].x, v[5].y, v[5].z); //
	glTexCoord2f(0, 0); glVertex3f(v[1].x, v[1].y, v[1].z); 

	// back face
	normal(&v[1], &v[5], &v[6], reversed);
	glTexCoord2f(3, 0); glVertex3f(v[1].x, v[1].y, v[1].z); 
	glTexCoord2f(2, 2); glVertex3f(v[5].x, v[5].y, v[5].z); //
	glTexCoord2f(1, 2); glVertex3f(v[6].x, v[6].y, v[6].z); //**
	glTexCoord2f(0, 0); glVertex3f(v[2].x, v[2].y, v[2].z); 

	// right face
	normal(&v[2], &v[6], &v[7], reversed);
	glTexCoord2f(3, 0); glVertex3f(v[2].x, v[2].y, v[2].z); 
	glTexCoord2f(2, 2); glVertex3f(v[6].x, v[6].y, v[6].z); //**
	glTexCoord2f(1, 2); glVertex3f(v[7].x, v[7].y, v[7].z);
	glTexCoord2f(0, 0); glVertex3f(v[3].x, v[3].y, v[3].z);

	// top face
	normal(&v[4], &v[5], &v[6], reversed);
	glTexCoord2f(0, 0); glVertex3f(v[4].x, v[4].y, v[4].z);
	glTexCoord2f(0, 2); glVertex3f(v[5].x, v[5].y, v[5].z); //**
	glTexCoord2f(2, 2); glVertex3f(v[6].x, v[6].y, v[6].z);
	glTexCoord2f(2, 0); glVertex3f(v[7].x, v[7].y, v[7].z);


	/* Front of the warehouse 5 sides in total, separated by the gate****************************************/
    // Front of the warehouse A //
	normal(&v[0], &v[8], &v[10], reversed);
	glTexCoord2f(v[0].x, v[0].y); glVertex3f(v[0].x, v[0].y, v[0].z);
	glTexCoord2f(v[8].x, v[8].y); glVertex3f(v[8].x, v[8].y, v[8].z);
	glTexCoord2f(v[10].x, v[10].y); glVertex3f(v[10].x, v[10].y, v[10].z);
	glTexCoord2f(v[12].x, v[12].y); glVertex3f(v[12].x, v[12].y, v[12].z);

	// In front of the warehouse E //
	normal(&v[9], &v[3], &v[13], reversed);
	glTexCoord2f(v[9].x, v[9].y); glVertex3f(v[9].x, v[9].y, v[9].z);
	glTexCoord2f(v[3].x, v[3].y); glVertex3f(v[3].x, v[3].y, v[3].z);
	glTexCoord2f(v[13].x, v[13].y); glVertex3f(v[13].x, v[13].y, v[13].z);
	glTexCoord2f(v[11].x, v[11].y); glVertex3f(v[11].x, v[11].y, v[11].z);

	// In front of the warehouse B //
	normal(&v[12], &v[10], &v[14], reversed);
	glTexCoord2f(v[12].x, v[12].y); glVertex3f(v[12].x, v[12].y, v[12].z);
	glTexCoord2f(v[10].x, v[10].y); glVertex3f(v[10].x, v[10].y, v[10].z);
	glTexCoord2f(v[14].x, v[14].y); glVertex3f(v[14].x, v[14].y, v[14].z);
	glTexCoord2f(v[4].x, v[4].y); glVertex3f(v[4].x, v[4].y, v[4].z);

	// In front of the warehouse D //
	normal(&v[11], &v[13], &v[7], reversed);
	glTexCoord2f(v[11].x, v[11].y); glVertex3f(v[11].x, v[11].y, v[11].z);
	glTexCoord2f(v[13].x, v[13].y); glVertex3f(v[13].x, v[13].y, v[13].z);
	glTexCoord2f(v[7].x, v[7].y); glVertex3f(v[7].x, v[7].y, v[7].z);
	glTexCoord2f(v[15].x, v[15].y); glVertex3f(v[15].x, v[15].y, v[15].z);

	// In front of the warehouse C //
	normal(&v[10], &v[11], &v[15], reversed);
	glTexCoord2f(v[10].x, v[10].y); glVertex3f(v[10].x, v[10].y, v[10].z);
	glTexCoord2f(v[11].x, v[11].y); glVertex3f(v[11].x, v[11].y, v[11].z);
	glTexCoord2f(v[15].x, v[15].y); glVertex3f(v[15].x, v[15].y, v[15].z);
	glTexCoord2f(v[14].x, v[14].y); glVertex3f(v[14].x, v[14].y, v[14].z);


	/* Noodles in front of the main gate Total 3 sides **********************************/
	// entrance left wall //
	normal(&v[8], &v[16], &v[18], reversed);
	glTexCoord2f(v[8].z, v[8].y); glVertex3f(v[8].x, v[8].y, v[8].z);
	glTexCoord2f(v[16].z, v[16].y); glVertex3f(v[16].x, v[16].y, v[16].z);
	glTexCoord2f(v[18].z, v[18].y); glVertex3f(v[18].x, v[18].y, v[18].z);
	glTexCoord2f(v[10].z, v[10].y); glVertex3f(v[10].x, v[10].y, v[10].z);

	// entrance right wall //
	normal(&v[17], &v[9], &v[11], reversed);
	glTexCoord2f(v[17].z, v[17].y); glVertex3f(v[17].x, v[17].y, v[17].z);
	glTexCoord2f(v[9].z, v[9].y); glVertex3f(v[9].x, v[9].y, v[9].z);
	glTexCoord2f(v[11].z, v[11].y); glVertex3f(v[11].x, v[11].y, v[11].z);
	glTexCoord2f(v[19].z, v[19].y); glVertex3f(v[19].x, v[19].y, v[19].z);

	// entrance roof //
	normal(&v[18], &v[19], &v[11], reversed);
	glTexCoord2f(v[18].x, v[18].z); glVertex3f(v[18].x, v[18].y, v[18].z);
	glTexCoord2f(v[19].x, v[19].z); glVertex3f(v[19].x, v[19].y, v[19].z);
	glTexCoord2f(v[11].x, v[11].z); glVertex3f(v[11].x, v[11].y, v[11].z);
	glTexCoord2f(v[10].x, v[10].z); glVertex3f(v[10].x, v[10].y, v[10].z);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Warehouse::drawCompleteWarehouse() 
{
	glTranslatef(100, 0, -100);
	glScalef(50, 50, 50);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.5, 0, -1.5); // to centre the pyramid

	// Left door
	glPushMatrix();
	glTranslatef(1.35 + 0.001, 0.5 - 0.001, -0.235);
	glScalef(-1, 1, 1);
	doorState.drawDoor();
	glPopMatrix();

	// Right Door
	glPushMatrix();
	glTranslatef(1.65 - 0.001, 0.5 - 0.001, -0.235);
	doorState.drawDoor();
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(0.03, 0, 0.01);
	glScalef(0.98, 0.98, 0.98);
	drawWarehouse(true);
	glPopMatrix();

}


/* Fance ************************************************/
Fencing::Fencing(TextureLoader* loader) :StaticObject(loader) 
{

}

Fencing::~Fencing() 
{

}

void Fencing::drawOne(bool horizontal) 
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM2]); //src
	if (horizontal)
	{
		// vertical column
		glPushMatrix();
		glScalef(1, 40, 3);
		drawCube();
		glTranslatef(0, 0, 3);
		drawCube();
		glTranslatef(0, 0, 3);
		drawCube();
		glTranslatef(0, 0, 3);
		drawCube();
		glTranslatef(0, 0, 3);
		drawCube();
		glPopMatrix();

		//Crossbar
		glPushMatrix();
		glTranslatef(0, 30, 0);
		glScalef(1, 3, 50);
		drawCube();
		glPopMatrix();
	}
	else
	{
		// vertical column
		glPushMatrix();
		glScalef(3, 40, 1);
		drawCube();
		glTranslatef(3, 0, 0);
		drawCube();
		glTranslatef(3, 0, 0);
		drawCube();
		glTranslatef(3, 0, 0);
		drawCube();
		glTranslatef(3, 0, 0);
		drawCube();
		glPopMatrix();

		// horizontal bar
		glPushMatrix();
		glTranslatef(0, 30, 0);
		glScalef(50, 3, 1);
		drawCube();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

// Draw the fence (px, py, pz: coordinates), (num: length of the fence) (horizontal: horizontal or vertical alignment)
void Fencing::drawMulti(float px, float py, float pz, int num, bool horizontal) 
{
	glPushMatrix();
	glTranslatef(px, py, pz); //Starting position

	if (horizontal)
	{
		for (int i = 0; i < num; ++i)
		{
			glPushMatrix();
			glTranslatef(0, 0, i * 45);
			drawOne(horizontal);
			glPopMatrix();
		}
	}
	else
	{
		for (int i = 0; i < num; ++i)
		{
			glPushMatrix();
			glTranslatef(i * 45, 0, 0);
			drawOne(horizontal);
			glPopMatrix();
		}
	}

	glPopMatrix();
}
