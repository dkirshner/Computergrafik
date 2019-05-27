#include "Init.h"

#include <vector>

void init_Y_Axis_Sun(GLuint a_programId, Object* a_pY_AxisSun)
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { 0.0f, 1.5f, 0.0f },{ 0.0f, -1.5f, 0.0f } };	// Parallel zu Achse Y

	//color
	const std::vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0, 0.0f } }; // rot
	const std::vector<GLushort> indices = { 0, 1 };

	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &a_pY_AxisSun->vao);
	glBindVertexArray(a_pY_AxisSun->vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &a_pY_AxisSun->positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, a_pY_AxisSun->positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(a_programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &a_pY_AxisSun->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, a_pY_AxisSun->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(a_programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &a_pY_AxisSun->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a_pY_AxisSun->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	a_pY_AxisSun->model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.07f, 0.0f, 0.0f));
}


void init_Y_Axis_Planet(GLuint a_programId, Object* a_Y_AxisMoon, Object a_PlanetGrade)
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, -1.0f } }; // Parallel zu Achse Z
	//color
	const std::vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0, 0.0f } }; // rot
	const std::vector<GLushort> indices = { 0, 1 };


	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &a_Y_AxisMoon->vao);
	glBindVertexArray(a_Y_AxisMoon->vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &a_Y_AxisMoon->positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, a_Y_AxisMoon->positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(a_programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &a_Y_AxisMoon->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, a_Y_AxisMoon->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(a_programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &a_Y_AxisMoon->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a_Y_AxisMoon->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	a_Y_AxisMoon->model = glm::translate(a_PlanetGrade.model, glm::vec3(0.0f, 0.0f, 0.0f));
}

void initY_AxisMoonSlope(GLuint a_programId, Object* a_Y_AxisMoonSlope, Object a_Planetschief)
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, -1.0f } };
	//color
	const std::vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0, 0.0f } }; // rot
	const std::vector<GLushort> indices = { 0, 1};

	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &a_Y_AxisMoonSlope->vao);
	glBindVertexArray(a_Y_AxisMoonSlope->vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &a_Y_AxisMoonSlope->positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, a_Y_AxisMoonSlope->positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(a_programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &a_Y_AxisMoonSlope->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, a_Y_AxisMoonSlope->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(a_programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &a_Y_AxisMoonSlope->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a_Y_AxisMoonSlope->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// Modify model matrix.
	a_Y_AxisMoonSlope->model = glm::translate(a_Planetschief.model, glm::vec3(0.0f, 0.0f, 0.0f));
}


void initWireSphere(GLuint a_programId, Object* a_Sonne) //Planet Sonne im Ursprung
{
	// set attribute locations (of shader) for GLUT
	/////////////////////////////////////////////////////////////////////GLuint programId = a_program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(a_programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(a_programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &a_Sonne->vao);

	// Modify model matrix.
	a_Sonne->model = glm::mat4(1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1, 0, 0));
}


void initWireSphereSchief(GLuint a_programId, Object* a_Planetschief) //gekippter Planet der Um die Sonne Rotiert
{
	// set attribute locations (of shader) for GLUT
	//GLuint programId = a_program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(a_programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(a_programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &a_Planetschief->vao);

	// Modify model matrix.
	a_Planetschief->model = glm::mat4(1.0f) * glm::translate(a_Planetschief->model, glm::vec3(-6.0, 0.0, 0.0));
}


void initWireSphereGrade(GLuint a_programId, Object* a_PlanetGrade)  // senkrechter Planet der um die Sonne Rotiert
{
	// set attribute locations (of shader) for GLUT
	//GLuint programId = a_program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(a_programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(a_programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &a_PlanetGrade->vao);


	// Modify model matrix.sun.model;
	a_PlanetGrade->model = glm::mat4(1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1, 0, 0)) * glm::translate(a_PlanetGrade->model, glm::vec3(4.0, 0.0, 0.0));
}


void initWireSpheremoon1(GLuint a_programId, Object* a_moon1, Object a_PlanetGrade)
{
	// set attribute locations (of shader) for GLUT
	//GLuint programId = a_program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(a_programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(a_programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &a_moon1->vao);

	// Modify model matrix.
	a_moon1->model = glm::mat4(1.0f) * glm::translate(a_PlanetGrade.model, glm::vec3(-1.0, 0.0, 0.0));
}


void initWireSpheremoon2(GLuint a_programId, Object* a_moon2, Object a_PlanetGrade)
{
	// set attribute locations (of shader) for GLUT
	//GLuint programId = a_program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(a_programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(a_programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &a_moon2->vao);

	// Modify model matrix.
	a_moon2->model = glm::mat4(1.0f) * glm::translate(a_PlanetGrade.model, glm::vec3(0.0, 1.0, 0.0));
}


void initWireSpheremoon3(GLuint a_programId, Object* a_moon3, Object a_PlanetGrade)
{
	// set attribute locations (of shader) for GLUT
	//GLuint programId = a_program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(a_programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(a_programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &a_moon3->vao);

	// Modify model matrix.
	a_moon3->model = glm::mat4(1.0f) * glm::translate(a_PlanetGrade.model, glm::vec3(1.0, 0.0, 0.0));
}

void initWireSpheremoon4(GLuint a_programId, Object* a_moon4, Object a_PlanetGrade)
{
	// set attribute locations (of shader) for GLUT
	//GLuint programId = a_program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(a_programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(a_programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &a_moon4->vao);

	// Modify model matrix.
	a_moon4->model = glm::mat4(1.0f)  * glm::translate(a_PlanetGrade.model, glm::vec3(0.0, -1.0, 0.0));
}

void initWireSpheremoon5(GLuint a_programId, Object* a_moon5, Object a_Planetschief)
{
	// set attribute locations (of shader) for GLUT
	//GLuint programId = a_program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(a_programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(a_programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &a_moon5->vao);

	// Modify model matrix.
	a_moon5->model = glm::mat4(1.0f) * glm::translate(a_Planetschief.model, glm::vec3(-1.0, 0.0, -1.0));
}
 

void initWireSpheremoon6(GLuint a_programId, Object* a_moon6, Object a_Planetschief)
{
	// set attribute locations (of shader) for GLUT
	//GLuint programId = a_program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(a_programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(a_programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &a_moon6->vao);

	// Modify model matrix.
	a_moon6->model = glm::mat4(1.0f) * glm::translate(a_Planetschief.model, glm::vec3(1.0, 0.0, -1.0));
}


void initWireSpheremoon7(GLuint a_programId, Object* a_moon7, Object a_Planetschief)
{
	// set attribute locations (of shader) for GLUT
	//GLuint programId = a_program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(a_programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(a_programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &a_moon7->vao);

	// Modify model matrix.
	a_moon7->model = glm::mat4(1.0f) * glm::translate(a_Planetschief.model, glm::vec3(0.0, 1.0, 1.0));
}

void initWireSpheremoon8(GLuint a_programId, Object* a_moon8, Object a_Planetschief)
{
	// set attribute locations (of shader) for GLUT
	//GLuint programId = a_program.getHandle();
	// position attribute to variable "position"
	glutSetVertexAttribCoord3(glGetAttribLocation(a_programId, "position"));
	// normal attribute to variable "color"
	// this creates a colorful sphere :-)
	glutSetVertexAttribNormal(glGetAttribLocation(a_programId, "color"));
	// create a vertex-array-object for GLUT geometry
	glGenVertexArrays(1, &a_moon8->vao);

	// Modify model matrix.
	a_moon8->model = glm::mat4(1.0f) * glm::translate(a_Planetschief.model, glm::vec3(1.0, 1.0, -1.0));
}
