#pragma once
#include "global.h"
#include "TextureLoader.h"

/* StaticObject **********************************************************/
class StaticObject {
public:
	StaticObject()=delete;
	StaticObject(TextureLoader* loader);
	~StaticObject();

protected:
	TextureLoader* texLoader;
};

class Ground : public StaticObject {
public:
	Ground() = delete;
	Ground(TextureLoader* loader);
	~Ground();


	void drawGround();
};




/* Floor **********************************************************/
class MFloor : public StaticObject
{
public:
	MFloor() = delete;
	MFloor(TextureLoader* loader);
	~MFloor();

	void drawFloor(int min, int max, int inc, Texture tex);

private:

};

/* Door **********************************************************/
//це

class Cammera;
class Door : public StaticObject
{
public:
	Door()=delete;
	Door(TextureLoader* loader);
	~Door();
	
	void drawDoor();
	void moveDoors(Cammera & cam);

public:
	bool open = false;
	bool opening = false;
	bool closing = false;
	float angle = 0;

};

/* Pyramid **********************************************************/

class Pyramid : public StaticObject
{
public:
	Pyramid() = delete;
	Pyramid(TextureLoader* loader);
	~Pyramid();

	void drawPyramid(bool reversed);
	void drawPyramidion();
	void drawCompletePyramid();

public:
	Door doorState; // Open/closeable door
};


/* Warehouse *******************************************************/

class Warehouse : public StaticObject
{
public:
	Warehouse() = delete;
	Warehouse(TextureLoader* loader);
	~Warehouse();

	// drawWarehouse
	void drawWarehouse(bool reversed);
	void drawCompleteWarehouse();

public:
	Door doorState; // Open/closeable door
};

/* н╖г╫ Fencing *******************************************************/

class Fencing : public StaticObject
{
public:
	Fencing() = delete;
	Fencing(TextureLoader* loader);
	~Fencing();

public:
	// Draw a fence
	void drawOne(bool horizontal = true);

	// Drawing the fence (px, py, pz: coordinates), (num: length of the enclosure) (horizontal: horizontal or vertical orientation)
	void drawMulti(float px, float py, float pz, int num = 1, bool horizontal = true);

};