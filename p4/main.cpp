#include "Init.h"
#include "Header.h"
#include "Render.h"


void rotate()
{
	//Rotation des Gesammten Systems
	//Planeten
	Planetschief.model = glm::rotate(Sonne.model, glm::radians(iVelocity), glm::vec3(0, 1, 0)) * Planetschief.model;
	PlanetGrade.model = glm::rotate(Sonne.model, glm::radians(iVelocity), glm::vec3(0, 1, 0)) * PlanetGrade.model;
	//Monde Planet Grade
	moon1.model = glm::rotate(PlanetGrade.model, glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon1.model;
	moon2.model = glm::rotate(PlanetGrade.model, glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon2.model;
	moon3.model = glm::rotate(PlanetGrade.model, glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon3.model;
	moon4.model = glm::rotate(PlanetGrade.model, glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon4.model;
	//Monde Planet schief:
	//unten
	moon5.model = glm::rotate(Planetschief.model, glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon5.model;
	moon6.model = glm::rotate(Planetschief.model, glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon6.model;

	moon7.model = glm::rotate(Planetschief.model, glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon7.model;
	moon8.model = glm::rotate(Planetschief.model, glm::radians(iVelocity), glm::vec3(0, 1, 0)) * moon8.model;

	
	glutPostRedisplay();
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{
	// OpenGL: Set "background" color and enable depth testing.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
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

	// Create all objects!!!
	init_Y_Axis_Sun(program.getHandle(), &Y_AxisSun);
	init_Y_Axis_Planet(program.getHandle(), &Y_AxisMoon, PlanetGrade);
	initY_AxisMoonSlope(program.getHandle(), &Y_AxisMoonSlope, Planetschief);


	// GLUT: create vertex-array-object for glut geometry, the "default"
	// must be bound before the glutWireSphere call

	initWireSphere(program.getHandle(), &Sonne);
	initWireSphereSchief(program.getHandle(), &Planetschief);

	Planetschief.model = Planetschief.model * glm::rotate(Sonne.model, glm::radians(0.0f), glm::vec3(1, 0, 0)); // kippen um 45° von Planetschief

	initWireSphereGrade(program.getHandle(), &PlanetGrade);

	initWireSpheremoon1(program.getHandle(), &moon1, PlanetGrade);
	initWireSpheremoon1(program.getHandle(), &moon2, PlanetGrade);
	initWireSpheremoon1(program.getHandle(), &moon3, PlanetGrade);
	initWireSpheremoon1(program.getHandle(), &moon4, PlanetGrade);

	
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
			iVelocity -= 0.1f;
		break;

	case 'W':	//Rotation des Gesammten Systems beschleunigen
		if(iVelocity < 0.7)
			iVelocity += 0.1f;

		break;
	case 't': //Bewegung des Gesammten Planetensystems entlang der Y-Achse nach unten
				//Planeten
		Sonne.model = glm::translate(Sonne.model, glm::vec3(0.0, 0.0, 1.0));
		Y_AxisSun.model = glm::translate(Y_AxisSun.model, glm::vec3(0.0, 0.0, 1.0));
		PlanetGrade.model = glm::translate(PlanetGrade.model, glm::vec3(0.0, 0.0, 1.0));
		Planetschief.model = glm::translate(Planetschief.model, glm::vec3(0.0, -0.7, 0.7));
		//Monde Planet Grade
		Y_AxisMoonSlope.model = glm::translate(Y_AxisMoonSlope.model, glm::vec3(0.0, -0.7, 0.7));
		Y_AxisMoon.model = glm::translate(Y_AxisMoon.model, glm::vec3(0.0, 1.0, 0.0));
		moon1.model = glm::translate(moon1.model, glm::vec3(0.0, 1.0, 0.0));
		moon2.model = glm::translate(moon2.model, glm::vec3(0.0, 1.0, 0.0));
		moon3.model = glm::translate(moon3.model, glm::vec3(0.0, 1.0, 0.0));
		moon4.model = glm::translate(moon4.model, glm::vec3(0.0, -0.7, 0.7));
		//Monde Planet schief:
		//unten

		moon5.model = glm::translate(moon5.model, glm::vec3(0.0, -0.7, 0.7));
		moon6.model = glm::translate(moon6.model, glm::vec3(0.0, -0.7, 0.7));
		moon7.model = glm::translate(moon7.model, glm::vec3(0.0, -0.7, 0.7));
		//mitte
		moon8.model = glm::translate(moon8.model, glm::vec3(0.0, -0.7, 0.7));
		break;
	case 'T': //Bewegung des Gesammten Planetensystems entlang der Y-Achse nach oben
				//Planeten
		Sonne.model = glm::translate(Sonne.model, glm::vec3(0.0, 0.0, -1.0));
		Y_AxisSun.model = glm::translate(Y_AxisSun.model, glm::vec3(0.0, 0.0, -1.0));
		PlanetGrade.model = glm::translate(PlanetGrade.model, glm::vec3(0.0, 0.0, -1.0));
		Planetschief.model = glm::translate(Planetschief.model, glm::vec3(0.0, 0.7, -0.7));
		//Monde Planet Grade
		Y_AxisMoonSlope.model = glm::translate(Y_AxisMoonSlope.model, glm::vec3(0.0, 0.7, -0.7));
		Y_AxisMoon.model = glm::translate(Y_AxisMoon.model, glm::vec3(0.0, 0.0, -1.0));

		moon1.model = glm::translate(moon1.model, glm::vec3(0.0, -1.0, 0.0));
		moon2.model = glm::translate(moon2.model, glm::vec3(0.0, -1.0, 0.0));
		moon3.model = glm::translate(moon3.model, glm::vec3(0.0, -1.0, 0.0));
		moon4.model = glm::translate(moon4.model, glm::vec3(0.0, -1.0, 0.0));
		//Monde Planet schief:
		//unten

		moon5.model = glm::translate(moon5.model, glm::vec3(0.0, 0.7, -0.7));
		moon6.model = glm::translate(moon6.model, glm::vec3(0.0, 0.7, -0.7));
		moon7.model = glm::translate(moon7.model, glm::vec3(0.0, 0.7, -0.7));
		//mitte
		moon8.model = glm::translate(moon8.model, glm::vec3(0.0, 0.7, -0.7));

		break;
	case 'l': //Grader Planet nach unten bewegen
		PlanetGrade.model = glm::translate(PlanetGrade.model, glm::vec3(0.0, 0.0, 1.0));
		Y_AxisMoon.model = glm::translate(Y_AxisMoon.model, glm::vec3(0.0, 0.0, 1.0));
		moon1.model = glm::translate(moon1.model, glm::vec3(0.0, 1.0, 0.0));
		moon2.model = glm::translate(moon2.model, glm::vec3(0.0, 1.0, 0.0));
		moon3.model = glm::translate(moon3.model, glm::vec3(0.0, 1.0, 0.0));
		moon4.model = glm::translate(moon4.model, glm::vec3(0.0, 1.0, 0.0));
		break;
	case 'L': //Grader Planet nach oben bewegen
		PlanetGrade.model = glm::translate(PlanetGrade.model, glm::vec3(0.0, 0.0, -1.0));
		Y_AxisMoon.model = glm::translate(Y_AxisMoon.model, glm::vec3(0.0, 0.0, -1.0));
		moon1.model = glm::translate(moon1.model, glm::vec3(0.0, -1.0, 0.0));
		moon2.model = glm::translate(moon2.model, glm::vec3(0.0, -1.0, 0.0));
		moon3.model = glm::translate(moon3.model, glm::vec3(0.0, -1.0, 0.0));
		moon4.model = glm::translate(moon4.model, glm::vec3(0.0, -1.0, 0.0));
		break;


	case 'p':  //Rotation des Schiefen Planeten 
		
			Planetschief.model = Planetschief.model*glm::rotate(glm::mat4(1.0f), glm::radians(-5.0f), glm::vec3(1, 0, 0));
		 	initWireSpheremoon4(program.getHandle(), &moon4, Planetschief);
		 	initWireSpheremoon5(program.getHandle(), &moon5, Planetschief);
		 	initWireSpheremoon6(program.getHandle(), &moon6, Planetschief);
			initWireSpheremoon7(program.getHandle(), &moon7, Planetschief);
		 	initWireSpheremoon8(program.getHandle(), &moon8, Planetschief);

			break;
		 	//bug: nach drehung geht der Planet bei T oder t immer in 45° gekippte X achse des Planeten 
	 	case 'P': //Rotation des Schiefen Planeten 
	 		Planetschief.model = Planetschief.model*glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(1, 0, 0));
	 		initWireSpheremoon4(program.getHandle(), &moon4, Planetschief);
	 		initWireSpheremoon5(program.getHandle(), &moon5, Planetschief);
	 		initWireSpheremoon6(program.getHandle(), &moon6, Planetschief);
	 		initWireSpheremoon7(program.getHandle(), &moon7, Planetschief);
	 		initWireSpheremoon8(program.getHandle(), &moon8, Planetschief);

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

	renderAxis(view, projection, program, Y_AxisSun);
	renderAxis(view, projection, program, Y_AxisMoon);
	renderAxis(view, projection, program, Y_AxisMoonSlope);

	renderWireSphereSonne(view, projection, program, Sonne);
	renderWireSpherePlanetschief(view, projection, program, Planetschief);
	renderWireSpherePlanetgrade(view, projection, program, PlanetGrade);

	renderWireSpheremoon1(view, projection, program, moon1);
	renderWireSpheremoon2(view, projection, program, moon2);
	renderWireSpheremoon3(view, projection, program, moon3);
	renderWireSpheremoon4(view, projection, program, moon4);

	renderWireSpheremoon5(view, projection, program, moon5);
	renderWireSpheremoon6(view, projection, program, moon6);
	renderWireSpheremoon7(view, projection, program, moon7);
	renderWireSpheremoon8(view, projection, program, moon8);
}

void glutDisplay()
{
	GLCODE(render());
	glutSwapBuffers();
	rotate();
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
	glutCreateWindow(WINDOW_TITLE_PREFIX);  // Fenster erstellen: "Praktikum Komputergrafik: Aufgabeblatt 3"
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

					// Räumen bei Beendigung alles auf.
	release();

	return 0;	// Erfolg, oder ->exit(EXIT_SUCCESS);
}