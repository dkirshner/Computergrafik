#pragma once

#include <vector>
#include <iostream>	// i/o cout()

using namespace std;

#define WINDOW_TITLE_PREFIX "Praktikum Komputergrafik: Aufgabeblatt 4"

// Standard window width
const int WINDOW_WIDTH = 980;
// Standard window height
const int WINDOW_HEIGHT = 650;

///////////////////////////////////////////////////

// GLUT window id/handle
int glutID = 0;

cg::GLSLProgram program;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

float iVelocity = -0.1f;

// Achsen Y
Object Y_AxisSun;
Object Y_AxisMoon;
Object Y_AxisMoonSlope;

Object moon1; // Mond 1 Für Planet Grade
Object moon2; // Mond 2 Für Planet Grade
Object moon3; // Mond 3 Für Planet Grade
Object moon4; // Mond 4 Für Planet Grade

Object moon5; // Mond 1 mittig für Planet schief
Object moon6; // Mond 2 unterhalb Planet schief
Object moon7; // Mond 3 unterhalb Planet schief
Object moon8; // Mond 4 unterhalb Planet schief

// GLUT geometry für Sonne und Planeten

Object Planetschief;
Object PlanetGrade;
Object Sonne; 
/////////////////////
// Prototypen
void rotate();
/*
Initialization. Should return true if everything is ok and false if something went wrong.
*/
bool init();
/*
Release object resources.
*/
void releaseObject(Object& obj);
/*
Release resources on termination.
*/
void release();

/*
Rendering.
*/
void render();
/*
Resize callback.
*/
void glutResize(int width, int height);
/*
Resize callback.
*/
void glutResize(int width, int height);
/*
Callback for char input.
*/
void glutKeyboard(unsigned char keycode, int x, int y);
void glutDisplay();
