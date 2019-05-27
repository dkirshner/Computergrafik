#pragma once

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"

/*
Struct to hold data for object rendering.
*/
struct Object
{
	inline Object()
		: vao(0),
		positionBuffer(0),
		colorBuffer(0),
		indexBuffer(0)
	{}

	/* IDs for several buffers. */
	GLuint vao;

	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;

	/* Model matrix */
	glm::mat4x4 model;
};

void init_Y_Axis_Sun(GLuint programId, Object* a_pY_AxisSun);
void init_Y_Axis_Planet(GLuint programId, Object* a_Y_AxisMoon, Object a_PlanetGrade);
void initY_AxisMoonSlope(GLuint programId, Object* a_Y_AxisMoonSlope, Object a_Planetschief);

void initWireSphere(GLuint programId, Object* a_Sonne);					//Planet Sonne im Ursprung
void initWireSphereSchief(GLuint programId, Object* a_Planetschief);	//gekippter Planet der Um die Sonne Rotiert
void initWireSphereGrade(GLuint programId, Object* a_PlanetGrade);		// senkrechter Planet der um die Sonne Rotiert

void initWireSpheremoon1(GLuint programId, Object* a_moon1, Object a_PlanetGrade);
void initWireSpheremoon2(GLuint programId, Object* a_moon2, Object a_PlanetGrade);
void initWireSpheremoon3(GLuint programId, Object* a_moon3, Object a_PlanetGrade);
void initWireSpheremoon4(GLuint programId, Object* a_moon4, Object a_PlanetGrade);

void initWireSpheremoon5(GLuint programId, Object* a_moon5, Object a_Planetschief);
void initWireSpheremoon6(GLuint programId, Object* a_moon7, Object a_Planetschief);
void initWireSpheremoon7(GLuint programId, Object* a_moon11, Object a_Planetschief);
void initWireSpheremoon8(GLuint programId, Object* a_moon12, Object a_Planetschief);



