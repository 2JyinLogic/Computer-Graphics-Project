#include <iostream>
#include <fstream>

#include "global.h"
#include "TextureLoader.h"
#include "Skybox.h"
#include "MoveObject.h"
#include "StaticObject.h"
#include "Room.h"



using namespace std;

// mapping loader()
TextureLoader* texLoader;

// Skybox
Skybox* skybox;

//Static object: (construction needs to be first into the mapper, so use the pointer form)
Ground* ground; //ground
MFloor* ff; //floor
Warehouse* warhouse; //warehouse
SquareWarehouse* sqhouse; // house
Fencing* fencing; // Fence



//Dynamic objects: camera, animal
Cammera cam;
Animal animal;

//Switch
bool charCamEnabled = false;// (camera view) (animal view) toggle switch

// Mouse to control the camera view
bool bCameraRotate = false;   //  Whether the camera is allowed to rotate
int lastMousePosX, lastMousePosY;  //  Last mouse position  


//Global parallel light 8, camera torch light 9
GLboolean bulb_switch = false, tube_switch = false;
GLboolean bulb_ambient_light = true, bulb_diffusion_light = true, bulb_specular_light = true;
GLboolean tube_ambient_light = true, tube_diffusion_light = true, tube_specular_light = true;



void initLight() 
{
	//On light function (light source setting is valid only when it is on), if not, the original value of color is displayed
	glEnable(GL_LIGHTING);


	// LIGHT1 (Global parallel light source) Light source position, switch 8
	float lpos_0[4] = { -1000.0, 1000.0, 1000.0, 1.0 };  //light's position
	glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos_0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);


}
 
// initialize
void initialize() {
	//Texture mapping loader
	texLoader = new TextureLoader(6 + 6 + 4 + 5);//Preset 22 texture maps (more can be added), up to the maximum of the TextureLoader member variable array
	texLoader->loadGLSkyboxTextures("textures/skybox/left.tga", SKYBOX_LEFT);
	texLoader->loadGLSkyboxTextures("textures/skybox/front.tga", SKYBOX_FRONT);
	texLoader->loadGLSkyboxTextures("textures/skybox/right.tga", SKYBOX_RIGHT);
	texLoader->loadGLSkyboxTextures("textures/skybox/back.tga", SKYBOX_BACK);
	texLoader->loadGLSkyboxTextures("textures/skybox/top.tga", SKYBOX_TOP);
	texLoader->loadGLSkyboxTextures("textures/skybox/down.tga", SKYBOX_BOTTOM);

	texLoader->loadGLSkyboxTextures("textures/skybox/night_left.tga", SKYBOX_NIGHT_LEFT);
	texLoader->loadGLSkyboxTextures("textures/skybox/night_front.tga", SKYBOX_NIGHT_FRONT);
	texLoader->loadGLSkyboxTextures("textures/skybox/night_right.tga", SKYBOX_NIGHT_RIGHT);
	texLoader->loadGLSkyboxTextures("textures/skybox/night_back.tga", SKYBOX_NIGHT_BACK);
	texLoader->loadGLSkyboxTextures("textures/skybox/night_top.tga", SKYBOX_NIGHT_TOP);
	texLoader->loadGLSkyboxTextures("textures/skybox/night_down.tga", SKYBOX_NIGHT_BOTTOM);

	texLoader->loadGLTextures("textures/sand.tga", SAND);
	texLoader->loadGLTextures("textures/sandstone_brick.tga", SANDSTONE_BRICK);
	texLoader->loadGLTextures("textures/floor.tga", FLOOR);
	texLoader->loadGLTextures("textures/grass.tga", GRASS);
	texLoader->loadGLTextures("textures/room/1.tga",  NUM1);
	texLoader->loadGLTextures("textures/room/2.tga",  NUM2);
	texLoader->loadGLTextures("textures/room/3.tga",  NUM3);
	texLoader->loadGLTextures("textures/room/6.tga",  NUM6);

	//initialize skybox
	skybox = new Skybox(texLoader);

	// Initializing the light source
	initLight();


	// background colour
	glClearColor(0, 0, 0, 0);//Background colour

	// Turn on the depth test£¨z-buffer£©
	glEnable(GL_DEPTH_TEST);
	// Turn on normalization (to ensure the stability of the operation)
	glEnable(GL_NORMALIZE);


	// Set (projection matrix) to the current matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//Standardization
	// fovy£¬aspect£¬zNear£¬zFar
	gluPerspective(60, 1, 1, 10000);  //The camera view volume



	// Initialize the camera (position, angle)
	cam.update(Vector3(-250.0, 45.0, 650.0f), 45.0 + 220.0);
	// Initialize the camel (position, angle, alternate feet)
	animal.update(Vector3(0.0,15.0, -220.0), 0.0f, true, false, true, false);

	// Static object initialization
	ground = new Ground(texLoader);
	ff = new MFloor(texLoader);
	warhouse = new Warehouse(texLoader);
	sqhouse = new SquareWarehouse(texLoader);
	fencing = new Fencing(texLoader);
}

/// Display
void display() 
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //GL_LINE = Wireframe;   GL_FILL = Solid
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//Set viewport (animal and free camera switching)
	if (charCamEnabled) {
		float angleInRads = animal.angle * TO_RAD;

		gluLookAt(animal.x, animal.y + 15, animal.z, //animal0 position
			animal.x + 100 * sin(angleInRads), animal.y, animal.z + 100 * cos(angleInRads), //animal0 Direction
			      0, 1, 0);
	}
	else {
		auto camPos = cam.pos();
		auto camLookAt = cam.lookAt();
		gluLookAt(camPos.x, camPos.y, camPos.z, //cammera position
				  camLookAt.x, camLookAt.y, camLookAt.z, //cammera Direction
			      0, 1, 0);
	}

	//Draw skybox
	glPushMatrix();
	glTranslatef(0, -2000, 0);
	glScalef(5, 4, 5);
	if (bulb_switch == false)
		skybox->drawSkyboxNight();
	else
		skybox->drawSkybox();


	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
	
	// Mapping the complete warehouse
	glPushMatrix();
	warhouse->drawCompleteWarehouse();
	glPopMatrix();


	// Rendering of the floor (inside the warehouse)
	glPushMatrix();
	glTranslatef(100, 0.08, -100);
	ff->drawFloor(-75, 75, 15, FLOOR);
	glPopMatrix();

	// Flooring in the fence
	glPushMatrix();
	glTranslatef(-150, 0.05, -50);
	ff->drawFloor(-450, 450, 50, GRASS);
	glPopMatrix();


	// Draw animal1
	glPushMatrix();
	glTranslatef(animal.x, animal.y, animal.z);
	glRotatef(animal.angle, 0, 1, 0);
	animal.drawAnimal(orange, chair_wood);
	glPopMatrix();

	// Draw animal2
	glPushMatrix();
	glTranslatef(animal.x- 100, animal.y, animal.z-100);
	glRotatef(animal.angle, 0, 1, 0);
	animal.drawAnimal(red, light_green);
	glPopMatrix();

	// Draw animal3
	glPushMatrix();
	glTranslatef(animal.x - 500, animal.y+18, animal.z + 500);
	glRotatef(animal.angle, 0, 1, 0);
	glScalef(2.5, 2.5, 2.5);
	animal.drawAnimal(orange, orange);
	glPopMatrix();


	//square house
	sqhouse->draw(-400, -2, -150); //The location of the house in the middle of the square house
	sqhouse->draw(-400, -2, 50); //The location of the house in the middle of the square barn
	//sqhouse->room.lampLight(); // Turn on the desk lamp function 
	
	
	// Drawground
	glPushMatrix();
	ground->drawGround();
	glPopMatrix();

	// Draw fance
	glPushMatrix();
	fencing->drawMulti(-600, -2, -500, 20, false);
	fencing->drawMulti(-600, -2, -500, 20, true);
	fencing->drawMulti(300, -2, -500, 20, true);
	fencing->drawMulti(-600, -2, 400, 20, false);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);

	glutSwapBuffers();
	glFlush();
}

// animation
void animate()
{
	// the animation of the house
	sqhouse->animate();

	glutPostRedisplay(); //The current window needs to be redrawn
}

// Keyboard Functions
void keyboard(unsigned char key, int x, int y) {
	const float MOVE_DISTANCE = 10.0;//Movement speed
	switch (key) {
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'w':
		if (!charCamEnabled) {
			cam.horizontalMove(MOVE_DISTANCE);
		}
		break;
	case 's':
		if (!charCamEnabled) {
			cam.horizontalMove(-MOVE_DISTANCE);
		}
		break;
	case 'a':
		if (!charCamEnabled) {
			cam.leftMove(MOVE_DISTANCE);
		}
		break;
	case 'd':
		if (!charCamEnabled) {
			cam.rightMove(MOVE_DISTANCE);
		}
		break;
	case 'f': // switch of fan 
		sqhouse->room.bRotate = !sqhouse->room.bRotate;
		sqhouse->room.uRotate = false;
		sqhouse->room.axis_x = 0.0;
		sqhouse->room.axis_y = 1.0;
		break;
	case 'g': // the view of the animal
		charCamEnabled = !charCamEnabled;
		break;
	case '8': //to turn on and off global lighting
		if (bulb_switch == false)
		{
			bulb_switch = true; bulb_ambient_light = true; bulb_diffusion_light = true; bulb_specular_light = true;
			glEnable(GL_LIGHT0); break;
		}
		else if (bulb_switch == true)
		{
			bulb_switch = false; bulb_ambient_light = false; bulb_diffusion_light = false; bulb_specular_light = false; 
			glDisable(GL_LIGHT0); break;
		}
		break;
	case '9': //to turn on and off tubelight
		if (tube_switch == false)
		{
			tube_switch = true; tube_ambient_light = true; tube_diffusion_light = true; tube_specular_light = true;
			
			GLfloat cam_pos[] = { cam.pos().x, cam.pos().y, cam.pos().z };// Current position of the camera
			GLfloat spot_direction[] = { cam.lookAt().x, cam.lookAt().y, cam.lookAt().z };// The direction the camera is looking
			glEnable(GL_LIGHT1);
			glLightfv(GL_LIGHT1, GL_POSITION, cam_pos);
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15);// Lighting Angle
			break;
		}
		else if (tube_switch == true)
		{
			tube_switch = false; tube_ambient_light = false; tube_diffusion_light = false; tube_specular_light = false;
			glDisable(GL_LIGHT1); break;
		}
		break;
	}
	glutPostRedisplay();
}

// Mouse function, click the right button to allow movement of the camera, release the right button that does not allow movement
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		bCameraRotate = true;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		bCameraRotate = false;
	}
}

// Mouse movement function, the right button pressed to move that swing the camera
void motion(int x, int y)
{
	const float CHANGE_VIEW_ANGLE = 2;//rotation speed
	const float MOVE_DISTANCE = 2;//move speed

	y = 600 - y;
	if (bCameraRotate)
	{
		if (x > lastMousePosX) // right
		{
			cam.rotate(CHANGE_VIEW_ANGLE);
			lastMousePosX = x;
		}
		else if (x < lastMousePosX) // left
		{
			cam.rotate(-CHANGE_VIEW_ANGLE);
			lastMousePosX = x;
		}
	}

	glutPostRedisplay();
}


void special(int key, int x, int y) {
	const float CHANGE_VIEW_ANGLE = 10;//rotation speed
	const float MOVE_DISTANCE = 10;//move speed

	switch (key) {
	case GLUT_KEY_LEFT:// The camera turns to the left
		if (!charCamEnabled) {
			cam.rotate(-CHANGE_VIEW_ANGLE);
		}
		break;
	case GLUT_KEY_RIGHT:// The camera turns to the right
		if (!charCamEnabled) {
			cam.rotate(+CHANGE_VIEW_ANGLE);
		}
		break;
	case GLUT_KEY_UP:// The camera moves forward
		if (!charCamEnabled) {
			cam.verticalMove(MOVE_DISTANCE);
		}
		break;
	case GLUT_KEY_DOWN:// The camera moves backwards
		if (!charCamEnabled) {
			cam.verticalMove(-MOVE_DISTANCE);
		}
		break;
	}

	glutPostRedisplay();
}



//////////////////////////////////// Animation
// Timer (update animals)
void timer(int value) {
	// warhouse's door moves
	warhouse->doorState.moveDoors(cam);
	

	//animal move
	animal.moveAnimal();
	//animals' legs move
	animal.moveAnimalLegs();
	
	//fix
	glutPostRedisplay();//redisplay
	glutTimerFunc(25, timer, 0);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1200, 720);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("3D Modelling Project");

	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTimerFunc(25, timer, 0);
	glutDisplayFunc(display);
	glutIdleFunc(animate);
 
	initialize();

	glutMainLoop();
	return 0;
}

