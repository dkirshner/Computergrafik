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
#include "GraphicObject.h"

float iKlick_X = 0.0f, iKlick_Y = 0.0f, iKlick_Z = 0.0f;
double dZoom = 0.4;	// init
float X_VIEW=-5.0f, Y_VIEW=3.0f, Z_VIEW=-5.0f; //view Matrix
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



GraphicObject quad;
// Axis (zur Darstellung der Koordinatenachsen)
GraphicObject quadXAxis, quadYAxis, quadZAxis;

void renderQuad()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * quad.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	//2 triangles have 6 vertices
	quad.renderObject(12 * 3);

}

void initQuad()
{
	// Construct triangles. These vectors can go out of scope after we have send all data to the graphics card.
	// Every side has two triangles á 3 vertices

	const std::vector<glm::vec3> vertices = {
		{ 1.0f, 1.0f, 1.0f }, //front
		{ -1.0f, 1.0f, 1.0f },
		{ -1.0f, -1.0f, 1.0f },

		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, -1.0f, 1.0f },
		{ -1.0f, -1.0f, 1.0f }, // end front

		{-1.0f, -1.0f, -1.0f }, // bottom
		{ 1.0f, -1.0f, -1.0f },
		{ 1.0f, -1.0f, 1.0f },

		{ -1.0f, -1.0f, -1.0f }, 
		{ -1.0f,-1.0f, 1.0f },
		{ 1.0f, -1.0f, 1.0f }, // end bottom

		{ -1.0f,-1.0f, -1.0f }, // left
		{ -1.0f, 1.0f, -1.0f },
		{ -1.0f, 1.0f, 1.0f },

		{ -1.0f,-1.0f, -1.0f }, 
		{ -1.0f, -1.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f }, // end left

		{ 1.0f, -1.0f, -1.0f }, // right
		{ 1.0f, 1.0f, -1.0f },
		{ 1.0f, 1.0f, 1.0f },

		{ 1.0f, -1.0f, -1.0f },
		{ 1.0f, 1.0f, 1.0f },//!!!
		{ 1.0f, -1.0f, 1.0f }, // end right

		{ -1.0f, -1.0f, -1.0f }, // back
		{ -1.0f, 1.0f, -1.0f },
		{ 1.0f, 1.0f, -1.0f },

		{ -1.0f, -1.0f, -1.0f },
		{ 1.0f, 1.0f, -1.0f },
		{ 1.0f, -1.0f, -1.0f }, // end back

		{ -1.0f, 1.0f, -1.0f }, // top
		{ 1.0f, 1.0f, -1.0f },
		{ 1.0f, 1.0f, 1.0f },

		{ -1.0f, 1.0f, -1.0f },
		{ -1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }  // end top
	};

	const std::vector<glm::vec3> colors = {
		{ 0.5f, 0.0f, 0.0f }, // front
		{ 0.5f, 0.0f, 0.0f },
		{ 0.5f, 0.0f, 0.0f },

		{ 0.5f, 0.0f, 0.0f },
		{ 0.5f, 0.0f, 0.0f },
		{ 0.5f, 0.0f, 0.0f }, // end front

		{ 1.0f, 0.0f, 0.0f }, // bottom
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },

		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f }, // end bottom

		{ 0.0f, 0.5f, 0.0f }, // left
		{ 0.0f, 0.5f, 0.0f },
		{ 0.0f, 0.5f, 0.0f },

		{ 0.0f, 0.5f, 0.0f },
		{ 0.0f, 0.5f, 0.0f },
		{ 0.0f, 0.5f, 0.0f }, // end left

		{ 0.0f, 1.0f, 0.0f }, // right
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },

		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f }, // end right

		{ 0.0f, 0.0f, 1.0f }, // back
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },

		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f }, // end back

		{ 1.0f, 1.0f, 1.0f }, // top
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }  // end top

	};

	// The indices of the sides, beginning at the front
	const std::vector<GLushort> indices = {
		6, 7, 8, // bottom
		9, 10, 11,
		24, 25, 26, // back
		27, 28, 29,
		12, 13, 14, // left
		15, 16, 17,
		18, 19, 20, // right
		21, 22, 23,
		30, 31, 32, // top
		33, 34, 35,
		0, 1, 2, // front
		3, 4, 5

	};

	GLuint programId = program.getHandle();
	quad.initObject(vertices, colors, indices, programId);
	quad.model = glm::scale(glm::mat4(1.0f), glm::vec3(2, 2, 2));
}

//Stellt ein Koordinatensystem dar zur besseren Veranschaulichung (Kein Teil des Praktikums)

void renderQuadXAxis()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * quadXAxis.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	quadXAxis.renderObject(6);

}

void renderQuadYAxis()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * quadYAxis.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	quadYAxis.renderObject(6);

}

void renderQuadZAxis()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * quadZAxis.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 2 triangles.
	quadZAxis.renderObject(6);

}

void initQuadXAxis()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { -3.0f, 0.0f, 0.0f }, { -3.0f, 0.03f, 0.0f }, { 3.0f, 0.03f, 0.0f }, { 3.0f, 0.0f,0.0f } };
	// color
	const std::vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const std::vector<GLushort> indices = { 0, 1, 2, 0, 2, 3 };

	GLuint programId = program.getHandle();

	quadXAxis.initObject(vertices, colors, indices, programId);

	
}

void initQuadYAxis()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { 0.05f, 3.0f, 0.0f },{ 0.08f, 3.0f, 0.0f },{ 0.08f, -3.0f, 0.0f },{ 0.05f, -3.0f, 0.0f } };
	//color
	const std::vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const std::vector<GLushort> indices = { 0, 1, 2, 0, 2, 3 };

	GLuint programId = program.getHandle();

	quadYAxis.initObject(vertices, colors, indices, programId);
}

void initQuadZAxis()
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { 0.0f, 0.0f, 3.0f },{ 0.0f, -0.03f, 3.0f },{ 0.0f, -0.03f, -3.0f },{ 0.0f, -0.0f, -3.0f } };
	// Farbe
	const std::vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const std::vector<GLushort> indices = { 0, 1, 2, 0, 2, 3 };

	GLuint programId = program.getHandle();

	quadZAxis.initObject(vertices, colors, indices, programId);
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

	// Create objects.
	initQuad();
	// show axis:
	initQuadXAxis();
	initQuadYAxis();
	initQuadZAxis();

	return true;
}


/*
Release resources on termination.
*/
void release()
{
	// Shader program will be released upon program termination.
	quad.deleteObject();
	quadXAxis.deleteObject();
	quadYAxis.deleteObject();
	quadZAxis.deleteObject();
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderQuad();
	renderQuadXAxis();
	renderQuadYAxis();
	renderQuadZAxis();
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
	  
	case 'a':
		if(Z_VIEW < 0){
			Z_VIEW += 0.2;
			X_VIEW += 0.2;
		}
		initView();
		break;

	case 's':
		if (Z_VIEW > -5) {
			Z_VIEW -= 0.2;
			X_VIEW -= 0.2;
		}
		initView();
		break;

	case 'z':
		quad.model = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(0, 0, 1)) * quad.model;
		break;
	case 'y':
		quad.model = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(0, 1, 0)) * quad.model;
		break;
	case 'x':
		quad.model = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(1, 0, 0)) * quad.model;
		break;
	}
	glutPostRedisplay();
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

	glutCreateWindow("Aufgabenblatt 03");
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
	//glutIdleFunc   (glutDisplay); // redisplay when idle

	glutKeyboardFunc(glutKeyboard);

	// Init VAO.
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

	// Clean up everything on termination.
	release();

	return 0;
}
