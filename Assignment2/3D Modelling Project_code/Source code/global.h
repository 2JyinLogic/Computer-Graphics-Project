#pragma once
#include <GL/freeglut.h>

#include<stdlib.h> 
#include<time.h> 




// Radian
#define TO_RAD (3.14159265/180.0); 


extern float red[],
			green[],
			blue[],
			black[],
			yellow[],
			gold[],
			purple[],
			cyan[],
			white[],
			orange[],
			greenish_yellow[],
			light_green[],
			dark_green[],
			magenta[],
			violet[],
			baby_blue[],
			lilac[],
			dark_grey[],
			dark_purple[],
			bronze[],
			dark_blue[],
			forest_green[],
			brown[],
			light_blue[],
			chair_wood[],
			table_wood[],
			bed_wood[],
			pillow_color[],
			closet_wood[],
			plastic_black[],
			tiles_white[],
	        light_yellow[],
			grey[];
         



// Vertices (vectors)
struct Vertex {
	float x;
	float y;
	float z;
};



struct MovingObject {
	float x;
	float y;
	float z;
	float angle;
};// camera, camel




// Knowing 3 points, find the plane normal vector
void normal(Vertex* v1, Vertex* v2, Vertex* v3, bool reversed);

void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3);



// Generate a random integer (in range)
int randInt(int min, int max);