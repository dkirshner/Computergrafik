#pragma once

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"

#include "GraphicObject.h" // linien für Achsen der Planeten
/////////////////////////////////
#include <vector>
#include <array>
#include <iostream>	// i/o cout()

using namespace std;

#define M_PI 3.14159265358979323846

extern cg::GLSLProgram program;



/*
Struct to hold data for object rendering.
*/
struct Object
{


	/* IDs for several buffers. */
	GLuint vao;

	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;

	/* Model matrix */
	glm::mat4x4 model;

	short iID;
};

// extern: any source file that includes this will be able to use "indicesSphere", "colorsSphere" und "verticesSphere"
//extern  vector<GLushort> indicesSphere;
extern array< vector<GLushort>, 11> indicesSphereArr; // indicesSphereArr[0].push_back( 1 );
													  //extern  vector<glm::vec3> colorsSphere;
extern array<vector<glm::vec3>, 11> colorsSphereArr; // indicesSphereArr[0].push_back( 1 );
													 //extern  vector<glm::vec3> verticesSphere;
extern array<vector<glm::vec3>, 11> verticesSphereArr; // indicesSphereArr[0].push_back( 1 );

extern array<vector<Object>, 11> SpherePiesesArr; // SphereArrr[0].push_back( Sun );

// Axis (zur Darstellung der Koordinatenachsen)
extern GraphicObject AxisSun, AxisPlanetSlope, AxisPlanetStraight;
extern GLfloat rotateZ;
extern GLfloat rotateZAxis;
//////////////////////////////////////////////////////////////////////////////
// 	GLuint programId = program.getHandle();
void initSphere(GLuint a_programId, Object* a_Sun, double a_dRadius, int a_iID, bool a_bSubDivReset = false);

// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// Axis (zur Darstellung der Koordinatenachsen)
// Initialisiere Achse für Sonne
void initAxisSun(GLuint a_programId);
// Initialisiere Achse für den geneigten Planeten
void initAxisPlanetSlope(GLuint a_programId);
void initAxisPlanetStraight(GLuint programId);
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// Ist schon ein Punkt in einer aktuellen Liste enthalten
bool IsVertexSaved(glm::vec3 a_Pnt, int *a_Index, int a_iID);
// clear actual data
bool ClearActualData(const int a_iID);
// Werte von n=0 bis n= 3 sichern bei "+" und
// Werte von n = 0 bis n =
///////////////////////////////////////////////////////////////////////////////
// Mittelpunkt von 2 Eckpunkten finden
// HINWEIS: Die Größe des neuen Scheitelpunkts muss geändert werden, damit die Länge dem Radius entspricht
///////////////////////////////////////////////////////////////////////////////
void computeHalfVertex(glm::vec3 v1, glm::vec3 v2, glm::vec3 *newV, const double a_dRadius);

// Der Unterteilungsalgorithmus teilt die drei Kantenlinien jedes Dreiecks in zwei Hälften und 
// extrudiert dann den neuen Mittelpunkt nach außen, sodass seine Länge(der Abstand vom Mittelpunkt)
// dem Radius der Kugel entspricht.
int SubDivisionAlgorithm(const double a_dRadius, Object* a_Sphere);

void initBaseSphere(int a_iId);