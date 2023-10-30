#include "Room.h"


Room::Room(TextureLoader* texLoader) { this->texLoader = texLoader; }

Room::~Room() {}

// Scenery (complete room rendering)
void Room::scene(float px, float py, float pz, int num/*Select house model*/)
{
    /*
     Room 2: window, bed, closet, table 2, fan, window wall
     Room 1: table 1, fan
     Room 0: bed, table 2, fan
    */
    if (num < 0 && num > 2) return;

    this->curPos = Vector3(px, py, pz);

    glPushMatrix();
    //scene placement
    glTranslatef(px, py, pz);


    //room
    glPushMatrix();
    interior(100, 90, 0, 0, 0, num);
    glPopMatrix();


    if (num == 2 || num == 1)
    {
        // Closet
        glPushMatrix();
        glTranslatef(22, 43, 4);
        glScalef(1.5, 2.5, 1.5);
        closet(18, 7, 26, 0, 0, 0);
        glPopMatrix();

        // Bed
        glPushMatrix();
        glRotatef(0, 0, 1, 0);
        glTranslatef(85, 17.5, 21);
        glScalef(2, 1.5, 1.5);
        bed(12, 24, 12, 14, 0, 0, 0);
        glPopMatrix();

        // Table 1
        glPushMatrix();
        glRotatef(90, 0, 1, 0);
        glTranslatef(-60, 20, 10);
        glScalef(3, 3, 2);
        table(12, 7, 7, 0, 0, 0);
        glPopMatrix();

        // Chair 1
        glPushMatrix();
        glTranslatef(20, 15, 65);
        glRotatef(-90, 0, 1, 0);
        glScalef(1.5, 2, 1);
        chair(7, 7, 6, 8, 0, 0, 0);
        glPopMatrix();
    }

    if (num == 1)
    {
        // lamp 
        glPushMatrix();
        glTranslatef(10, 19, 52);
        glRotatef(-45, 0, 1, 0);
        glScalef(1, 1, 1);
        lamp(0, 0, 0, white);
        glPopMatrix();
    }


    // Table 2
    glPushMatrix();
    glRotatef(0, 0, 1, 0);
    glTranslatef(50, 22, 10);
    glScalef(1.5, 3, 2);
    table(12, 7, 7, 0, 0, 0);
    glPopMatrix();

    // Chair 2
    glPushMatrix();
    glTranslatef(50, 15, 25);
    glRotatef(180, 0, 1, 0);
    glScalef(1.5, 2, 1);
    chair(7, 7, 6, 8, 0, 0, 0);
    glPopMatrix();


    // Fans
    glPushMatrix();
    glTranslatef(45, 91, 28);
    glRotatef(alpha, axis_x, axis_y, 0.0);
    glRotatef(theta, axis_x, axis_y, 0.0);
    glRotatef(90, 1, 0, 0);
    glScalef(.6, .6, .6);
    fan(0, 0, 0);
    glPopMatrix();


    // bulb 
    glPushMatrix();
    glTranslatef(70, 80, 7);
    glRotatef(0, 0, 1, 0);
    glScalef(.5, .5, .5);
    bulb(0, 0, 0, white);
    glPopMatrix();


    // tubelight 
    glPushMatrix();
    glTranslatef(1, 90, 70);
    glRotatef(-90, 0, 0, 1);
    glRotatef(90, 0, 1, 0);
    glScalef(3, 1, 3);
    tubelight(0, 0, 0, white);
    glPopMatrix();


    glPopMatrix();
}


// Animation
void Room::animate()
{
    // Fan animation
    if (bRotate == true)
    {
        theta += 10.2;
        if (theta > 360.0)
            theta -= 360.0 * floor(theta / 360.0);
    }

    if (uRotate == true)
    {
        alpha += 10.2;
        if (alpha > 360.0)
            alpha -= 360.0 * floor(alpha / 360.0);
    }
}

void Room::drawCube(float x, float y, float z, float xheight, float yheight, float zheight, float color[], float shine)
{
    glColor4fv(color);

    static GLfloat v_cube[8][3] =
    {
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

// Room
void Room::interior(int basex, int basey, float px, float py, float pz, int num)
{

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();


    glTranslatef(px, py, pz);


    //base
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texLoader->texId[FLOOR]);
    glTranslatef(0, 3.5, 1);
    glScalef(basex, 3.5, basey);
    drawCube(0, 0, 0, 1, 1, 1, tiles_white, 110);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //wall1
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM3]);
  

    //wall1
    glPushMatrix();
    glTranslatef(0, 4.5, -3);
    glScalef(basex, basey + 10, 1);
    drawCube(0, 0, 0, 1, 1, 1, light_yellow, 100);
    glPopMatrix();


    //wall2

    glPushMatrix();
    glTranslatef(0, 4.5, -3);
    glScalef(1, basey + 10, basey);
    drawCube(0, 0, 0, 1, 1, 1, light_yellow, 100);
    glPopMatrix();


    if (num == 2) {
        ////wall3.left
        glPushMatrix();
        glTranslatef(100, 4.5, -3);
        glScalef(1, basey + 10, basey - (basey * .6));
        drawCube(0, 0, 0, 1, 1, 1, light_yellow, 100);
        glPopMatrix();

        ////wall3 right
        glPushMatrix();
        glTranslatef(100, 4.5, 51);
        glScalef(1, basey + 10, basey - (basey * .6));
        drawCube(0, 0, 0, 1, 1, 1, light_yellow, 100);
        glPopMatrix();

        //wall 3 down
        glPushMatrix();
        glTranslatef(100, 4.5, -3);
        glScalef(1, basey - (basey * .7), basey);
        drawCube(0, 0, 0, 1, 1, 1, light_yellow, 10);
        glPopMatrix();

        //wall3 up
        glPushMatrix();
        glTranslatef(100, 68, -3);
        glScalef(1, basey - (basey * .7) + 10, basey);
        drawCube(0, 0, 0, 1, 1, 1, light_yellow, 100);
        glPopMatrix();
    }


    //Ceiling
    glPushMatrix();
    glTranslatef(0, 100, -3);
    glScalef(basex, .5, basey);
    drawCube(0, 0, 0, 1, 1, 1, grey, 100);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    if (num == 2)
    {
        //curtain base
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM2]);
        glPushMatrix();
        glTranslatef(98, 70, 30);
        glScalef(1, 5, 25);
        drawCube(0, 0, 0, 1, 1, 1, white, 100);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        //Curtains1
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM1]);
        glPushMatrix();
        glTranslatef(99, 20, 40);
        glRotatef(180, 0, 1, 0);
        glScalef(.5, 52, 8);
        drawCube(0, 0, 0, 1, 1, 1, tiles_white, 100);
        glPopMatrix();

        //Curtains 2
        glPushMatrix();
        glTranslatef(99, 20, 54);
        glRotatef(180, 0, 1, 0);
        glScalef(.5, 52, 3);
        drawCube(0, 0, 0, 1, 1, 1, tiles_white, 100);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

// Wardrobe
void Room::closet(int basex, int basey, float topsize, float px, float py, float pz)
{

    glPushMatrix();
    glTranslatef(px, py, pz);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM2]);

    //basebottom
    glPushMatrix();
    glScalef(basex, 1, basey);
    glTranslatef(-0.5, -12, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    //basetop
    glPushMatrix();
    glScalef(basex, 1, basey);
    glTranslatef(-0.5, 8, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();


    //legs
    glPushMatrix();
    glTranslatef(8.5, -2.5, 3);
    glScalef(1, topsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.5, -2.5, 3);
    glScalef(1, topsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.5, -2.5, -3);
    glScalef(1, topsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.5, -2.5, -3);
    glScalef(1, topsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    //side connector

    glPushMatrix();
    glTranslatef(7, -2, 0);
    glScalef(1, topsize - 3, basey - 2);
    glTranslatef(-0.1, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.5, -2, .5);
    glScalef(1, topsize - 3, basey - 2);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white, 20);
    glPopMatrix();



    //top leg connector
    glPushMatrix();
    glTranslatef(0, -2, -3);
    glScalef(basex - 2, 23, 2.5);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -2, 2.5);
    glScalef(basex - 2, 23, 2.5);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white, 20);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //door
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM3]);

    glPushMatrix();
    glTranslatef(4.5, -2, 3);
    glScalef(basex - 12, 20, 2);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5, -2, 3);
    glScalef(basex - 12, 20, 2);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //handle
    glPushMatrix();
    glTranslatef(2.5, 1.75, 4);
    glScalef(.5, 2, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5, 1.75, 4);
    glScalef(.5, 2, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white, 100);
    glPopMatrix();


    glPopMatrix();


}

// bed
void Room::bed(int basex, int basey, float legsize, float topsize, float px, float py, float pz)
{
    glPushMatrix();
    glTranslatef(px, py, pz);

    //matress
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM2]);
    glPushMatrix();
    glScalef(basex - 1, 1, basey - 1);
    glTranslatef(-0.55, 0, -0.56);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    

    //pillow 
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM6]);
    glPushMatrix();
    glScalef(basex - 5, 2.5, basey - 19);
    glTranslatef(-0.55, 0, -2.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM2]);
    //base
    glPushMatrix();
    glScalef(basex, 4, basey);
    glTranslatef(-0.55, -1, -0.56);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();


    //legs
    glPushMatrix();
    glTranslatef(5, -2.5, 10);
    glScalef(1, legsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, -2.5, 10);
    glScalef(1, legsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, -2.5, -13);
    glScalef(1, legsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, -2.5, -13);
    glScalef(1, legsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(5, 0, -13);
    glScalef(1, topsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0, -13);
    glScalef(1, topsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();


    //top leg connector
    glPushMatrix();
    glTranslatef(-0.55, 1.5, -13);
    glScalef(10, 6, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();



    //leg down top
    glPushMatrix();
    glTranslatef(5, -1, 10);
    glScalef(1, legsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, -1, 10);
    glScalef(1, legsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    //down leg connector

    glPushMatrix();
    glTranslatef(-0.55, 0.75, 10);
    glScalef(10, 5, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


}

// desk
void Room::table(int basex, int basey, float legsize, float px, float py, float pz)
{

    glPushMatrix();
    glTranslatef(px, py, pz);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM2]);

    //base
    glPushMatrix();
    glScalef(basex, 1, basey);
    glTranslatef(-0.55, 0, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();


    //legs
    glPushMatrix();
    glTranslatef(5, -2.5, 3);
    glScalef(.5, legsize, .5);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, -2.5, 3);
    glScalef(.5, legsize, .5);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, -2.5, -3);
    glScalef(.5, legsize, .5);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, -2.5, -3);
    glScalef(.5, legsize, .5);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();


    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


}

// chair
void Room::chair(int basex, int basey, float legsize, float topsize, float px, float py, float pz)
{


    glPushMatrix();
    glTranslatef(px, py, pz);


    //base
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM2]);

    glPushMatrix();
    glScalef(basex, 1, basey);
    glTranslatef(-0.5, 0, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();


    //legs
    glPushMatrix();
    glTranslatef(3, -2.5, 3);
    glScalef(1, legsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3, -2.5, 3);
    glScalef(1, legsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, -2.5, -3);
    glScalef(1, legsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3, -2.5, -3);
    glScalef(1, legsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    //leg top
    glPushMatrix();
    glTranslatef(3, 3, -3);
    glScalef(1, topsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3, 3, -3);
    glScalef(1, topsize, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();


    //top leg connector
    glPushMatrix();
    glTranslatef(0, 4.5, -3);
    glScalef(5, 3, 1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0, 0, 0, 1, 1, 1, white);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


}

// fan
void Room::fan(float px, float py, float pz)
{
    float shine = 60;

    glPushMatrix();
    glTranslatef(px, py, pz);

    //fan base
    glPushMatrix();
    glColor4fv(gold);
    glScalef(1, 1, 1);
    gluCylinder(gluNewQuadric(), 5, 5, 2, 100, 100);
    glPopMatrix();

    //back
    glPushMatrix();
    glColor4fv(gold);
    gluDisk(gluNewQuadric(), 1, 5, 32, 32);
    glPopMatrix();


    //front
    glPushMatrix();
    glColor4fv(gold);
    glTranslatef(0, 0, 2);
    gluDisk(gluNewQuadric(), 0, 5, 32, 32);
    glPopMatrix();

    //cone1
    glPushMatrix();
    glColor4fv(gold);
    glTranslatef(0, 0, -3);
    gluCylinder(gluNewQuadric(), 1, 4, 3, 32, 32);
    glPopMatrix();

    //rod
    glPushMatrix();
    glColor4fv(gold);
    glTranslatef(0, 0, -12);
    gluCylinder(gluNewQuadric(), 1, 1, 10, 32, 32);
    glPopMatrix();

    //cone2
    glPushMatrix();
    glColor4fv(gold);
    glTranslatef(0, 0, -15);
    gluCylinder(gluNewQuadric(), 2.5, 1, 3, 32, 32);
    glPopMatrix();

    //connector1
    glPushMatrix();
    glRotatef(5, 0, 1, 0);
    glTranslatef(-1, 5, 0.5);
    glScalef(2, 4, .7);
    drawCube(0, 0, 0, 1, 1, 1, tiles_white);
    glPopMatrix();

    //connector2
    glPushMatrix();
    glRotatef(5, 0, 1, 0);
    glTranslatef(5, -5, 0.5);
    glRotatef(45, 0, 0, 1);
    glScalef(2, 4, .7);
    drawCube(0, 0, 0, 1, 1, 1, tiles_white);
    glPopMatrix();

    //connector3
    glPushMatrix();
    glRotatef(5, 0, 1, 0);
    glTranslatef(-6, -4, 0.5);
    glRotatef(-45, 0, 0, 1);
    glScalef(2, 4, .7);
    drawCube(0, 0, 0, 1, 1, 1, tiles_white);
    glPopMatrix();

    //blade 1
    glPushMatrix();
    glRotatef(5, 0, 1, 0);
    glTranslatef(-1.8, 6, 0.5);
    glScalef(3.5, 25, .5);
    drawCube(0, 0, 0, 1, 1, 1, orange);
    glPopMatrix();

    //blade2
    glPushMatrix();
    glRotatef(5, 0, 1, 0);
    glTranslatef(20, -21, 0.5);
    glRotatef(45, 0, 0, 1);
    glScalef(3.5, 25, .5);
    drawCube(0, 0, 0, 1, 1, 1, orange);
    glPopMatrix();

    //blade3
    glPushMatrix();
    glRotatef(5, 0, 1, 0);
    glTranslatef(-23, -20, 0.5);
    glRotatef(-45, 0, 0, 1);
    glScalef(3.5, 25, .5);
    drawCube(0, 0, 0, 1, 1, 1, orange);
    glPopMatrix();


    glPopMatrix();

}

// lamp
void Room::lamp(float px, float py, float pz, float lamp_bulb_color[])
{
    glPushMatrix();
    glTranslatef(px, py, pz);

    //base
    glPushMatrix();
    glTranslatef(0, 4.5, -3);
    glScalef(6, 3, 2);
    drawCube(0, 0, 0, 1, 1, 1, cyan);
    glPopMatrix();

    //base decorator
    glPushMatrix();
    glTranslatef(0, 5, -3.1);
    glScalef(6.2, 2, 2.2);
    drawCube(0, 0, 0, 1, 1, 1, dark_blue);
    glPopMatrix();

    //first arm
    glPushMatrix();
    glTranslatef(0, 5, -3);
    glScalef(.5, 15, .5);
    drawCube(0, 0, 0, 1, 1, 1, grey);
    glPopMatrix();


    //second arm

    glPushMatrix();

    glTranslatef(0, 5, -1.5);
    glScalef(.5, 15, .5);
    drawCube(0, 0, 0, 1, 1, 1, grey);
    glPopMatrix();


    //lamp site

    glPushMatrix();
    glRotatef(15, 0, 0, 1);
    glTranslatef(5, 19, -3);
    glScalef(7, 1, 2);
    drawCube(0, 0, 0, 1, 1, 1, cyan);
    glPopMatrix();


    //light area
    glPushMatrix();

    glRotatef(15, 0, 0, 1);
    glTranslatef(5.5, 18.7, -2.8);
    glScalef(6.5, .5, 1.5);
    drawCube(0, 0, 0, 1, 1, 1, lamp_bulb_color);

    glPopMatrix();

    glPopMatrix();
}

// bulb
void Room::bulb(float px, float py, float pz, float bulb_color[])
{
    glPushMatrix();
    glTranslatef(px, py, pz);

    //base cone
    glPushMatrix();
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient1[] = { orange[0] * .3, orange[1] * .3, orange[2] * .3, 1.0 };
    GLfloat mat_diffuse1[] = { orange[0], orange[1], orange[2], 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess1[] = { 60 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
    glTranslatef(0, 0, -15);
    gluCylinder(gluNewQuadric(), 2.5, 1, 1, 32, 32);
    glPopMatrix();

    //extension
    glPushMatrix();
    GLfloat mat_ambient2[] = { orange[0] * .3, orange[1] * .3, orange[2] * .3, 1.0 };
    GLfloat mat_diffuse2[] = { orange[0], orange[1],orange[2], 1.0 };
    GLfloat mat_shininess2[] = { 60 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);
    glTranslatef(0, 0, -14);
    gluCylinder(gluNewQuadric(), 1, 1, 1, 32, 32);
    glPopMatrix();


    //bulb head
    glPushMatrix();
    GLfloat mat_ambient3[] = { bulb_color[0] * .3, bulb_color[1] * .3, bulb_color[2] * .3, 1.0 };
    GLfloat mat_diffuse3[] = { bulb_color[0], bulb_color[1], bulb_color[2], 1.0 };
    GLfloat mat_shininess3[] = { 60 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess3);
    glTranslatef(0, 0, -12);
    gluSphere(gluNewQuadric(), 2, 32, 32);

    glPopMatrix();



    glPopMatrix();
}

// tubelight
void Room::tubelight(float px, float py, float pz, float tubelight_bulb_color[])
{
    glPushMatrix();
    glTranslatef(px, py, pz);


    //base
    glPushMatrix();
    glScalef(6.5, .5, .7);
    drawCube(0, 0, 0, 1, 1, 1, orange);
    glPopMatrix();

    //left connector
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(.5, 1.5, .7);
    drawCube(0, 0, 0, 1, 1, 1, orange);

    glPopMatrix();

    //right connector
    glPushMatrix();
    glTranslatef(6, 0, 0);
    glScalef(.5, 1.5, .7);
    drawCube(0, 0, 0, 1, 1, 1, orange);

    glPopMatrix();

    //tube
    glPushMatrix();
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient1[] = { tubelight_bulb_color[0] * .3, tubelight_bulb_color[1] * .3,tubelight_bulb_color[2] * .3, 1.0 };
    GLfloat mat_diffuse1[] = { tubelight_bulb_color[0], tubelight_bulb_color[1], tubelight_bulb_color[2], 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess1[] = { 60 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
    glTranslatef(0, 1, .3);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), .3, .3, 6, 32, 32);
    glPopMatrix();



    glPopMatrix();
}

/*** SquareWarehouse *******************************************************************/

SquareWarehouse::SquareWarehouse(TextureLoader* texLoader):room(texLoader)
{
    this->texLoader = texLoader;
}

SquareWarehouse::~SquareWarehouse() {}


void SquareWarehouse::drawCube(float color[])
{
    glColor4fv(color);

    static GLfloat v_cube[8][3] =
    {
        //{ 0.0, 0.0, 0.0 }, //0
        //{ 0.0, 0.0, 1.0 }, //1
        //{ 1.0, 0.0, 1.0 }, //2
        //{ 1.0, 0.0, 0.0 }, //3
        //{ 0.0, 1.0, 0.0 }, //4
        //{ 0.0, 1.0, 1.0 }, //5
        //{ 1.0, 1.0, 1.0 }, //6
        //{ 1.0, 1.0, 0.0 }  //7


        { 0.0, 0.0, 0.0 }, //0
        { 0.0, 0.0, 1.0 }, //1
        { 1.0, 0.0, 1.0 }, //2
        { 1.0, 0.0, 0.0 }, //3
        { 0.2, 1.0, 0.2 }, //4
        { 0.2, 1.0, 0.8 }, //5
        { 0.8, 1.0, 0.8 }, //6
        { 0.8, 1.0, 0.2 }  //7
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

void SquareWarehouse::draw(float px, float py, float pz)
{

    // Draw three house subjects
    this->room.scene(px + 100, py, pz, 2); // The rightmost house
    this->room.scene(px, py, pz, 1); // The middle house 
    this->room.scene(px - 100, py, pz, 0); // The leftmost house


    // Drawing the roof of the square cabin
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texLoader->texId[NUM2]);
    glPushMatrix();
    glTranslatef(px - 100, py, pz);

    //Ceilings
    glPushMatrix();
    glTranslatef(0, 104, -3);
    glScalef(300.0,   40.0,   90.0);
    drawCube(grey);
    glPopMatrix();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

// Animation

void SquareWarehouse::animate() 
{
    this->room.animate();
}
