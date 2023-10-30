#pragma once
#include "global.h"
#include "TextureLoader.h"
#include "Vector3.h"

//A house
class Room {
public:
    Room()=delete;
    Room(TextureLoader* texLoader);
    ~Room();

    // Scenery (complete room rendering)
    void scene(float px, float py, float pz, int num=0/*Select house model*/);

private:
    Vector3 curPos;

public:

    // Ì¨µÆ
    void lampLight();

public:
    GLboolean bRotate = false;
    GLboolean uRotate = false;

    // Parameters of fan rotation
    GLfloat alpha = 0.0, theta = 0.0, axis_x = 0.0, axis_y = 0.0;

    // Animation
    void animate();

private:
    TextureLoader* texLoader;


private:
    void drawCube(float x, float y, float z, float xheight, float yheight, float zheight, float color[], float shine = 60);


    // interior
    void interior(int basex, int basey, float px, float py, float pz, int num = 0);

    // closet
    void closet(int basex, int basey, float topsize, float px, float py, float pz);

    // bed
    void bed(int basex, int basey, float legsize, float topsize, float px, float py, float pz);


    // table
    void table(int basex, int basey, float legsize, float px, float py, float pz);


    // chair
    void chair(int basex, int basey, float legsize, float topsize, float px, float py, float pz);


    // laptop
    void laptop(int basex, int basey, float px, float py, float pz, float color[]);


    // fan
    void fan(float px, float py, float pz);

    // lamp
    void lamp(float px, float py, float pz, float lamp_bulb_color[]);

    // bulb
    void bulb(float px, float py, float pz, float bulb_color[]);

    // tubelight
    void tubelight(float px, float py, float pz, float tubelight_bulb_color[]);

};


// SquareWarehouse£¨3 houses in a row£©
class SquareWarehouse
{
public:
    SquareWarehouse()=delete;
    SquareWarehouse(TextureLoader* texLoader);
    ~SquareWarehouse();
public:
    void draw(float px, float py, float pz);
    // animation
    void animate();

    void drawCube(float color[]);
public:
    Room room;
    TextureLoader* texLoader;
};

