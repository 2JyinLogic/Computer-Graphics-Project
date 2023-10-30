#include "global.h"


// Define colors
float red[] = { 1.0 ,0.0 ,0.0, 1.0 },
green[] = { 0.0 ,1.0 ,0.0, 1.0 },
blue[] = { 0.0, 0.0 ,1.0, 1.0 },
black[] = { 0.0, 0.0, 0.0, 1.0 },
yellow[] = { 1.0 ,1.0, 0.0, 1.0 },
gold[] = { 0.8, 0.7, 0.3, 1 },
purple[] = { 1.0 ,0.0,1.0, 1.0 },
cyan[] = { 0.0 ,1.0, 1.0, 1.0 },
white[] = { 1.0 ,1.0 ,1.0, 1.0 },
orange[] = { 1.0 ,0.5, 0.0, 1.0 },
greenish_yellow[] = { 0.5, 1.0 ,0.0, 1.0 },
light_green[] = { 0.5, 1.0 ,0.5, 1.0 },
dark_green[] = { 0.0, 0.5, 0.0, 1.0 },
magenta[] = { 1,0,1, 1.0 },
violet[] = { 0.5f, 0.5f, 0.5f, 1.0 },
baby_blue[] = { 0.0f, 0.5f, 1.0f, 1.0 },
lilac[] = { 2.0f, 0.5f, 1.0f, 1.0 },
dark_grey[] = { 0.1f, 0.1f, 0.1f, 1.0 },
dark_purple[] = { 0.1f, 0.0f, 0.1f, 1.0 },
bronze[] = { 0.1f, 0.1f, 0.0f, 1.0 },
dark_blue[] = { 0.0f, 0.1f, 0.1f, 1.0 },
forest_green[] = { 0.0f, 0.1f, 0.0f, 1.0 },
brown[] = { 0.1f, 0.0f, 0.0f, 1.0 },
light_blue[] = { 0.0f, 1.0f, 1.0f, 1.0f },
chair_wood[] = { .20,.14,.14, 1.0 },
table_wood[] = { .30,.14,.14, 1.0 },
bed_wood[] = { .568,.318,.004, 1.0 },
pillow_color[] = { 0,1,.7, 1.0 },
closet_wood[] = { 1,.5,0, 1.0 },
plastic_black[] = { .2,.2,.2, 1.0 },
tiles_white[] = { .7,.7,.7 },
light_yellow[] = { 1.0, 0.9 ,0.5, 0.6 },
grey[] = { .4,.4,.4 };


// Find the normal vector of the plane, knowing 3 points
void normal(Vertex* v1, Vertex* v2, Vertex* v3, bool reversed) {
	float x1 = v1->x, y1 = v1->y, z1 = v1->z;
	float x2 = v2->x, y2 = v2->y, z2 = v2->z;
	float x3 = v3->x, y3 = v3->y, z3 = v3->z;

	float nx, ny, nz;
	nx = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
	ny = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
	nz = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);

	if (reversed) {
		glNormal3f(nx, ny, nz);
	}
	else {
		glNormal3f(-nx, -ny, -nz);
	}
}

void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz;
    GLfloat Vx, Vy, Vz;
    GLfloat Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}

int randInt(int min, int max)
{//generate random numbers in the range [a,b) 
	int randoxNumber = min + rand() % (max - min);
	return randoxNumber;
}
