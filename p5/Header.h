#pragma once

#include "Render.h"

#define WINDOW_TITLE_PREFIX "Praktikum Komputergrafik: Aufgabeblatt 4"

// Standard window width
const int WINDOW_WIDTH = 980;
// Standard window height
const int WINDOW_HEIGHT = 650;

///////////////////////////////////////////////////

// GLUT window id/handle
int glutID = 0;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

float iVelocity = -0.1f;

// GLUT geometry für Sonne und Planeten
Object Sun;
Object PlanetSlope;
Object PlanetStraight;

Object MoonSlope_1;
Object MoonSlope_2;
Object MoonSlope_3;
Object MoonSlope_4;
Object MoonStraight_1;
Object MoonStraight_2;
Object MoonStraight_3;
Object MoonStraight_4;
/////////////////////
// Prototypen
void rotatePlanetSystem();
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

