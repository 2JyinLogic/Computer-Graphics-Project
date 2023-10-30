#pragma once

#include "Vector3.h"
#include "global.h"

/* MoveObject *************************************************************/
class MoveObject
{
public:
	MoveObject();
	virtual void update(Vector3 pos, float angle);



	Vector3 pos();// Position
	Vector3 lookAt();// Direction

	~MoveObject();



public:
	float x;
	float y;
	float z;
	float angle; // Radian system
};

/* Cammera *************************************************************/
class Cammera : public MoveObject 
{
public:
	Cammera();
	~Cammera();

	void verticalMove(float distance);
	void horizontalMove(float distance);
	void leftMove(float distance);
	void rightMove(float distance);
	void rotate(float angle);

private:
	void changeCamX(float amount);
	void changeCamZ(float amount);

};


/* animal *************************************************************/
class Animal : public MoveObject
{
public:
	//Leg
	struct Leg {
		bool increasing = false;
		float angle = 0;
	} clFrontLeft, clFrontRight, clBackLeft, clBackRight;// animal leg

public:
	Animal();
	~Animal();

	// Position, orientation, alternate foot state
	void update(Vector3 pos, float angle, bool frontLeft = true, bool frontRight = false, bool backLeft = true, bool backRight = false);

public:
	// Draw animal
	void drawEye();
	void drawAnimalLeg(Leg* camelLeg, float legColor[]);
	void drawAnimal(float color[], float legColor[]);


	//Move animal
	void moveAnimal();
	//Move animals' legs
	void moveAnimalLegs();


private:
	float atan_degrees_360(float opp, float adj); //Animal walk 8 special angle conversion function
};