#include <iostream>
#include <vector>

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"
//#include "HE.cpp"


// Standard window width
const int WINDOW_WIDTH = 980;
// Standard window height
const int WINDOW_HEIGHT = 650;
// GLUT window id/handle
int glutID = 0;
cg::GLSLProgram program;




glm::mat4x4 view;
glm::mat4x4 projection;
int zoomstufe = 4;
float Linienanzahl = 10;
float groesseSonne = 0.5;
float groessePlanet = 0.3;
float groesseMond = 0.1;
float zNear = 0.1f;
float zFar  = 100.0f;

float iVelocity = 0.1f;

/*
Struct to hold data for object rendering.
*/
struct Object
{
	inline Object ()
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

Object quad;
Object Y_AxisSun;
Object Y_AxisMoon;
Object Y_AxisMoonSlope;

Object moon1; // Mond 1 F�r Planet Grade
Object moon2; // Mond 2 F�r Planet Grade
Object moon3; // Mond 3 F�r Planet Grade

Object moon4; // Mond 1 mittig f�r Planet schief
Object moon5; // Mond 2 mittig f�r Planet schief

Object moon6; // Mond 1 unterhalb Planet schief
Object moon7; // Mond 2 unterhalb Planet schief
Object moon8; // Mond 3 unterhalb Planet schief
Object moon9; // Mond 4 unterhalb Planet schief

Object moon10; // Mond 1 oberhalb Planet schief
Object moon11; // Mond 2 oberhalb Planet schief
Object moon12; // Mond 3 oberhalb Planet schief
Object moon13; // Mond 4 oberhalb Planet schief

Object Planetschief;
Object PlanetGrade;
Object Sonne; // GLUT geometry

void renderY_AxisSun()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * Y_AxisSun.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);
	
	// Bind vertex array object so we can render the 2 triangles.
	glBindVertexArray(Y_AxisSun.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderY_AxisMoon()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * Y_AxisMoon.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	glBindVertexArray(Y_AxisMoon.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderY_AxisMoonSlope()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * Y_AxisMoonSlope.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	glBindVertexArray(Y_AxisMoonSlope.vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void renderWireSphereSonne()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * Sonne.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(Sonne.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseSonne, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon1()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon1.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon1.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon2()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon2.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon2.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon3()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon3.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon3.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon4()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon4.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon4.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon5()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon5.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon5.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon6()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon6.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon6.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon7()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon7.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon7.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon8()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon8.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon8.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon9()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon9.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon9.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon10()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon10.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon10.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon11()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon11.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon11.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon12()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon12.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon12.vao);

	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpheremoon13()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * moon13.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(moon13.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groesseMond, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpherePlanetschief()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * Planetschief.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(Planetschief.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groessePlanet, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void renderWireSpherePlanetgrade()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * PlanetGrade.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// GLUT: bind vertex-array-object
	// this vertex-array-object must be bound before the glutWireSphere call
	glBindVertexArray(PlanetGrade.vao);


	//glLineWidth(1.0f);
	glutSolidSphere(groessePlanet, Linienanzahl, Linienanzahl);
	//gr��e, linien vertikal, linien horizontal

	// GLUT: unbind vertex-array-object
	glBindVertexArray(0);
}

void initY_AxisSun()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { 0.05f, 1.0f, 0.0f },{ 0.08f, 1.0f, 0.0f },{ 0.08f, -1.0f, 0.0f },{ 0.05f, -1.0f, 0.0f } };
	//color
	const std::vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const std::vector<GLushort> indices = { 0, 1, 2, 0, 2, 3 };

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &Y_AxisSun.vao);
	glBindVertexArray(Y_AxisSun.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &Y_AxisSun.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Y_AxisSun.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &Y_AxisSun.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Y_AxisSun.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &Y_AxisSun.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Y_AxisSun.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	Y_AxisSun.model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.07f, 0.0f, 0.0f));
}

void initY_AxisMoon()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { 0.0f, 0.55f, 1.0f },{ 0.0f, 0.58f, 1.0f },{ 0.0f, -0.58f, -1.0f },{ 0.0f, -0.55f, -1.0f } };
	//color
	const std::vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const std::vector<GLushort> indices = { 0, 1, 2, 0, 2, 3 };

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &Y_AxisMoon.vao);
	glBindVertexArray(Y_AxisMoon.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &Y_AxisMoon.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Y_AxisMoon.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &Y_AxisMoon.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Y_AxisMoon.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &Y_AxisMoon.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Y_AxisMoon.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	Y_AxisMoon.model = glm::translate(PlanetGrade.model, glm::vec3(0.0f, 0.0f, 0.0f));
}

void initY_AxisMoonSlope()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { 0.0f, 0.55f, 1.0f },{ 0.0f, 0.58f, 1.0f },{ 0.0f, -0.58f, -1.0f },{ 0.0f, -0.55f, -1.0f } };
	//color
	const std::vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const std::vector<GLushort> indices = { 0, 1, 2, 0, 2, 3 };

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &Y_AxisMoonSlope.vao);
	glBindVertexArray(Y_AxisMoonSlope.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &Y_AxisMoonSlope.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Y_AxisMoonSlope.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &Y_AxisMoonSlope.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Y_AxisMoonSlope.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &Y_AxisMoonSlope.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Y_AxisMoonSlope.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	Y_AxisMoonSlope.model = glm::translate(Planetschief.model, glm::vec3(0.0f, 0.0f, 0.0f));
}

void initWireSphere() //Planet Sonne im Ursprung
{
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &Sonne.vao);

	// Modify model matrix.
	Sonne.model = glm::mat4(1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1, 0, 0));
}

void initWireSphereSchief() //gekippter Planet der Um die Sonne Rotiert
{
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &Planetschief.vao);
	
	
	
	// Modify model matrix.
	Planetschief.model = glm::mat4(1.0f) * glm::translate(Planetschief.model,glm::vec3 (-6.0,0.0,0.0));
}

void initWireSphereGrade()  // senkrechter Planet der um die Sonne Rotiert
{
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &PlanetGrade.vao);


	// Modify model matrix.sun.model;
	PlanetGrade.model = glm::mat4(1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1, 0, 0)) * glm::translate(PlanetGrade.model, glm::vec3(4.0, 0.0, 0.0));
}

void initWireSpheremoon1() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon1.vao);

	// Modify model matrix.
	moon1.model = glm::mat4(1.0f) * glm::translate(PlanetGrade.model, glm::vec3(-1.0,0.0,0.0)) ;
}

void initWireSpheremoon2() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon2.vao);

	// Modify model matrix.
	moon2.model = glm::mat4(1.0f) * glm::translate(PlanetGrade.model, glm::vec3(0.6, 0.6, 0.0));
}

void initWireSpheremoon3() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon3.vao);

	// Modify model matrix.
	moon3.model = glm::mat4(1.0f) * glm::translate(PlanetGrade.model, glm::vec3(0.6, -0.6, 0.0));
}

void initWireSpheremoon4() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon4.vao);

	// Modify model matrix.
	moon4.model = glm::mat4(1.0f)  * glm::translate(Planetschief.model, glm::vec3(1.0, 0.0, 0.0));
}

void initWireSpheremoon5() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon5.vao);

	// Modify model matrix.
	moon5.model = glm::mat4(1.0f) * glm::translate(Planetschief.model, glm::vec3(-1.0, 0.0, 0.0));
}

void initWireSpheremoon6() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon6.vao);

	// Modify model matrix.
	moon6.model = glm::mat4(1.0f) * glm::translate(Planetschief.model, glm::vec3(-1.0, 0.0, 1.0));
}

void initWireSpheremoon7() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon7.vao);

	// Modify model matrix.
	moon7.model = glm::mat4(1.0f) * glm::translate(Planetschief.model, glm::vec3(1.0, 0.0, 1.0));
}

void initWireSpheremoon8() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon8.vao);

	// Modify model matrix.
	moon8.model = glm::mat4(1.0f) * glm::translate(Planetschief.model, glm::vec3(0.0, -1.0, 1.0));
}

void initWireSpheremoon9() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon9.vao);

	// Modify model matrix.
	moon9.model = glm::mat4(1.0f) * glm::translate(Planetschief.model, glm::vec3(0.0, 1.0, 1.0));
}

void initWireSpheremoon10() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon10.vao);

	// Modify model matrix.
	moon10.model = glm::mat4(1.0f) * glm::translate(Planetschief.model, glm::vec3(-1.0, 0.0, -1.0));
}

void initWireSpheremoon11() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon11.vao);

	// Modify model matrix.
	moon11.model = glm::mat4(1.0f) * glm::translate(Planetschief.model, glm::vec3(1.0, 0.0, -1.0));
}

void initWireSpheremoon12() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon12.vao);

	// Modify model matrix.
	moon12.model = glm::mat4(1.0f) * glm::translate(Planetschief.model, glm::vec3(0.0, -1.0, -1.0));
}

void initWireSpheremoon13() {
	// set attribute locations (of shader) for GLUT
	GLuint programId = program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &moon13.vao);

	// Modify model matrix.
	moon13.model = glm::mat4(1.0f) * glm::translate(Planetschief.model, glm::vec3(0.0, 1.0, -1.0));
}

void rotate()
{
	//Rotation des Gesammten Systems
	//Planeten
	Planetschief.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * Planetschief.model;
	PlanetGrade.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * PlanetGrade.model;
	//Monde Planet Grade
	moon1.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon1.model;
	moon2.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon2.model;
	moon3.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon3.model;
	//Monde Planet schief:
	//unten
	moon4.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon4.model;
	moon5.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon5.model;
	moon6.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon6.model;
	moon7.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon7.model;
	//mitte
	moon8.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon8.model;
	moon9.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon9.model;
	//oben
	moon10.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon10.model;
	moon11.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon11.model;
	moon12.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon12.model;
	moon13.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon13.model;

	/// ZWEITE DREHUNG!!!
	PlanetGrade.model = glm::rotate(PlanetGrade.model, glm::radians(0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
	initWireSpheremoon1();
	initWireSpheremoon2();
	initWireSpheremoon3();

	
	//Rotation um den gekippten Planeten.
	Planetschief.model = glm::rotate(Planetschief.model, glm::radians(0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
	initWireSpheremoon4();
	initWireSpheremoon5();
	initWireSpheremoon6(); 
	initWireSpheremoon7();
	initWireSpheremoon8();
	initWireSpheremoon9();
	initWireSpheremoon10();
	initWireSpheremoon11();
	initWireSpheremoon12();
	initWireSpheremoon13();
	
	initY_AxisMoon();
	initY_AxisMoonSlope();

	glutPostRedisplay();
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Construct view matrix.
	glm::vec3 eye(0.0f, 0.0f, 10.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(eye, center, up);

	// Create a shader program and set light direction.
	if (!program.compileShaderFromFile("shader/simple.vert", cg::GLSLShader::VERTEX))
	{
		std::cerr << program.log();
		return false;
	}

	if (!program.compileShaderFromFile("shader/simple.frag", cg::GLSLShader::FRAGMENT))
	{
		std::cerr << program.log();
		return false;
	}
	
	if (!program.link())
	{
		std::cerr << program.log();
		return false;
	}

	// Create all objects.
	// GLUT: create vertex-array-object for glut geometry, the "default"
	// must be bound before the glutWireSphere call

	initWireSphere();
	initWireSphereSchief();
	Planetschief.model = Planetschief.model * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1, 0, 0)); // kippen um 45� von Planetschief
	initWireSphereGrade();
	initWireSpheremoon1();
	initWireSpheremoon2();
	initWireSpheremoon3();
	initWireSpheremoon4();
	initWireSpheremoon5();
	initWireSpheremoon6();
	initWireSpheremoon7();
	initWireSpheremoon8();
	initWireSpheremoon9();
	initWireSpheremoon10();
	initWireSpheremoon11();
	initWireSpheremoon12();
	initWireSpheremoon13();

	

	initY_AxisSun();
	initY_AxisMoon();
	initY_AxisMoonSlope();
	return true;
}

/*
 Release object resources.
*/
void releaseObject(Object& obj)
{
	glDeleteVertexArrays(1, &obj.vao);
	glDeleteBuffers(1, &obj.indexBuffer);
	glDeleteBuffers(1, &obj.colorBuffer);
	glDeleteBuffers(1, &obj.positionBuffer);
}

/*
 Release resources on termination.
 */
void release()
{
	// Shader program will be released upon program termination.

	releaseObject(Y_AxisSun);
	releaseObject(Y_AxisMoon);
	releaseObject(Y_AxisMoonSlope);

	releaseObject(Sonne);
	releaseObject(Planetschief);
	releaseObject(PlanetGrade);
	releaseObject(moon1);
	releaseObject(moon2);
	releaseObject(moon3);
	releaseObject(moon4);
	releaseObject(moon5);
	releaseObject(moon6);
	releaseObject(moon7);
	releaseObject(moon8);
	releaseObject(moon9);
	releaseObject(moon10);
	releaseObject(moon11);
	releaseObject(moon12);
	releaseObject(moon13);
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderY_AxisSun();
	renderY_AxisMoon();
	renderY_AxisMoonSlope();

	renderWireSphereSonne();
	renderWireSpherePlanetschief();
	renderWireSpherePlanetgrade();
	renderWireSpheremoon1();
	renderWireSpheremoon2();
	renderWireSpheremoon3();
	renderWireSpheremoon4();
	renderWireSpheremoon5();
	renderWireSpheremoon6();
	renderWireSpheremoon7();
	renderWireSpheremoon8();
	renderWireSpheremoon9();
	renderWireSpheremoon10();
	renderWireSpheremoon11();
	renderWireSpheremoon12();
	renderWireSpheremoon13();


}

/*
 Resize callback.
 */
void glutResize (int width, int height)
{
	// Division by zero is bad...
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}
		
/*
Callback for char input.
*/
void glutKeyboard(unsigned char keycode, int x, int y)
{

	switch (keycode)
	{
	case 27: // ESC
		glutDestroyWindow(glutID);
		return;

	case 'w':	//Rotation des Gesammten Systems
		if (iVelocity > 0.1)
			iVelocity -= 0.1;
		break;

	case 'W':	//Rotation des Gesammten Systems beschleunigen
		if(iVelocity < 1.0)
			iVelocity += 0.1;
		break;

	case 't': //Bewegung des Gesammten Planetensystems entlang der Y-Achse nach unten
				//Planeten
		Sonne.model = glm::translate(Sonne.model, glm::vec3(0.0, 0.0, 1.0));
		Y_AxisSun.model = glm::translate(Y_AxisSun.model, glm::vec3(0.0, -1.0, 0.0));
		PlanetGrade.model = glm::translate(PlanetGrade.model, glm::vec3(0.0, 0.0, 1.0));
		Planetschief.model = glm::translate(Planetschief.model, glm::vec3(0.0, -0.7, 0.7));
		//Monde Planet Grade
		Y_AxisMoonSlope.model = glm::translate(Y_AxisMoonSlope.model, glm::vec3(0.0, -0.7, 0.7));
		Y_AxisMoon.model = glm::translate(Y_AxisMoon.model, glm::vec3(0.0, 1.0, 0.0));
		moon1.model = glm::translate(moon1.model, glm::vec3(0.0, 1.0, 0.0));
		moon2.model = glm::translate(moon2.model, glm::vec3(0.0, 1.0, 0.0));
		moon3.model = glm::translate(moon3.model, glm::vec3(0.0, 1.0, 0.0));
		//Monde Planet schief:
		//unten
		moon4.model = glm::translate(moon4.model, glm::vec3(0.0, -0.7, 0.7));
		moon5.model = glm::translate(moon5.model, glm::vec3(0.0, -0.7, 0.7));
		moon6.model = glm::translate(moon6.model, glm::vec3(0.0, -0.7, 0.7));
		moon7.model = glm::translate(moon7.model, glm::vec3(0.0, -0.7, 0.7));
		//mitte
		moon8.model = glm::translate(moon8.model, glm::vec3(0.0, -0.7, 0.7));
		moon9.model = glm::translate(moon9.model, glm::vec3(0.0, -0.7, 0.7));
		//oben
		moon10.model = glm::translate(moon10.model, glm::vec3(0.0, -0.7, 0.7));
		moon11.model = glm::translate(moon11.model, glm::vec3(0.0, -0.7, 0.7));
		moon12.model = glm::translate(moon12.model, glm::vec3(0.0, -0.7, 0.7));
		moon13.model = glm::translate(moon13.model, glm::vec3(0.0, -0.7, 0.7));
		break;
	case 'T': //Bewegung des Gesammten Planetensystems entlang der Y-Achse nach oben
				//Planeten
		Sonne.model = glm::translate(Sonne.model, glm::vec3(0.0, 0.0, -1.0));
		Y_AxisSun.model = glm::translate(Y_AxisSun.model, glm::vec3(0.0, 1.0, 0.0));
		PlanetGrade.model = glm::translate(PlanetGrade.model, glm::vec3(0.0, 0.0, -1.0));
		Planetschief.model = glm::translate(Planetschief.model, glm::vec3(0.0, 0.7, -0.7));
		//Monde Planet Grade
		Y_AxisMoonSlope.model = glm::translate(Y_AxisMoonSlope.model, glm::vec3(0.0, 0.7, -0.7));
		Y_AxisMoon.model = glm::translate(Y_AxisMoon.model, glm::vec3(0.0, 0.0, -1.0));

		moon1.model = glm::translate(moon1.model, glm::vec3(0.0, -1.0, 0.0));
		moon2.model = glm::translate(moon2.model, glm::vec3(0.0, -1.0, 0.0));
		moon3.model = glm::translate(moon3.model, glm::vec3(0.0, -1.0, 0.0));
		//Monde Planet schief:
		//unten
		moon4.model = glm::translate(moon4.model, glm::vec3(0.0, 0.7, -0.7));
		moon5.model = glm::translate(moon5.model, glm::vec3(0.0, 0.7, -0.7));
		moon6.model = glm::translate(moon6.model, glm::vec3(0.0, 0.7, -0.7));
		moon7.model = glm::translate(moon7.model, glm::vec3(0.0, 0.7, -0.7));
		//mitte
		moon8.model = glm::translate(moon8.model, glm::vec3(0.0, 0.7, -0.7));
		moon9.model = glm::translate(moon9.model, glm::vec3(0.0, 0.7, -0.7));
		//oben
		moon10.model = glm::translate(moon10.model, glm::vec3(0.0, 0.7, -0.7));
		moon11.model = glm::translate(moon11.model, glm::vec3(0.0, 0.7, -0.7));
		moon12.model = glm::translate(moon12.model, glm::vec3(0.0, 0.7, -0.7));
		moon13.model = glm::translate(moon13.model, glm::vec3(0.0, 0.7, -0.7));
		break;
	case 'l': //Grader Planet nach unten bewegen
		PlanetGrade.model = glm::translate(PlanetGrade.model, glm::vec3(0.0, 0.0, 1.0));
		Y_AxisMoon.model = glm::translate(Y_AxisMoon.model, glm::vec3(0.0, 0.0, 1.0));
		moon1.model = glm::translate(moon1.model, glm::vec3(0.0, 1.0, 0.0));
		moon2.model = glm::translate(moon2.model, glm::vec3(0.0, 1.0, 0.0));
		moon3.model = glm::translate(moon3.model, glm::vec3(0.0, 1.0, 0.0));
		break;
	case 'L': //Grader Planet nach oben bewegen
		PlanetGrade.model = glm::translate(PlanetGrade.model, glm::vec3(0.0, 0.0, -1.0));
		Y_AxisMoon.model = glm::translate(Y_AxisMoon.model, glm::vec3(0.0, 0.0, -1.0));
		moon1.model = glm::translate(moon1.model, glm::vec3(0.0, -1.0, 0.0));
		moon2.model = glm::translate(moon2.model, glm::vec3(0.0, -1.0, 0.0));
		moon3.model = glm::translate(moon3.model, glm::vec3(0.0, -1.0, 0.0));
		break;


	case 'p':  //Rotation des Schiefen Planeten 
		Planetschief.model = Planetschief.model*glm::rotate(glm::mat4(1.0f), glm::radians(-5.0f), glm::vec3(1, 0, 0));	
		break;
		//bug: nach drehung geht der Planet bei T oder t immer in 45� gekippte X achse des Planeten 
	 case 'P': //Rotation des Schiefen Planeten 
	 	Planetschief.model = Planetschief.model*glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(1, 0, 0));	
	 	break;

	case '+': //Zoom in to Sun
		if (zoomstufe > 0) {
			view = glm::translate(view, glm::vec3(0.0, 0.0, 0.5));
			zoomstufe--;
		}		
		break;
	case '-': //Zoom out of Sun
		if (zoomstufe < 10) {
			view = glm::translate(view, glm::vec3(0.0, 0.0, -0.5));
			zoomstufe++;
		}
		break;
	}
	glutPostRedisplay();
}


void glutDisplay()
{
	GLCODE(render());
	glutSwapBuffers();
	rotate();
}

int main(int argc, char** argv)
{
	// GLUT: Initialize freeglut library (window toolkit).
    glutInitWindowSize    (WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(40,40);
	glutInit(&argc, argv);

	// GLUT: Create a window and opengl context (version 4.3 core profile).
	glutInitContextVersion(4, 3);
	glutInitContextFlags  (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutInitDisplayMode   (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("Aufgabenblatt 04");
	glutID = glutGetWindow();
	  
	// GLEW: Load opengl extensions
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();

	if (result != GLEW_OK) {
	   return -1;
	}

	// GLUT: Set callbacks for events.
	glutReshapeFunc(glutResize);
	glutDisplayFunc(glutDisplay);
	glutIdleFunc(glutDisplay); // redisplay when idle

	glutKeyboardFunc(glutKeyboard);

	// init vertex-array-objects.
	{
		GLCODE(bool result = init());
		if (!result) {
			release();
			return -2;
		}
	}

	// GLUT: Loop until the user closes the window
	// rendering & event handling
	glutMainLoop ();

	// Cleanup everything on termination.
	release();

	return 0;
}
