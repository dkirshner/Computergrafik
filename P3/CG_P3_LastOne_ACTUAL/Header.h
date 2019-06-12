#pragma once

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"
#include "GraphicObject.h"

#define M_PI 3.14159265358979323846

#include <iostream>	// i/o cout()
#include <vector>
using namespace std;

#define WINDOW_TITLE_PREFIX "Praktikum Komputergrafik: Aufgabeblatt 3"

// Radius der Kreises
double dRadius = 0.5;			// init
unsigned short iSubdivision = 0, iPrevSubdivision = 0;	// init 
double X_VIEW = -3.0f, Y_VIEW = -3.0f, Z_VIEW = -3.0f; //view Matrix
// Standard Fensterbreite
const int WINDOW_WIDTH = 940;
// Standard Fensterhöhe
const int WINDOW_HEIGHT = 680;
// GLUT: Fenster ID / Handle
int glutID = 0;

cg::GLSLProgram program;	// Schader-programm

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

vector<GLushort> indicesSphere_0, indicesSphere_1, indicesSphere_2, indicesSphere_3;
vector<glm::vec3> colorsSphere_0, colorsSphere_1, colorsSphere_2, colorsSphere_3;
vector<glm::vec3> verticesSphere_0, verticesSphere_1, verticesSphere_2, verticesSphere_3;

// 
// Konstruiere Dreiecke. Diese Vektoren können den Gültigkeitsbereich verlassen, nachdem wir alle Daten an die Grafikkarte gesendet haben.
// Jede Seite hat zwei Dreiecke mit 3 Eckpunkten

vector<glm::vec3> verticesSphere = {	// Punkte der Dreiecke
	{ 0.5f, 0.0f, -0.5f }, //front
	{ 0.5f, 0.0f,  0.5f },
	{ 0.0f, 0.87f, 0.0f },

	{ -0.5f, 0.0f, 0.5f },
	{ -0.5f, 0.0f, -0.5f },
	{ 0.0f, -0.87f, 0.0f }
};

vector<glm::vec3> colorsSphere = {	// Einheitliche Farbe gelb!
	{ 1.0f, 1.0f, 0.0f }, // front
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f },

	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f }, // end front

	{ 1.0f, 1.0f, 0.0f }, //bottom
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f },

	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f }, // end bottom

	{ 1.0f, 1.0f, 1.0f }, // left
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },

	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f }, // end left

	{ 1.0f, 1.0f, 0.0f }, // right
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f },

	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f }  // end right
};

// Die Indizes der Punkte, von vorne beginnend
vector<GLushort>indicesSphere = {
	0, 1, 2, 
	2, 1, 3,
	2, 3, 4,
	2, 4, 0,
	5, 4, 0,  
	5, 1, 0,
	5, 1, 3, 
	5, 3, 4
};

/*
Struct zum Speichern von Daten für das Rendern von Objekten.
*/
struct Object
{
	/* IDs für mehrere Puffers. */
	// OpenGL Type ->GLuint: Unsigned binary integer (Bitdepth 32)
	GLuint vao;							//	VAO (Vertex Array Object)

	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;

	/* Model matrix */
	glm::mat4x4 model;	// GLM Type: 4 * 4 Matrix von Gleitkommazahlen mit doppelter Genauigkeit
};

Object Sphere;	// Aktuelles Objekt Kugel
std::vector<Object> SpherePieses;	// Aktueller Vektor wo alle Kugelteile gespeichert werden aus denen der Kugel entsteht
std::vector<Object> SpherePieses_2;	// Vektor wo 2 Kugelhelfte gespeichert werden aus denen der Kugel entsteht
std::vector<Object> SpherePieses_3;	// Vektor wo 8 Kugelteile gespeichert werden aus denen der Kugel entsteht

// Axis (zur Darstellung der Koordinatenachsen)
GraphicObject XAxis, YAxis, ZAxis;