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

double iKlick_X = 0.0f, iKlick_Y = 0.0f, iKlick_Z = 0.0f;
double dRadius = 0.5;			// init
unsigned short iSubdivision = 0, iPrevSubdivision = 0;	// init 
double X_VIEW=-3.0f, Y_VIEW=-3.0f, Z_VIEW=-3.0f; //view Matrix
// Standard window width
const int WINDOW_WIDTH  = 940;
// Standard window height
const int WINDOW_HEIGHT = 680;
// GLUT window id/handle
int glutID = 0;

cg::GLSLProgram program;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar  = 100.0f;

vector<GLushort> indicesCircle_0, indicesCircle_1, indicesCircle_2, indicesCircle_3;
vector<glm::vec3> colorsCircle_0, colorsCircle_1, colorsCircle_2, colorsCircle_3;
vector<glm::vec3> verticesCircle_0, verticesCircle_1, verticesCircle_2, verticesCircle_3;

// Construct triangles. These vectors can go out of scope after we have send all data to the graphics card.
// Every side has two triangles á 3 vertices

vector<glm::vec3> verticesCircle = {
	{ 0.5f, 0.0f, -0.5f }, //front
	{ 0.5f, 0.0f,  0.5f },
	{ 0.0f, 0.87f, 0.0f },

	{ -0.5f, 0.0f, 0.5f },
	{ -0.5f, 0.0f, -0.5f },
	{ 0.0f, -0.87f, 0.0f }
};

vector<glm::vec3> colorsCircle = {	// Einheitliche Farbe gelb!
	{ 1.0f, 1.0f, 0.0f }, // front
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f },

	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f }, // end front

	{ 1.0f, 1.0f, 0.0f },//bottom
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

// The indices of the sides, beginning at the front
vector<GLushort>indicesCircle = {
	0, 1, 2, // bottom
	2, 1, 3,
	2, 3, 4,
	2, 4, 0,
	5, 4, 0, // left
	5, 1, 0,
	5, 1, 3, // right
	5, 3, 4
};

/*
Struct to hold data for object rendering.
*/
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

Object Circle;
std::vector<Object> CirclePieses;	// Vektor wo alle Kugelteile gespeichert werden aus denen der Kugel entsteht
// Axis (zur Darstellung der Koordinatenachsen)
GraphicObject XAxis, YAxis, ZAxis;

void renderCircle(Object a_cirle)
{
	// Cumulating transformations -> Create mvp: the ModelViewProjection matrix!
	glm::mat4x4 mvp = projection * view * a_cirle.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 1 triangle.
    glBindVertexArray(a_cirle.vao);	 //Vertex Array Object

	int iSizeOfTriangles = (int)indicesCircle.size(); // init

	if (iSizeOfTriangles < 24)
	{
		cout << "FEHLER renderCircle(): Anzahl Dreiecke ist unter 24!" << iSizeOfTriangles;
		iSizeOfTriangles = 24;
	}
	else if (iSizeOfTriangles > 200)
	{
		cout << "FEHLER renderCircle(): Anzahl Dreiecke ist höher 200!" << iSizeOfTriangles;
		iSizeOfTriangles = 24;
	}
		
	glDrawElements(GL_TRIANGLES, iSizeOfTriangles, GL_UNSIGNED_SHORT, 0); // glDrawElements (GLenum mode, GLsizei count, GLenum type, const void *indices); KI
	glBindVertexArray(0);
}

void initCircle()
{
	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &Circle.vao);
	glBindVertexArray(Circle.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &Circle.positionBuffer);				// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glBindBuffer(GL_ARRAY_BUFFER, Circle.positionBuffer);	// The following commands will talk about our 'vertexbuffer' buffer
																// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, verticesCircle.size() * sizeof(glm::vec3), verticesCircle.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	/*Vertex-Attribute können durch die glVertexAttribPointer-Funktion und ihre beiden Schwesterfunktionen glVertexAttribIPointer und glVertexAttribLPointer beschrieben werden.*/
	glVertexAttribPointer(pos,			// attribute 0. No particular reason for 0, but must match the layout in the shader.
						  3,			// size
						  GL_FLOAT,		// type
						  GL_FALSE,		// normalized?
						  0,			// stride (Forschritt)
						  0);			// array buffer offset

					// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &Circle.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Circle.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colorsCircle.size() * sizeof(glm::vec3), colorsCircle.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &Circle.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Circle.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCircle.size() * sizeof(GLushort), indicesCircle.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
	// INIT: Transformation des Kreise
	Circle.model = glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));
}

//Stellt ein Koordinatensystem dar

void renderXAxis()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * XAxis.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	XAxis.renderObject(6);
}

void renderYAxis()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * YAxis.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	YAxis.renderObject(6);
}

void renderZAxis()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * ZAxis.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	ZAxis.renderObject(6);
}

void initXAxis()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const vector<glm::vec3> vertices = { { -3.0f, 0.0f, 0.0f }, { 3.0f, 0.0f, 0.0f } };
	// color
	const vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const vector<GLushort> indices = {1,0};

	GLuint programId = program.getHandle();
	XAxis.initObject(vertices, colors, indices, programId);
}

void initYAxis()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const vector<glm::vec3> vertices = { { 0.0f, 3.0f, 0.0f },{ 0.0f, -3.0f, 0.0f } };
	//color
	const vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const vector<GLushort> indices = { 1,0};

	GLuint programId = program.getHandle();

	YAxis.initObject(vertices, colors, indices, programId);
}

void initZAxis()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const vector<glm::vec3> vertices = { { 0.0f, 0.0f, 3.0f }, { 0.0f, 0.0f, -3.0f } };
	// Farbe
	const vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } }; // rot
	const vector<GLushort> indices = {1,0};

	GLuint programId = program.getHandle();

	ZAxis.initObject(vertices, colors, indices, programId);
}

void initView() {
	// Construct view matrix.
	glm::vec3 eye(X_VIEW, Y_VIEW, Z_VIEW);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(eye, center, up);
}

/*
Initialization. Should return true if everything is ok and false if something went wrong.
*/
bool init()
{
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	initView();

	// Create a shader program and set light direction.
	if (!program.compileShaderFromFile("shader/simple.vert", cg::GLSLShader::VERTEX))
	{
		cerr << program.log();
		return false;
	}

	if (!program.compileShaderFromFile("shader/simple.frag", cg::GLSLShader::FRAGMENT))
	{
		cerr << program.log();
		return false;
	}

	if (!program.link())
	{
		cerr << program.log();
		return false;
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Create objects:
	initCircle();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// show axis:
	initXAxis();
	initYAxis();
	initZAxis();

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
	releaseObject(Circle);
	XAxis.deleteObject();
	YAxis.deleteObject();
	ZAxis.deleteObject();
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(iSubdivision >= 2)
	{
		for (unsigned int i = 0; i < CirclePieses.size(); i++)
			renderCircle(CirclePieses.at(i));
	}
	else
		renderCircle(Circle);

	renderXAxis();
	renderYAxis();
	renderZAxis();
}

void glutDisplay ()
{
   GLCODE(render());
   glutSwapBuffers();
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


bool IsVertexSaved(glm::vec3 a_Pnt, int *a_Index)
{
	for (int i = 0; i < verticesCircle.size(); i++)
	{
		double dVert_X = ceilf(verticesCircle.at(i).x * 1000) / 1000;
		double dVert_Y = ceilf(verticesCircle.at(i).y * 1000) / 1000;
		double dVert_Z = ceilf(verticesCircle.at(i).z * 1000) / 1000;

		double dPnt_X = ceilf(a_Pnt.x * 1000) / 1000;
		double dPnt_Y = ceilf(a_Pnt.y * 1000) / 1000;
		double dPnt_Z = ceilf(a_Pnt.z * 1000) / 1000;

		if (dVert_X  == dPnt_X &&
			dVert_Y == dPnt_Y &&
			dVert_Z == dPnt_Z	)
		{
			*a_Index = i;
			return true;
		}
	}

	return false;
}


///////////////////////////////////////////////////////////////////////////////
// find middle point of 2 vertices
// NOTE: new vertex must be resized, so the length is equal to the radius
///////////////////////////////////////////////////////////////////////////////
void computeHalfVertex( glm::vec3 v1,  glm::vec3 v2, glm::vec3 *newV)
{
	newV->x = v1[0] + v2[0];    // x
	newV->y = v1[1] + v2[1];    // y
	newV->z = v1[2] + v2[2];    // z
	double dResult = sqrt(newV->x * newV->x + newV->y * newV->y + newV->z * newV->z);
	const double scale = dRadius / dResult;
	newV->x = newV->x * (float)scale;
	newV->y = newV->y * (float)scale;
	newV->z = newV->z * (float)scale;
}
 
// Der Unterteilungsalgorithmus teilt die drei Kantenlinien jedes Dreiecks in zwei Hälften und 
// extrudiert dann den neuen Mittelpunkt nach außen, sodass seine Länge(der Abstand vom Mittelpunkt)
// dem Radius der Kugel entspricht.
int SubDivisionAlgorithm()
{
	if (iSubdivision > 4)
		return true;

	if (verticesCircle.size() && indicesCircle.size() && colorsCircle.size())
	{
		if (iPrevSubdivision < iSubdivision)
		{
			if (iSubdivision == 1)
			{
				for (int i = 0; i < verticesCircle.size(); i++)
					verticesCircle_0.push_back(verticesCircle[i]);

				for (int i = 0; i < indicesCircle.size(); i++)
					indicesCircle_0.push_back(indicesCircle[i]);

				for (int i = 0; i < colorsCircle.size(); i++)
					colorsCircle_0.push_back(colorsCircle[i]);
			}
			else if (iSubdivision == 2)
			{
				for (int i = 0; i < verticesCircle.size(); i++)
					verticesCircle_1.push_back(verticesCircle[i]);

				for (int i = 0; i < indicesCircle.size(); i++)
					indicesCircle_1.push_back(indicesCircle[i]);

				for (int i = 0; i < colorsCircle.size(); i++)
					colorsCircle_1.push_back(colorsCircle[i]);
			}
			else if (iSubdivision == 3)
			{
				for (int i = 0; i < verticesCircle.size(); i++)
					verticesCircle_2.push_back(verticesCircle[i]);

				for (int i = 0; i < indicesCircle.size(); i++)
					indicesCircle_2.push_back(indicesCircle[i]);

				for (int i = 0; i < colorsCircle.size(); i++)
					colorsCircle_2.push_back(colorsCircle[i]);
			}
		}
		else 
		{
			if (verticesCircle.size())
				verticesCircle.clear();

			if (indicesCircle.size())
				indicesCircle.clear();

			if (colorsCircle.size())
				colorsCircle.clear();

			if (CirclePieses.size())
				CirclePieses.clear();

			if (iSubdivision == 1)
			{
				for (int i = 0; i < verticesCircle_0.size(); i++)
					verticesCircle.push_back(verticesCircle[i]);

				for (int i = 0; i < indicesCircle_0.size(); i++)
					indicesCircle.push_back(indicesCircle[i]);

				for (int i = 0; i < colorsCircle_0.size(); i++)
					colorsCircle.push_back(colorsCircle[i]);
			}
			else if (iSubdivision == 2)
			{
				for (int i = 0; i < verticesCircle_1.size(); i++)
					verticesCircle.push_back(verticesCircle[i]);

				for (int i = 0; i < indicesCircle_1.size(); i++)
					indicesCircle.push_back(indicesCircle[i]);

				for (int i = 0; i < colorsCircle_1.size(); i++)
					colorsCircle.push_back(colorsCircle[i]);
			}
			else if (iSubdivision == 3)
			{
				for (int i = 0; i < verticesCircle_2.size(); i++)
					verticesCircle.push_back(verticesCircle[i]);

				for (int i = 0; i < indicesCircle_2.size(); i++)
					indicesCircle.push_back(indicesCircle[i]);

				for (int i = 0; i < colorsCircle_2.size(); i++)
					colorsCircle.push_back(colorsCircle[i]);
			}
			else if (iSubdivision == 4)
			{
				for (int i = 0; i < verticesCircle_3.size(); i++)
					verticesCircle.push_back(verticesCircle[i]);

				for (int i = 0; i < indicesCircle_3.size(); i++)
					indicesCircle.push_back(indicesCircle[i]);

				for (int i = 0; i < colorsCircle_3.size(); i++)
					colorsCircle.push_back(colorsCircle[i]);
			}
		}
	}

	vector<glm::vec3>tmpColors;
	vector<glm::vec3>tmpVertices;
	vector<GLushort> tmpIndices;  

	glm::vec3 newV1, newV2, newV3; // new vertex positions
	unsigned int index;

	// copy prev vertex/index arrays and clear

	for (int i = 0; i < verticesCircle.size(); i++)
		tmpVertices.push_back(verticesCircle[i]);

	for (int i = 0; i < indicesCircle.size(); i++)
		tmpIndices.push_back(indicesCircle[i]);

	for (int i = 0; i < colorsCircle.size(); i++)
		tmpColors.push_back(colorsCircle[i]);

	if(verticesCircle.size())
		verticesCircle.clear();

	if (indicesCircle.size())
		indicesCircle.clear();

	if (colorsCircle.size())
		colorsCircle.clear();

	if (CirclePieses.size())
		CirclePieses.clear();

	index = 0;
	bool bNoBreak = true;

	// perform subdivision for each triangle
	for (int j = 0; j < tmpIndices.size() && bNoBreak; j += 3)
	{
		// get 3 vertices of a triangle
		glm::vec3 v1 = tmpVertices[tmpIndices[j]];
		glm::vec3 v2 = tmpVertices[tmpIndices[j + 1]];
		glm::vec3 v3 = tmpVertices[tmpIndices[j + 2]];

		// compute 3 new vertices by spliting half on each edge
		//         v1       
		//        / \       
		// newV1 *---* newV3
		//      / \ / \     
		//    v2---*---v3   
		//       newV2  

		glm::vec3 newV1, newV2, newV3;

		computeHalfVertex(v1, v2, &newV1);
		computeHalfVertex(v2, v3, &newV2);
		computeHalfVertex(v1, v3, &newV3);

		int iIndex_0 = index;
		int iIndex_1 = index + 1;
		int iIndex_2 = index + 2;
		int iIndex_3 = index + 3;
		int iIndex_4 = index + 4;
		int iIndex_5 = index + 5;

		// add 4 new triangles to vertex array
		if (IsVertexSaved(v1, &iIndex_0) == false)
		{
			verticesCircle.push_back(v1);		// #0
			iIndex_0 = (int)verticesCircle.size() - 1;
		}

		if (IsVertexSaved(v2, &iIndex_1) == false)
		{
			verticesCircle.push_back(v2);		// #1
			iIndex_1 = (int)verticesCircle.size() - 1;
		}

		if (IsVertexSaved(v3, &iIndex_2) == false)
		{
			verticesCircle.push_back(v3);		// #2
			iIndex_2 = (int)verticesCircle.size() - 1;
		}

		if (IsVertexSaved(newV1, &iIndex_3) == false)
		{
			verticesCircle.push_back(newV1);	// #3
			iIndex_3 = (int)verticesCircle.size() - 1;
		}

		if (IsVertexSaved(newV2, &iIndex_4) == false)
		{
			verticesCircle.push_back(newV2);	// #4
			iIndex_4 = (int)verticesCircle.size() - 1;
		}

		if (IsVertexSaved(newV3, &iIndex_5) == false)
		{
			verticesCircle.push_back(newV3);	// #6
			iIndex_5 = (int)verticesCircle.size() - 1;
		}

		for (int i = 0; i < verticesCircle.size(); i++)
		{
			verticesCircle[i] *= 1.0f / sqrt(verticesCircle[i].x * verticesCircle[i].x + verticesCircle[i].y * verticesCircle[i].y + verticesCircle[i].z * verticesCircle[i].z);
		}

		////////////////  indices   ////////////////

		indicesCircle.push_back(GLushort(iIndex_0));
		indicesCircle.push_back(GLushort(iIndex_3));
		indicesCircle.push_back(GLushort(iIndex_5));	// addIndices(index, index + 1, index + 2);

		indicesCircle.push_back(GLushort(iIndex_3));
		indicesCircle.push_back(GLushort(iIndex_1));
		indicesCircle.push_back(GLushort(iIndex_4));

		indicesCircle.push_back(GLushort(iIndex_3));
		indicesCircle.push_back(GLushort(iIndex_4));
		indicesCircle.push_back(GLushort(iIndex_5));

		indicesCircle.push_back(GLushort(iIndex_5));
		indicesCircle.push_back(GLushort(iIndex_4));
		indicesCircle.push_back(GLushort(iIndex_2));



		//////////////   colors   //////////////////////////

		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsCircle.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

		index += 6;

		if (index == 96)
		{
			initCircle();
			CirclePieses.push_back(Circle);
		}

		if (iSubdivision >= 2)
			if (index >= 91)
				bNoBreak = false;
	}

	if (iSubdivision == 2)
	{
		initCircle();
		//Bogenmass in Radian: Umrechnung von Grad in Bogenmaß
		// degree = radian * 180/π
		// radian = degree * π/180

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Circle.model = glm::rotate(glm::mat4(1.0f), ((float)M_PI), glm::vec3(0.0f, 0.0f, 1.0f)) * 
				        glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		CirclePieses.push_back(Circle);
	}
	else if (iSubdivision == 3)
	{
		// Körper oben #2
		initCircle();
		//Bogenmass in Radian: Umrechnung von Grad in Bogenmaß
		// degree =v radian * 180/π
		// radian = degree * π/180
		float dAngle = (float)(M_PI) / (-2.0);

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Circle.model =	glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		CirclePieses.push_back(Circle);

		// Körper oben #3
		initCircle();

		dAngle = (float)(M_PI) / 2.0;

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Circle.model =	glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
				        glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		CirclePieses.push_back(Circle);

		// Körper oben #4
		initCircle();
		dAngle = (float)(M_PI);

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Circle.model =	glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		CirclePieses.push_back(Circle);

		// Körper unten #1
		initCircle();
		dAngle = (float)(M_PI);

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Circle.model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 0.0f, 1.0f)) *
					   glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		CirclePieses.push_back(Circle);

		// Körper unten #2
		initCircle();
		dAngle = (float)(M_PI) /2.0;
		float dAngle_2 = (float)(M_PI);

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Circle.model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
					   glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(1.0f, 0.0f, 0.0f)) *
					   glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		CirclePieses.push_back(Circle);

		// Körper unten #3
		initCircle();
		dAngle = (float)(M_PI) / 2.0;
		dAngle_2 = (float)(M_PI);

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Circle.model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
			           glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(1.0f, 0.0f, 0.0f)) *
					   glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(0.0f, 1.0f, 0.0f)) *
			           glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		CirclePieses.push_back(Circle);

		// Körper unten #3
		initCircle();
		dAngle = (float)(M_PI) / 2.0;
		dAngle_2 = (float)(M_PI)*(-1.0);
		float dAngle_3 = (float)(M_PI) / 2.0;

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Circle.model =	glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(1.0f, 0.0f, 0.0f)) *
						glm::rotate(glm::mat4(1.0f), dAngle_3, glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		CirclePieses.push_back(Circle);
	}
 
	if (iSubdivision != 3)
		initCircle();

	if (tmpVertices.size())
		tmpVertices.clear();

	if (tmpIndices.size())
		tmpIndices.clear();

	if (tmpColors.size())
		tmpColors.clear();

	return 0;
}

////////////////////////////////////////////////////////////////7

/*
 Callback for char input.
 */
void glutKeyboard (unsigned char keycode, int x, int y)
{
	switch (keycode)
	{
	case 27: // ESC
	  glutDestroyWindow ( glutID );
	  return;

	case 'r':
		if (dRadius > 0.3) 
		{
			dRadius -= 0.1;
			Circle.model = Circle.model * glm::mat4x4{ {0.9, 0,0,0}, {0,0.9,0,0}, {0,0,0.9,0}, {0,0,0,1}};
		}
 
		break;

	case 'R':
		if (dRadius < 2.0) {
			dRadius += 0.1;
			
			Circle.model = Circle.model * glm::mat4x4{ { 1.1, 0,0,0 },{ 0,1.1,0,0 },{ 0,0,1.1,0 },{ 0,0,0,1 } };
		}
 
		break;

	case 's':
		if(Z_VIEW < -1){
			Z_VIEW += 0.2;
			Y_VIEW += 0.2;
			X_VIEW += 0.2;
		}
		initView();
		break;

	case 'a':
		if (Z_VIEW > -5) {
			Z_VIEW -= 0.2;
			Y_VIEW -= 0.2;
			X_VIEW -= 0.2;
		}
		initView();
		break;

	case 'z':
		if (iSubdivision >= 2)
		{
			for (unsigned int i = 0; i < CirclePieses.size(); i++)
				CirclePieses.at(i).model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0, 0, 1)) * CirclePieses.at(i).model;
		}
		else
			Circle.model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0, 0, 1)) * Circle.model;

		break;
	case 'y':
		if (iSubdivision >= 2)
		{
			for (unsigned int i = 0; i < CirclePieses.size(); i++)
				CirclePieses.at(i).model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0, 1, 0)) * CirclePieses.at(i).model;
		}
		else
			Circle.model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0, 1, 0)) * Circle.model;
		break;
	case 'x':
		if (iSubdivision >= 2)
		{
			for (unsigned int i = 0; i < CirclePieses.size(); i++)
				CirclePieses.at(i).model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(1, 0, 0)) * CirclePieses.at(i).model;
		}
		else
			Circle.model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(1, 0, 0)) * Circle.model;
		break;
 
	case '+':
		if (iSubdivision < 4.0)
		{
			iPrevSubdivision = iSubdivision;
			iSubdivision+= 1;
			SubDivisionAlgorithm();
		}
		break;

	case '-':
		if (iSubdivision > 0.0)
		{
			iSubdivision -= 1;
			iPrevSubdivision = iSubdivision;
			SubDivisionAlgorithm();
		}
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
					///  START cratewindow: 

	// Initialize the FreeGLUT library (window toolkit)
	glutInit(&argc, argv); // FreeGLUT benötigt mehrere Parameter (siehe main(...)) für das Programm-Kontolle...
						   /*This function does not return anything, but simply sets up FreeGLUT for use in your application.
						   In any program, this should be the first FreeGLUT function you should call!*/

	// GLUT: Initialize freeglut library (window toolkit).
    glutInitWindowSize    (WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(40,40);

	/*FreeGLUT mitteilen, welche Art von OpenGL-Kontext wir für unser Programm verwenden möchten:*/
	glutInitContextVersion(4, 3);	// GLUT: Create a window and opengl context (version 4.3 core profile).
									/*Wenn in der Befehlszeile OpenGL 4.0 nicht angezeigt wird, ist
									bei der Erstellung des Kontexts ein Fehler aufgetreten,
									oder Ihr Treiber hat Ihre Anforderung nach einem OpenGL 4.0-Kontext nicht erfüllt!*/
	glutInitContextProfile(GLUT_CORE_PROFILE);
	/*Wir bitten FreeGLUT, einen vorwärtskompatiblen OpenGL 4.3-Kernprofilkontext zurückzugeben.*/
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);

	/*Welche Art von OpenGL-Kontext wir wünschen und wie das Gerät unsere Szene rendern soll:
	Parameter:
	GLUT_RGB, GLUT_RGBA   : ist ein Flag, das die Art und Weise definiert,
	wie Farben unter Verwendung einzelner Rot-, Grün-, Blau- und Alpha-Werte zusammengesetzt werden.
	GLUT_DEPTH : ermöglicht die Verwendung des Tiefenpuffers, einem wichtigen Mechanismus in der 3D - Computergrafik.
	Der Tiefenpuffer(auch Z - Puffer genannt) enthält die Fließkomma - Z - Tiefeninformation
	jedes auf dem Bildschirm gerenderten Pixels.
	Dieser Mechanismus ist wichtig beim Rendern neuer Objekte, um sicherzustellen,
	dass sie keine Objekte überlappen, die sich näher am Bildschirm befinden
	(und somit auch bestimmt wird, ob das neue Pixel das vorhandene Pixel überschreiben soll).
	GLUT_DOUBLE: Verwendung von Doppelpufferung ermöglicht, eine Funktion, die das Bildflimmern reduziert.
	Bei Doppelpufferung werden alle Zeichenbefehle in einem Puffer außerhalb des Bildschirms ausgeführt,
	der an den Bildschirm gesendet wird, wenn alle Zeichnungen für einen Rahmen abgeschlossen sind,
	sodass keine unvollständigen Bilder angezeigt werden.
	Der aktuell angezeigte Puffer wird als vorderer Puffer bezeichnet, und der Puffer, in den wir ziehen,
	wird als (Sie ahnen Sie es) Back-Puffer bezeichnet. Wenn alle Zeichenbefehle abgeschlossen sind,
	werden diese Puffer ausgetauscht, so dass der hintere Puffer zum vorderen Puffer wird und umgekehrt.
	*/
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	/*Sicherstellen, dass die glutMainLoop-Funktion in main zum Programm zurückkehrt
	und das Programm nicht beendet, wenn es fertig ist.

	Die ursprüngliche GLUT-Bibliothek kehrte nicht zum Programm zurück.
	Nachdem das Rendern von GLUT abgeschlossen war, wurde das Programm beendet.
	Dies bedeutete, dass wenn Sie Speicher zugewiesen hatten, es keine Möglichkeit gab,
	Speicherlecks zu vermeiden, wenn Sie nicht in die GLUT-Bibliothek gehackt wurden.
	glutSetOption(
	GLUT_ACTION_ON_WINDOW_CLOSE,
	GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);*/

	/*Fenster und damit unseren Rendering-Kontext erstellen*/
	glutCreateWindow(WINDOW_TITLE_PREFIX);  // Fenster erstellen: "Aufgabenblatt 02"
	glutID = glutGetWindow();				// glutID->window handle created by FreeGLUT

	if (glutID < 1)
	{
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	// GLEW: Load opengl extensions
	glewExperimental = GL_TRUE;

	// Um OpenGL 4.0-Funktionen unterstützen zu können, benötigt unser Programm Hilfe von der GLEW-Bibliothek!!!
	GLenum GlewInitResult = glewInit();	// Adding GLEW (Werkzeuge!)

	if (GlewInitResult != GLEW_OK)
	{
		/*Wenn dies nicht der Fall ist, schreiben wir eine Fehlernachricht in die Befehlszeile und
		beenden das Programm. Die Fehlernachricht enthält den tatsächlichen Fehler,
		der von GLEW durch den Funktionsaufruf "glewGetErrorString" zurückgegeben wird.*/
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));

		exit(EXIT_FAILURE);
	}

	// GLUT: Set CALLBACS (Rückruffunktionen: glutResize, glutDisplay) for events:
	glutReshapeFunc(glutResize);	// Verändern der Fenstergröße: Funktion zum Umformen wird jedes Mal aufgerufen, wenn die Größe des Fensters geändert wird
	glutDisplayFunc(glutDisplay);	// Rendern der Szene: Anzeigefunktion wird jedes Mal aufgerufen, wenn die Szene auf den Bildschirm gezeichnet wird.
									//glutIdleFunc   (glutDisplay); 

									/*Da wir zu diesem Zeitpunkt einen OpenGL-Kontext haben, ist es sicher, OpenGL-Funktionen aufzurufen.
									Als erstes rufen wir glGetString mit GL_VERSION als Parameter auf,
									um die erstellte Version des OpenGL-Kontexts abzurufen.*/
	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));
						///  END create window

	/// ********* Kontext ist gültig und wir sind zum Zeichnen bereit! ********

	// GLUT: Set CALLBAC (Rückruffunktion: glutKeyboardFunc) for keyboard-events:
	glutKeyboardFunc(glutKeyboard);	//	Tastatureingabe wird als CALLBAC vearbeitet!

									// Init VAO.
									/* Init VAO (Vertex Array Object)->create and use Vertex Buffer Objects (VBO)
									Ein Vertex Array Object (oder VAO) ist ein Objekt,
									das beschreibt, wie die Vertex-Attribute in einem Vertex Buffer Objects Vertex-Puffer-Objekt (VBO) gespeichert werden.
									Dies bedeutet, dass der VAO nicht das eigentliche Objekt ist, das die Vertexdaten speichert,
									sondern der Deskriptor der Vertexdaten.
									*/
	{
		GLCODE(bool result = init());
		if (!result) {
			release();
			cout << "FEHLER bei Init VAO!";
			return -2;
		}
	}

	// GLUT: Loop until the user closes the window
	/*das Herz der Anwendung. Diese Funktion wird ausgeführt, solange das Fenster aktiv ist und
	das Fenster nicht geschlossen wurde.
	Daraufhin werden Zeichenbefehle ausgegeben und Fensteroperationen ausgeführt.*/
	glutMainLoop();	// rendering & event handling

	// Clean up everything on termination.
	release();

	return 0;	// success, oder ->exit(EXIT_SUCCESS);
}
