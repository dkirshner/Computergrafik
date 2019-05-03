#pragma once

//zur ermittlung von Pi
//zum einbezug mathematischer Konstanten macro -> _USE_MATH_DEFINES 
#define _USE_MATH_DEFINES

#include <cmath>
/*
Mathematical Expression		C++ Symbol		Decimal Representation
pi								M_PI		3.14159265358979323846
pi/2							M_PI_2		1.57079632679489661923
pi/4							M_PI_4		0.785398163397448309616
1/pi							M_1_PI		0.318309886183790671538
2/pi							M_2_PI		0.636619772367581343076
2/sqrt(pi)						M_2_SQRTPI	1.12837916709551257390
sqrt(2)							M_SQRT2		1.41421356237309504880
1/sqrt(2)						M_SQRT1_2	0.707106781186547524401
e								M_E			2.71828182845904523536
log_2(e)						M_LOG2E		1.44269504088896340736
log_10(e)						M_LOG10E	0.434294481903251827651
log_e(2)						M_LN2		0.693147180559945309417
log_e(10)						M_LN10		2.30258509299404568402
*/

#include <vector>
#include <iostream>	
using namespace std;

//////////////////////////////////////////////////////////

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"

//////////////////////////////////////////////////////////

#define WINDOW_TITLE_PREFIX "Aufgabenblatt 2"

//------------------------------------ Globale Variablen: ------------------------------------------------
//Struktur zum Speichern von Daten für Objektwiedergabe
struct Object
{
	/* IDs for several buffers. */
	// OpenGL Type ->GLuint: Unsigned binary integer (Bitdepth 32)
	GLuint vao;							//	VAO (Vertex Array Object)

	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;

	/* Model matrix */
	glm::mat4x4 model;	// GLM Type: 4 * 4 matrix of double-precision floating-point numbers
};

int glutID = 0;					// GLUT window id/handle

cg::GLSLProgram program;		// shader program
glm::mat4x4 view;				// GLM Type: 4 * 4 matrix of double-precision floating-point numbers
glm::mat4x4 projection;			// GLM Type: 4 * 4 matrix of double-precision floating-point numbers

float zNear = 0.1f;
float zFar = 100.0f;

std::vector<Object> Triangle;	// Vektor wo alle Dreiecke gespeichert werden aus denen der Kreis entsteht

//für den Bereich 3 <= n <= 30
const int MIN_COUNT_TRIANGLE = 3;
const int MAX_COUNT_TRIANGLE = 30;

// Current dimensions of the window:
// Standard window width	
const int WINDOW_WIDTH = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;

int iCountTriangle = MIN_COUNT_TRIANGLE + 2;// 5-Eck darstellung zum Programmstart(n=5) 
int iTaskNr = 1; //Anzeige ersten Aufgabenteils mit "1" zum Anzeigen von Aufgabenteil "2" drücken
double dRadiusApproxCircle = 1.0; //Radius vergrößern("q") und verkleinern("w") 

///////////////////////////////////// Prototypen /////////////////////////////////////
void renderTriangle(Object a_triangle);
void initTriangle(const std::vector<glm::vec3> a_vertices, const std::vector<glm::vec3> a_colors, Object& a_triangle);
bool initAllTriangles(void);
void renderCircle();
