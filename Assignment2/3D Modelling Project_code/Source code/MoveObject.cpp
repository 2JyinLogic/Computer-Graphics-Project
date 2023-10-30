#include "MoveObject.h"
#include <iostream>

/* MoveObject *************************************************************/
MoveObject::MoveObject() 
{
}
MoveObject::~MoveObject() {

}

void MoveObject::update(Vector3 pos, float angle)
{
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;

	this->angle = angle;

}



Vector3 MoveObject::pos()
{
	return Vector3(this->x, this->y, this->z);
}

Vector3 MoveObject::lookAt()
{	
	auto rad = this->angle * TO_RAD;
	return Vector3(this->x + cos(rad) * 500, this->y, this->z + sin(rad) * 500);
}

/* Cammera *************************************************************/

Cammera::Cammera()
{
}
Cammera::~Cammera() {

}

void Cammera::changeCamX(float amount) {
	auto rad = this->angle * TO_RAD;
	float x_offset = amount * cos(rad);
	this->x += x_offset;
}
void Cammera::changeCamZ(float amount)
{
	auto rad = this->angle * TO_RAD;
	float z_offset = amount * sin(rad);
	this->z += z_offset;
}

void Cammera::verticalMove(float distance)
{
	this->y += distance;
}

void Cammera::horizontalMove(float distance)
{
	changeCamX(distance);
	changeCamZ(distance);
}

void Cammera::leftMove(float distance)
{
	float temp = this->angle;

	this->angle -= 90;
	changeCamX(distance);
	changeCamZ(distance);

	this->angle = temp;
}

void Cammera::rightMove(float distance)
{
	float temp = this->angle;

	this->angle += 90;
	changeCamX(distance);
	changeCamZ(distance);

	this->angle = temp;
}

void Cammera::rotate(float angle) {
	this->angle += angle;
}

/* Camel *************************************************************/
Animal::Animal()
{
}
Animal::~Animal() {

}

void Animal::update(Vector3 pos, float angle, bool frontLeft, bool frontRight, bool backLeft, bool backRight)
{
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;

	this->angle = angle;

	this->clFrontLeft.increasing = frontLeft;
	this->clFrontRight.increasing = frontRight;
	this->clBackLeft.increasing = backLeft;
	this->clBackRight.increasing = backRight;
}

// Obtain the angular transformation by offsetting the x and z axes
float Animal::atan_degrees_360(float opp, float adj) {
	if (adj == 0) {
		if (opp > 0) {
			return 90;
		}
		else {
			return -90;
		}
	}
	else {
		if (adj >= 0) {
			return atan(opp / adj) / TO_RAD;
		}
		else {
			return 180 + atan(opp / adj) / TO_RAD;
		}
	}
}


void Animal::drawEye() {
	glPushMatrix();
	glColor4fv(white);
	glScalef(1, 1, 0.3);
	glutSolidTorus(0.5, 1, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glColor4fv(black);
	glScalef(0.5, 0.5, 0.15);
	glutSolidTorus(1, 1, 16, 16);
	glPopMatrix();
}
void Animal::drawAnimalLeg(Leg* animalLeg, float legColor[]) {
	glScalef(1.5, 1, 1.5);

	glTranslatef(0, 5, 0);
	glRotatef(animalLeg->angle, 1, 0, 0);
	glTranslatef(0, -5, 0);

	// upper
	glPushMatrix();
	glColor4f(legColor[0], legColor[1], legColor[2], legColor[3]);
	glScalef(1, 10, 1);
	glutSolidCube(1);
	glPopMatrix();

	// top of hoof
	glPushMatrix();
	glColor4f(0.9, 0.85, 0.7, 1);
	glTranslatef(0, -5, 0);
	glutSolidCube(1);
	glPopMatrix();

	// bottom of hoof
	glPushMatrix();
	glColor4f(0.4, 0.3, 0.1, 1);
	glTranslatef(0, -6, 0);
	glutSolidCube(1);
	glPopMatrix();

	glColor4f(0.8, 0.7, 0.5, 1);
}
void Animal::drawAnimal(float color[], float legColor[]) {
	glColor4f(color[0], color[1], color[2], color[3]);

	glPushMatrix();
	glScalef(6, 8, 10);
	glutSolidCube(1);
	glPopMatrix();

	// hump
	glPushMatrix();
	glTranslatef(0, 3.5, -2);
	glScalef(2.5, 5, 3);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();

	// NECK //
	glPushMatrix();
	glTranslatef(0, 0, 6.5);
	glScalef(3, 4, 3);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 5, 7.25);
	glScalef(2, 6, 1.5);
	glutSolidCube(1);
	glPopMatrix();


	// HEAD //
	// back of head
	glPushMatrix();
	glTranslatef(0, 10, 8);
	glScalef(3, 4.5, 3);
	glutSolidCube(1);
	glPopMatrix();

	// front of head
	glPushMatrix();
	glTranslatef(0, 9.5, 10.75);
	glScalef(2, 3.5, 2.5);
	glutSolidCube(1);
	glPopMatrix();

	// left eye
	glPushMatrix();
	glTranslatef(1.5, 10.5, 8.5);
	glScalef(0.4, 0.4, 0.4);
	glRotatef(90, 0, 1, 0);
	drawEye();
	glPopMatrix();

	// right eye
	glPushMatrix();
	glTranslatef(-1.5, 10.5, 8.5);
	glScalef(0.4, 0.4, 0.4);
	glRotatef(-90, 0, 1, 0);
	drawEye();
	glPopMatrix();

	glColor4f(legColor[0], legColor[1], legColor[2], legColor[3]);

	// left ear
	glPushMatrix();
	glTranslatef(1.2, 12.5, 6.9);
	glScalef(0.4, 1.5, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	// right ear
	glPushMatrix();
	glTranslatef(-1.2, 12.5, 6.9);
	glScalef(0.4, 1.5, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	// LEGS //
	// front left leg
	glPushMatrix();
	glTranslatef(2.25, -8, 4.25);
	drawAnimalLeg(&clFrontLeft, legColor);
	glPopMatrix();

	// front right leg
	glPushMatrix();
	glTranslatef(-2.25, -8, 4.25);
	drawAnimalLeg(&clFrontRight, legColor);
	glPopMatrix();

	// back left leg
	glPushMatrix();
	glTranslatef(2.25, -8, -4.25);
	drawAnimalLeg(&clBackLeft, legColor);
	glPopMatrix();

	// back right leg
	glPushMatrix();
	glTranslatef(-2.25, -8, -4.25);
	drawAnimalLeg(&clBackRight, legColor);
	glPopMatrix();

	glColor4fv(white);
}


// Move Animal (position, angle)
void Animal::moveAnimal()
{
	const float CAMEL_MOVE = 0.5;// Adjustment of speed

	static float time;
	float x_change, z_change, angle;

	time += 0.01;

	
	// Time is the final result of change (not a cumulative amount) and cannot be done by moving forward (drift will occur)
	// Here the position, angle and time are directly bound.
	x_change = sin(time);
	z_change = cos(2 * time);
	angle = atan_degrees_360(x_change, z_change);//返回一个角度

	// Camel Location
	this->x += CAMEL_MOVE * x_change;
	this->z += CAMEL_MOVE * z_change;

	// Camel Angle
	this->angle = angle;
}

    // Moving Animals Legs
void Animal::moveAnimalLegs() {
	const float LEG_ANGLE_LOWER = -14, LEG_ANGLE_UPPER = 14;
	const float LEG_ANGLE_CHANGE = 2;

	Leg* legs[4] = { &clFrontLeft, &clFrontRight, &clBackLeft, &clBackRight };
	Leg* leg;

	for (int i = 0; i < 4; i++) {
		leg = legs[i];
		if (leg->increasing) {
			if (leg->angle < LEG_ANGLE_UPPER) {
				leg->angle += LEG_ANGLE_CHANGE;
			}
			else {

				leg->increasing = false;
			}
		}
		else {
			if (leg->angle > LEG_ANGLE_LOWER) {
				leg->angle -= LEG_ANGLE_CHANGE;
			}
			else {
				leg->increasing = true;
			}
		}
	}
}

