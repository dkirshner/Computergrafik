#include "Header.h"
#include "Render.h"
#include <time.h>


double X_VIEW = 0.0f, Y_VIEW = 0.0f, Z_VIEW = 10.0f; //view Matrix
GLfloat rotateViewZ = 0.0f;
bool bShutDown = true;
clock_t start, end_, end_measure;
bool bStartTime= true;
bool solid = false;


void initView() {
	// Construct view matrix.
	glm::vec3 eye(X_VIEW, Y_VIEW, Z_VIEW);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 5.0f);

	view = glm::lookAt(eye, center, up);
	view = glm::rotate(view, glm::radians(rotateViewZ), glm::vec3(0.0f, 0.0f, 1.0f));
}



/*
Initialization. Should return true if everything is ok and false if something went wrong.
*/
bool init()
{
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


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

	if (bShutDown)
	{
		// Create all objects!!!
		// Achsen
		initAxisSun(program.getHandle());
		initAxisPlanetSlope(program.getHandle());
		initAxisPlanetStraight(program.getHandle());

		// "WIRE-FRAME" Modus aktivieren
		if (solid == true) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Face: GL_FRONT_AND_BACK ---- Modi: GL_POINT, GL_LINE, GL_FILL;
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Face: GL_FRONT_AND_BACK ---- Modi: GL_POINT, GL_LINE, GL_FILL;
		}
		glCullFace(GL_FRONT);	// GL_FRONT, GL_BACK oder GL_FRONT_AND_BACK
		glEnable(GL_CULL_FACE); // abschalten: glDisable () und demselben Argument


		// Objekt Kugel !!!
		initSphere(1.0f, 1.0f, 0.0f, program.getHandle(), &Sun, 1.4, 0);

		initSphere(0.0f, 0.0f, 1.0f, program.getHandle(), &PlanetSlope, 0.4, 1, true);
		SpherePiesesArr[1].at(0).model = glm::translate(SpherePiesesArr[1].at(0).model, glm::vec3(14.0, 0.0, 0.0)); //#1 translate
		SpherePiesesArr[1].at(1).model = glm::translate(SpherePiesesArr[1].at(1).model, glm::vec3(-14.0, 0.0, 0.0));
		SpherePiesesArr[1].at(0).model = glm::rotate(SpherePiesesArr[1].at(0).model, glm::radians(-45.0f), glm::vec3(1.0, 0.0, 0.0)); // #1 kippen um 45°
		SpherePiesesArr[1].at(1).model = glm::rotate(SpherePiesesArr[1].at(1).model, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));  // #1 kippen um 45°

		initSphere(1.0f, 1.0f, 1.0f, program.getHandle(), &MoonSlope_1, 0.1, 2, true);
		SpherePiesesArr[2].at(0).model = glm::translate(SpherePiesesArr[2].at(0).model, glm::vec3(76.0, 7.0, 0.0)); //#1 translate
		SpherePiesesArr[2].at(1).model = glm::translate(SpherePiesesArr[2].at(1).model, glm::vec3(-76.0, -7.0, 0.0));
		SpherePiesesArr[2].at(0).model = glm::rotate(SpherePiesesArr[2].at(0).model, glm::radians(-45.0f), glm::vec3(1.0, 0.0, 0.0)); // #1 kippen um 45°
		SpherePiesesArr[2].at(1).model = glm::rotate(SpherePiesesArr[2].at(1).model, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));  // #1 kippen um 45°


		initSphere(1.0f, 1.0f, 1.0f, program.getHandle(), &MoonSlope_2, 0.1, 3, true);
		SpherePiesesArr[3].at(0).model = glm::translate(SpherePiesesArr[3].at(0).model, glm::vec3(63.0, 19.0, 0.0)); //#1 translate
		SpherePiesesArr[3].at(1).model = glm::translate(SpherePiesesArr[3].at(1).model, glm::vec3(-63.0, -19.0, 0.0));
		SpherePiesesArr[3].at(0).model = glm::rotate(SpherePiesesArr[3].at(0).model, glm::radians(-45.0f), glm::vec3(1.0, 0.0, 0.0)); // #1 kippen um 45°
		SpherePiesesArr[3].at(1).model = glm::rotate(SpherePiesesArr[3].at(1).model, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));  // #1 kippen um 45°

		initSphere(1.0f, 1.0f, 1.0f, program.getHandle(), &MoonSlope_3, 0.1, 4, true);
		SpherePiesesArr[4].at(0).model = glm::translate(SpherePiesesArr[4].at(0).model, glm::vec3(45.0, -19.0, 6.0)); //#1 translate, 49
		SpherePiesesArr[4].at(1).model = glm::translate(SpherePiesesArr[4].at(1).model, glm::vec3(-45.0, 19.0, 6.0));
		SpherePiesesArr[4].at(0).model = glm::rotate(SpherePiesesArr[4].at(0).model, glm::radians(-45.0f), glm::vec3(1.0, 0.0, 0.0)); // #1 kippen um 45°
		SpherePiesesArr[4].at(1).model = glm::rotate(SpherePiesesArr[4].at(1).model, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));  // #1 kippen um 45°


		initSphere(1.0f, 1.0f, 1.0f, program.getHandle(), &MoonSlope_4, 0.1, 5, true);
		SpherePiesesArr[5].at(0).model = glm::translate(SpherePiesesArr[5].at(0).model, glm::vec3(45.0, -7.0, -6.0)); //#1 translate, 36
		SpherePiesesArr[5].at(1).model = glm::translate(SpherePiesesArr[5].at(1).model, glm::vec3(-45.0, 7.0, -6.0));
		SpherePiesesArr[5].at(0).model = glm::rotate(SpherePiesesArr[5].at(0).model, glm::radians(-45.0f), glm::vec3(1.0, 0.0, 0.0)); // #1 kippen um 45°
		SpherePiesesArr[5].at(1).model = glm::rotate(SpherePiesesArr[5].at(1).model, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));  // #1 kippen um 45°

		//----------------------------------------------------------------------------------------------------------------------------

		initSphere(0.0f, 0.0f, 1.0f, program.getHandle(), &PlanetStraight, 0.3, 6, true);
		SpherePiesesArr[6].at(0).model = glm::translate(SpherePiesesArr[6].at(0).model, glm::vec3(-12.0, 0.0, 0.0)); //#1 translate
		SpherePiesesArr[6].at(1).model = glm::translate(SpherePiesesArr[6].at(1).model, glm::vec3(12.0, 0.0, 0.0));

		initSphere(1.0f, 1.0f, 1.0f, program.getHandle(), &MoonSlope_1, 0.1, 7, true);
		SpherePiesesArr[7].at(0).model = glm::translate(SpherePiesesArr[7].at(0).model, glm::vec3(-26.0, 0.0, 0.0)); //#1 translate
		SpherePiesesArr[7].at(1).model = glm::translate(SpherePiesesArr[7].at(1).model, glm::vec3(26.0, 0.0, 0.0));

		initSphere(1.0f, 1.0f, 1.0f, program.getHandle(), &MoonSlope_2, 0.1, 8, true);
		SpherePiesesArr[8].at(0).model = glm::translate(SpherePiesesArr[8].at(0).model, glm::vec3(-46.0, 0.0, 0.0)); //#1 translate
		SpherePiesesArr[8].at(1).model = glm::translate(SpherePiesesArr[8].at(1).model, glm::vec3(46.0, 0.0, 0.0));

		initSphere(1.0f, 1.0f, 1.0f, program.getHandle(), &MoonSlope_3, 0.1, 9, true);
		SpherePiesesArr[9].at(0).model = glm::translate(SpherePiesesArr[9].at(0).model, glm::vec3(-36.0, 0.0, 10.0)); //#1 translate
		SpherePiesesArr[9].at(1).model = glm::translate(SpherePiesesArr[9].at(1).model, glm::vec3(36.0, 0.0, 10.0));

		initSphere(1.0f, 1.0f, 1.0f, program.getHandle(), &MoonSlope_4, 0.1, 10, true);
		SpherePiesesArr[10].at(0).model = glm::translate(SpherePiesesArr[10].at(0).model, glm::vec3(-36.0, 0.0, -10.0)); //#1 translate
		SpherePiesesArr[10].at(1).model = glm::translate(SpherePiesesArr[10].at(1).model, glm::vec3(36.0, 0.0, -10.0));

	}

	return true;
}

void rotatePlanetSystem()
{
	//Rotation des Gesammten Systems
	// Der Planet schief
	SpherePiesesArr[1].at(0).model = glm::rotate(SpherePiesesArr[1].at(0).model, glm::radians(0.5f), glm::vec3(-1.0, -1.0, 0.0));	// Rotation den gekippten Planeten um eigene Achse
	SpherePiesesArr[1].at(1).model = glm::rotate(SpherePiesesArr[1].at(1).model, glm::radians(0.5f), glm::vec3(1.0, 1.0, 0.0));		// Rotation den gekippten Planeten um eigene Achse
	SpherePiesesArr[1].at(0).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[1].at(0).model;
	SpherePiesesArr[1].at(1).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[1].at(1).model;
	// Achse schief
	AxisPlanetSlope.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * AxisPlanetSlope.model;
	//Monde Planet mit schiefer Achse
	SpherePiesesArr[2].at(0).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[2].at(0).model; // Über die Sonne
	SpherePiesesArr[2].at(1).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[2].at(1).model;
	//SpherePiesesArr[2].at(0).model = glm::rotate(SpherePiesesArr[2].at(0).model, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));	// #2 Rotation den gekippten Planeten um eigene Achse
	//SpherePiesesArr[2].at(1).model = glm::rotate(SpherePiesesArr[2].at(1).model, glm::radians(0.5f), glm::vec3(0.0, -1.0, 0.0)); // #2 Rotation den gekippten Planeten um eigene Achse
	// Modify model matrix.
	SpherePiesesArr[2].at(0).model = glm::mat4(1.0f) *  glm::translate(SpherePiesesArr[1].at(0).model, glm::vec3(-6.0, -2.0, 0.0));
	SpherePiesesArr[2].at(0).model = glm::scale(SpherePiesesArr[2].at(0).model, glm::vec3(0.4, 0.4, 0.4));	//scale
	SpherePiesesArr[2].at(1).model = glm::mat4(1.0f) * glm::translate(SpherePiesesArr[1].at(1).model, glm::vec3(6.0, 2.0, 0.0));
	SpherePiesesArr[2].at(1).model = glm::scale(SpherePiesesArr[2].at(1).model, glm::vec3(0.4, 0.4, 0.4));	//scale

	SpherePiesesArr[3].at(0).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[3].at(0).model;
	SpherePiesesArr[3].at(1).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[3].at(1).model;
	//SpherePiesesArr[3].at(0).model = glm::rotate(SpherePiesesArr[3].at(0).model, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));	// #2 Rotation den gekippten Planeten um eigene Achse
	//SpherePiesesArr[3].at(1).model = glm::rotate(SpherePiesesArr[3].at(1).model, glm::radians(0.5f), glm::vec3(0.0, -1.0, 0.0)); // #2 Rotation den gekippten Planeten um eigene Achse
	// Modify model matrix.
	SpherePiesesArr[3].at(0).model = glm::mat4(1.0f) *  glm::translate(SpherePiesesArr[1].at(0).model, glm::vec3(-2.0, -6.0, 0.0));
	SpherePiesesArr[3].at(0).model = glm::scale(SpherePiesesArr[3].at(0).model, glm::vec3(0.4, 0.4, 0.4));	//scale
	SpherePiesesArr[3].at(1).model = glm::mat4(1.0f) * glm::translate(SpherePiesesArr[1].at(1).model, glm::vec3(2.0, 6.0, 0.0));
	SpherePiesesArr[3].at(1).model = glm::scale(SpherePiesesArr[3].at(1).model, glm::vec3(0.4, 0.4, 0.4));	//scale

	SpherePiesesArr[4].at(0).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[4].at(0).model;
	SpherePiesesArr[4].at(1).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[4].at(1).model;
	//SpherePiesesArr[4].at(0).model = glm::rotate(SpherePiesesArr[4].at(0).model, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));	// #2 Rotation den gekippten Planeten um eigene Achse
	//SpherePiesesArr[4].at(1).model = glm::rotate(SpherePiesesArr[4].at(1).model, glm::radians(0.5f), glm::vec3(0.0, -1.0, 0.0)); // #2 Rotation den gekippten Planeten um eigene Achse
	// Modify model matrix.
	SpherePiesesArr[4].at(0).model = glm::mat4(1.0f) *  glm::translate(SpherePiesesArr[1].at(0).model, glm::vec3(2.0, 2.0, 6.0));
	SpherePiesesArr[4].at(0).model = glm::scale(SpherePiesesArr[4].at(0).model, glm::vec3(0.4, 0.4, 0.4));	//scale
	SpherePiesesArr[4].at(1).model = glm::mat4(1.0f) * glm::translate(SpherePiesesArr[1].at(1).model, glm::vec3(-2.0, -2.0, 6.0));
	SpherePiesesArr[4].at(1).model = glm::scale(SpherePiesesArr[4].at(1).model, glm::vec3(0.4, 0.4, 0.4));	//scale

	SpherePiesesArr[5].at(0).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[5].at(0).model;
	SpherePiesesArr[5].at(1).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[5].at(1).model;
	//SpherePiesesArr[5].at(0).model = glm::rotate(SpherePiesesArr[5].at(0).model, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));	// #2 Rotation den gekippten Planeten um eigene Achse
	//SpherePiesesArr[5].at(1).model = glm::rotate(SpherePiesesArr[5].at(1).model, glm::radians(0.5f), glm::vec3(0.0, -1.0, 0.0)); // #2 Rotation den gekippten Planeten um eigene Achse
	// Modify model matrix.
	SpherePiesesArr[5].at(0).model = glm::mat4(1.0f) *  glm::translate(SpherePiesesArr[1].at(0).model, glm::vec3(6.0, 2.0, -2.0));
	SpherePiesesArr[5].at(0).model = glm::scale(SpherePiesesArr[5].at(0).model, glm::vec3(0.4, 0.4, 0.4));	//scale
	SpherePiesesArr[5].at(1).model = glm::mat4(1.0f) * glm::translate(SpherePiesesArr[1].at(1).model, glm::vec3(-6.0, -2.0, -2.0));
	SpherePiesesArr[5].at(1).model = glm::scale(SpherePiesesArr[5].at(1).model, glm::vec3(0.4, 0.4, 0.4));	//scale

																											// Planet mit gerader Achse
	SpherePiesesArr[6].at(0).model = glm::rotate(SpherePiesesArr[6].at(0).model, glm::radians(0.5f), glm::vec3(0.0, -1.0, 0.0));	// #2 Rotation des geraden Planeten um eigene Achse
	SpherePiesesArr[6].at(1).model = glm::rotate(SpherePiesesArr[6].at(1).model, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0)); // #2 Rotation des geraden Planeten um eigene Achse
	SpherePiesesArr[6].at(0).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[6].at(0).model;
	SpherePiesesArr[6].at(1).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[6].at(1).model;
	// Achse gerade
	AxisPlanetStraight.model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * AxisPlanetStraight.model;
	/*
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model,glm::vec3(0,0,0)); //position = 0,0,0
	model = glm::rotate(model,glm::radians(0.0f),glm::vec3(1,0,0));//rotation x = 0.0 degrees
	model = glm::rotate(model,glm::radians(0.0f),glm::vec3(0,1,0));//rotation y = 0.0 degrees
	model = glm::rotate(model,glm::radians(0.0f),glm::vec3(0,0,1));//rotation z = 0.0 degrees
	model = glm::scale(model,glm::vec3(1,1,1);//scale = 1,1,1
	*/
	//Monde Planet Grade
	SpherePiesesArr[7].at(0).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[7].at(0).model;
	SpherePiesesArr[7].at(1).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[7].at(1).model;
	//SpherePiesesArr[7].at(0).model = glm::rotate(SpherePiesesArr[7].at(0).model, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));	// #2 Rotation den gekippten Planeten um eigene Achse
	//SpherePiesesArr[7].at(1).model = glm::rotate(SpherePiesesArr[7].at(1).model, glm::radians(0.5f), glm::vec3(0.0, -1.0, 0.0)); // #2 Rotation den gekippten Planeten um eigene Achse
	// Modify model matrix.
	SpherePiesesArr[7].at(0).model = glm::mat4(1.0f) *  glm::translate(SpherePiesesArr[6].at(0).model, glm::vec3(-3.0, 0.0, 0.0));
	SpherePiesesArr[7].at(0).model = glm::scale(SpherePiesesArr[7].at(0).model, glm::vec3(0.4, 0.4, 0.4));	//scale
	SpherePiesesArr[7].at(1).model = glm::mat4(1.0f) * glm::translate(SpherePiesesArr[6].at(1).model, glm::vec3(3.0, 0.0, 0.0));
	SpherePiesesArr[7].at(1).model = glm::scale(SpherePiesesArr[7].at(1).model, glm::vec3(0.4, 0.4, 0.4));	//scale

	SpherePiesesArr[8].at(0).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[8].at(0).model;
	SpherePiesesArr[8].at(1).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[8].at(1).model;
	//SpherePiesesArr[8].at(0).model = glm::rotate(SpherePiesesArr[8].at(0).model, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));	// #2 Rotation den gekippten Planeten um eigene Achse
	//SpherePiesesArr[8].at(1).model = glm::rotate(SpherePiesesArr[8].at(1).model, glm::radians(0.5f), glm::vec3(0.0, -1.0, 0.0)); // #2 Rotation den gekippten Planeten um eigene Achse
	// Modify model matrix.	
	SpherePiesesArr[8].at(0).model = glm::mat4(1.0f) *  glm::translate(SpherePiesesArr[6].at(0).model, glm::vec3(3.0, 0.0, 0.0));
	SpherePiesesArr[8].at(0).model = glm::scale(SpherePiesesArr[8].at(0).model, glm::vec3(0.4, 0.4, 0.4));	//scale
	SpherePiesesArr[8].at(1).model = glm::mat4(1.0f) * glm::translate(SpherePiesesArr[6].at(1).model, glm::vec3(-3.0, 0.0, 0.0));
	SpherePiesesArr[8].at(1).model = glm::scale(SpherePiesesArr[8].at(1).model, glm::vec3(0.4, 0.4, 0.4));	//scale

	SpherePiesesArr[9].at(0).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[9].at(0).model;
	SpherePiesesArr[9].at(1).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[9].at(1).model;
	//SpherePiesesArr[9].at(0).model = glm::rotate(SpherePiesesArr[9].at(0).model, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));	// #2 Rotation den gekippten Planeten um eigene Achse
	//SpherePiesesArr[9].at(1).model = glm::rotate(SpherePiesesArr[9].at(1).model, glm::radians(0.5f), glm::vec3(0.0, -1.0, 0.0)); // #2 Rotation den gekippten Planeten um eigene Achse
	// Modify model matrix.	
	SpherePiesesArr[9].at(0).model = glm::mat4(1.0f) *  glm::translate(SpherePiesesArr[6].at(0).model, glm::vec3(0.0, 0.0, -3.0));
	SpherePiesesArr[9].at(0).model = glm::scale(SpherePiesesArr[9].at(0).model, glm::vec3(0.4, 0.4, 0.4));	//scale
	SpherePiesesArr[9].at(1).model = glm::mat4(1.0f) * glm::translate(SpherePiesesArr[6].at(1).model, glm::vec3(0.0, 0.0, 3.0));
	SpherePiesesArr[9].at(1).model = glm::scale(SpherePiesesArr[9].at(1).model, glm::vec3(0.4, 0.4, 0.4));	//scale

	SpherePiesesArr[10].at(0).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[10].at(0).model;
	SpherePiesesArr[10].at(1).model = glm::rotate(glm::mat4(1.0f), glm::radians(iVelocity), glm::vec3(0, 1, 0)) * SpherePiesesArr[10].at(1).model;
	//SpherePiesesArr[10].at(0).model = glm::rotate(SpherePiesesArr[10].at(0).model, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));	// #2 Rotation den gekippten Planeten um eigene Achse
	//SpherePiesesArr[10].at(1).model = glm::rotate(SpherePiesesArr[10].at(1).model, glm::radians(0.5f), glm::vec3(0.0, -1.0, 0.0)); // #2 Rotation den gekippten Planeten um eigene Achse
	// Modify model matrix.	
	SpherePiesesArr[10].at(0).model = glm::mat4(1.0f) *  glm::translate(SpherePiesesArr[6].at(0).model, glm::vec3(0.0, 0.0, 3.0));
	SpherePiesesArr[10].at(0).model = glm::scale(SpherePiesesArr[10].at(0).model, glm::vec3(0.4, 0.4, 0.4));	//scale
	SpherePiesesArr[10].at(1).model = glm::mat4(1.0f) * glm::translate(SpherePiesesArr[6].at(1).model, glm::vec3(0.0, 0.0, -3.0));
	SpherePiesesArr[10].at(1).model = glm::scale(SpherePiesesArr[10].at(1).model, glm::vec3(0.4, 0.4, 0.4));	//scale

	glutPostRedisplay();
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
	// Das Shader-Programm wird nach Beendigung des Programms freigegeben

	//releaseObject(Y_AxisSun);
	AxisSun.deleteObject();
	AxisPlanetSlope.deleteObject();
	AxisPlanetStraight.deleteObject();
	releaseObject(Sun);
	releaseObject(PlanetSlope);
	releaseObject(MoonSlope_1);
	releaseObject(MoonSlope_2);
	releaseObject(MoonSlope_3);
	releaseObject(MoonSlope_4);
	releaseObject(PlanetStraight);
	releaseObject(MoonStraight_1);
	releaseObject(MoonStraight_2);
	releaseObject(MoonStraight_3);
	releaseObject(MoonStraight_4);
}

/*
Resize callback.
*/
void glutResize(int width, int height)
{
	// Division by zero is bad...
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = glm::perspective(45.0f, (float)width / height, zNear, zFar);
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

	case '-':
		if (Z_VIEW < 20) {
			Z_VIEW += 0.1;
			Y_VIEW += 0.0;
			X_VIEW += 0.0;
		}
		initView();
		break;

	case '+':
		if (Z_VIEW > 3) {
			Z_VIEW -= 0.1;
			Y_VIEW -= 0.0;
			X_VIEW -= 0.0;
		}
		initView();
		break;

		case 'd':	//Rotation des Gesammten Systems
			if (iVelocity < -0.1)
				iVelocity += 0.007f;
			break;

		case 'f':	//Rotation des Gesammten Systems beschleunigen
			if (iVelocity > -0.40)
				iVelocity -= 0.003f;

		break;

		case 'u': //Bewegung des Gesammten Planetensystems entlang der Y-Achse nach unten
				  //Planeten
			for (unsigned int i = 0; i < SpherePiesesArr[6].size(); i++)
			{
				if (i < SpherePiesesArr[6].size() / 2.0)
					SpherePiesesArr[6].at(i).model = glm::translate(SpherePiesesArr[6].at(i).model, glm::vec3(0.0, -0.3, 0.0));
				else
					SpherePiesesArr[6].at(i).model = glm::translate(SpherePiesesArr[6].at(i).model, glm::vec3(0.0, 0.3, 0.0));
			}

			AxisPlanetStraight.model = glm::translate(AxisPlanetStraight.model, glm::vec3(0, -0.05, 0.0));
	
			break;

		case 'i': //Bewegung des Gesammten Planetensystems entlang der Y-Achse nach unten
				  //Planeten
			for (unsigned int i = 0; i < SpherePiesesArr[6].size(); i++)
			{
				if (i < SpherePiesesArr[6].size() / 2.0)
					SpherePiesesArr[6].at(i).model = glm::translate(SpherePiesesArr[6].at(i).model, glm::vec3(0.0, 0.3, 0.0));
				else
					SpherePiesesArr[6].at(i).model = glm::translate(SpherePiesesArr[6].at(i).model, glm::vec3(0.0, -0.3, 0.0));
			}

			AxisPlanetStraight.model = glm::translate(AxisPlanetStraight.model, glm::vec3(0, 0.05, 0.0));
			break;

		case 'q':
			if (bStartTime)
			{
				start = clock();
				bStartTime = false;
			}

			end_measure = start + 1;
			end_ = clock();

			if (end_measure > end_)
				return;

			bStartTime = true;

				rotateViewZ += 1.5f;
			
			bShutDown = false;
			init();
			bShutDown = true;
			break;
		case 'w':
			if (bStartTime)
			{
				start = clock();
				bStartTime = false;
			}

			end_measure = start + 1;
			end_ = clock();

			if (end_measure > end_)
				return;

			bStartTime = true;

				rotateViewZ -= 1.5f;
			

			bShutDown = false;
			init();
			bShutDown = true;
			break; 

		case 'o':   //Rotation des schiefen Planeten um Axis "X" um 45°

			SpherePiesesArr[1].at(0).model = glm::rotate(SpherePiesesArr[1].at(0).model, glm::radians((- 10.1f)), glm::vec3(0.0, 0.0, 1.0));	 //	rotierem um 45° erste Hälfte mit Uhrzeigersinn
			SpherePiesesArr[1].at(1).model = glm::rotate(SpherePiesesArr[1].at(1).model, glm::radians((10.1f)), glm::vec3(0.0, 0.0, 1.0));		 // rotierem um 45° erste Hälfte mit Uhrzeigersinn

			break;

		case 'p':  //Rotation des schiefen Planeten um Axis "X" um -45°

		SpherePiesesArr[1].at(0).model = glm::rotate(SpherePiesesArr[1].at(0).model, glm::radians((rotateZ)), glm::vec3(0.0f, 0.0f, 1.0f));		//	rotierem um 45° erste Hälfte gegen Uhrzeigersinn
		SpherePiesesArr[1].at(1).model = glm::rotate(SpherePiesesArr[1].at(1).model, glm::radians((rotateZ)), glm::vec3(0.0f, 0.0f, 1.0f));		//	rotierem um 45° zweite Hälfte gegen Uhrzeigersinn
	
			break;

		case 'a': 
			solid = !solid;
			if (solid == true) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Face: GL_FRONT_AND_BACK ---- Modi: GL_POINT, GL_LINE, GL_FILL;
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Face: GL_FRONT_AND_BACK ---- Modi: GL_POINT, GL_LINE, GL_FILL;
			}
			
			break;

		default:
			break;
	}

	glutPostRedisplay();
}

/*
Rendering.
*/
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//renderY_AxisSun(view, projection, program, Y_AxisSun);
	renderAxisSun(view, projection, program);
	renderAxisPlanetSlope(view, projection, program);
	renderAxisPlanetStraight(view, projection, program);

	// Sun
	for (unsigned int i = 0; i < SpherePiesesArr[0].size(); i++)
		renderSphere(view, projection, program, SpherePiesesArr[0].at(i));

	for (unsigned int i = 0; i < SpherePiesesArr[1].size(); i++)
		renderSphere(view, projection, program, SpherePiesesArr[1].at(i));

	for (unsigned int i = 0; i < SpherePiesesArr[2].size(); i++)
		renderSphere(view, projection, program, SpherePiesesArr[2].at(i));

	for (unsigned int i = 0; i < SpherePiesesArr[3].size(); i++)
		renderSphere(view, projection, program, SpherePiesesArr[3].at(i));

	for (unsigned int i = 0; i < SpherePiesesArr[4].size(); i++)
		renderSphere(view, projection, program, SpherePiesesArr[4].at(i));

	for (unsigned int i = 0; i < SpherePiesesArr[5].size(); i++)
		renderSphere(view, projection, program, SpherePiesesArr[5].at(i));


	for (unsigned int i = 0; i < SpherePiesesArr[6].size(); i++)
		renderSphere(view, projection, program, SpherePiesesArr[6].at(i));

	for (unsigned int i = 0; i < SpherePiesesArr[7].size(); i++)
		renderSphere(view, projection, program, SpherePiesesArr[7].at(i));

	for (unsigned int i = 0; i < SpherePiesesArr[8].size(); i++)
		renderSphere(view, projection, program, SpherePiesesArr[8].at(i));

	for (unsigned int i = 0; i < SpherePiesesArr[9].size(); i++)
		renderSphere(view, projection, program, SpherePiesesArr[9].at(i));

	for (unsigned int i = 0; i < SpherePiesesArr[10].size(); i++)
		renderSphere(view, projection, program, SpherePiesesArr[10].at(i));
}

void glutDisplay()
{
	GLCODE(render());
	glutSwapBuffers();
	rotatePlanetSystem();
}

int main(int argc, char** argv)
{
	///  START: erzeuge Fenster
	// Initialisiere "FreeGLUT" - Bibliothek (window toolkit)
	glutInit(&argc, argv); // FreeGLUT benötigt mehrere Parameter (siehe main(...)) für das Programm-Kontolle...
						   /*This function does not return anything, but simply sets up FreeGLUT for use in your application.
						   In any program, this should be the first FreeGLUT function you should call!*/

						   // GLUT: Initialisiere "FreeGLUT" - Bibliothek (window toolkit).
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(40, 40);

	/*FreeGLUT mitteilen, welche Art von OpenGL-Kontext wir für unser Programm verwenden möchten:*/
	glutInitContextVersion(4, 3);	// GLUT:  Erstellen einen OpenGL-Kontext(version 4.3 core profile).
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
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS	);*/

	/*Fenster und damit unseren Rendering-Kontext erstellen*/
	glutCreateWindow(WINDOW_TITLE_PREFIX);  // Fenster erstellen: "Praktikum Komputergrafik: Aufgabeblatt 4"
	glutID = glutGetWindow();				// glutID->window handle created by FreeGLUT

	if (glutID < 1)
	{
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	// GLEW: opengl -Erweiterungen laden!
	glewExperimental = GL_TRUE;

	// Um OpenGL 4.0-Funktionen unterstützen zu können, benötigt unser Programm Hilfe von der GLEW-Bibliothek!!!
	GLenum GlewInitResult = glewInit();	// GLEW - Werkzeuge (!) aktivieren

	if (GlewInitResult != GLEW_OK)
	{
		/*Wenn dies nicht der Fall ist, schreiben wir eine Fehlernachricht in die Befehlszeile und
		beenden das Programm. Die Fehlernachricht enthält den tatsächlichen Fehler,
		der von GLEW durch den Funktionsaufruf "glewGetErrorString" zurückgegeben wird.*/
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));

		exit(EXIT_FAILURE);
	}

	// GLUT: Rückruffunktionen: glutResize(), glutDisplay()  (CALLBACS) für folgende Ereignisse:
	glutReshapeFunc(glutResize);	// Verändern der Fenstergröße: Funktion zum Umformen wird jedes Mal aufgerufen, wenn die Größe des Fensters geändert wird
	glutDisplayFunc(glutDisplay);	// Rendern der Szene: Anzeigefunktion wird jedes Mal aufgerufen, wenn die Szene auf den Bildschirm gezeichnet wird.
									//glutIdleFunc   (glutDisplay); 

									/*Da wir zu diesem Zeitpunkt einen OpenGL-Kontext haben, ist es sicher, OpenGL-Funktionen aufzurufen.
									Als erstes rufen wir glGetString mit GL_VERSION als Parameter auf,
									um die erstellte Version des OpenGL-Kontexts abzurufen.*/
	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));
	///  END Fenster erstellen

	/// ********* Kontext ist gültig und wir sind zum Zeichnen bereit! ********

	// GLUT: Rückruffunktion: glutKeyboardFunc (CALLBAC) für die Tastatur-Ereignisse:
	glutKeyboardFunc(glutKeyboard);	//	Tastatureingabe wird als CALLBAC vearbeitet!
									/* Initialisation von VAO (Vertex Array Object)->Erstellen und Verwenden von Vertex-Pufferobjekten -> Vertex Buffer Objects (VBO)
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

	// GLUT: Schleife, bis der Benutzer das Fenster schließt
	/*das Herz der Anwendung. Diese Funktion wird ausgeführt, solange das Fenster aktiv ist und
	das Fenster nicht geschlossen wurde.
	Daraufhin werden Zeichenbefehle ausgegeben und Fensteroperationen ausgeführt.*/
	glutMainLoop();	// Rendering und Handhabung des Events

	release();	// Räumen bei Beendigung alles auf.

	return 0;	// Erfolg, oder ->exit(EXIT_SUCCESS);
}