#include "header.h"

//R�ndert Dreick f�r Darstellung 
// Parameter [in] a_triangle: enth�llt alle Informationen zum Objekt
void renderTriangle(Object a_triangle)
{
	// Cumulating transformations -> Create mvp: the ModelViewProjection matrix!
	glm::mat4x4 mvp = projection * view * a_triangle.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);

	// Bind vertex array object so we can render the 1 triangle.
	glBindVertexArray(a_triangle.vao);	 //Vertex Array Object
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0); // glDrawElements (GLenum mode, GLsizei count, GLenum type, const void *indices); KI
	glBindVertexArray(0);
}

// initialisiert Objekt "Triangle"
// Parameter [in, out]	a_vertices: alle Punkte von Dreieck 
// Parameter[in]		a_colors:	alle farben des Dreiecks
// Parameter [in]		a_triangle: enth�llt alle Informationen zum Objekt
void initTriangle(const std::vector<glm::vec3> a_vertices, const std::vector<glm::vec3> a_colors, Object& a_triangle)
{
	// Construct triangle.
	const std::vector<GLushort> indices = { 0, 1, 2 };

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &a_triangle.vao);
	glBindVertexArray(a_triangle.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &a_triangle.positionBuffer);				// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glBindBuffer(GL_ARRAY_BUFFER, a_triangle.positionBuffer);	// The following commands will talk about our 'vertexbuffer' buffer
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, a_vertices.size() * sizeof(glm::vec3), a_vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	/*Vertex-Attribute k�nnen durch die glVertexAttribPointer-Funktion und ihre beiden Schwesterfunktionen 
	glVertexAttribIPointer und glVertexAttribLPointer beschrieben werden.*/
	glVertexAttribPointer( pos,			// attribute 0. No particular reason for 0, but must match the layout in the shader.
							3,			// size
							GL_FLOAT,	// type
							GL_FALSE,	// normalized?
							0,			// stride (Forschritt)
							0);			// array buffer offset

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &a_triangle.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, a_triangle.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, a_colors.size() * sizeof(glm::vec3), a_colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &a_triangle.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a_triangle.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// !!! Modify model matrix (�nderung des Position des Objekt im Fenster) !!!
	// a_triangle.model = glm::translate(glm::mat4(1.0f), glm::vec3(1.65f, 0.7f, 0.0f));
}

//initialisierung ALLER Dreiecke aus denen der Kreis besteht
//return-Wert: true bei Erfolg, sonst false
bool initAllTriangles(void)
{
	float dAngleIRad = ((float)M_PI*2.0f)/iCountTriangle; // Bogenmass in Radian
	//Ermittlung des 3.ten Punktes des ersten Rechtecks (Richtung: gegen Uhrzeiger-Sinn)
	//Wertberechnung nur f�r das erste Dreieck
	double dX = cos(dAngleIRad)*dRadiusApproxCircle; //�nderung der Koordinaten vom dritten Punkt der Koordinatenachse X mit Ber�cksichtigung der Radius�nderung
	double dY = sin(dAngleIRad)*dRadiusApproxCircle; //�nderung der Koordinaten vom dritten Punkt der Koordinatenachse Y mit Ber�cksichtigung der Radius�nderung
	const std::vector<glm::vec3> vertices = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(dRadiusApproxCircle, 0.0f, 0.0f), glm::vec3(dX, dY, 0.0f) };	// init: erstes Dreieck
	std::vector<glm::vec3> colors;		// init

	if (!Triangle.empty())
		Triangle.clear();

	if (iTaskNr == 1)	//Aufruf Aufgabenteil 1
	{
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);		// !!! Hintergrund- gr�n

		colors = { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) };	// !!! Farbe gelb f�r Dreieckk
		//colors = { glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) };		// !!! blau  
	}
	else if (iTaskNr == 2)
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);		// !!! Aufruf Aufgabenteil 2 NUR F�R HSV: Hintergrund: wei�

	const int ANZ_SECTORS = 12;

	for (int iCount = 0; iCount < iCountTriangle; iCount++)//schleife �ber alle Dreiecke
	{
		Object triangle;
		Triangle.push_back(triangle);

		if (iTaskNr == 2)	//Aufruf Aufgabenteil 2 NUR F�R HSV
		{
			float r, g, b;
			// Ver�nderungswerte f�r HSV!
			float H = (float)(iCount * 12);			// 0�-> 360�
			const float S = 1.0; //iCount/ 30.0F;	// 0->1.0
			const float V = 1.0F;					// const 1.0

			// START: Umrechnung HSV in RGB um die colors in die Funktion "initTriangle(...) zu �bergeben"
			{
				int i;
				float f, p, q, t;

				if (H == 360)
					H = 0;
				else
					H = H / 60;

				i = (int)trunc(H);	// Rounds x toward zero, returning the nearest integral value that is not larger in magnitude than x
				f = H - i;

				p = (float)(V * (1.0 - S));
				q = (float)(V * (1.0 - (S * f)));
				t = (float)(V * (1.0 - (S * (1.0 - f))));

				switch (i)
				{
					case 0:
						r = V;
						g = t;
						b = p;
						break;

					case 1:
						r = q;
						g = V;
						b = p;
						break;

					case 2:
						r = p;
						g = V;
						b = t;
						break;

					case 3:
						r = p;
						g = q;
						b = V;
						break;

					case 4:
						r = t;
						g = p;
						b = V;
						break;

					default:
						r = V;
						g = p;
						b = q;
						break;
				}
			}
			// END: Umrechnung HSV in RGB um die colors in die Funktion "initTriangle(...) zu �bergeben"
 
			colors = { { r, g, b },{ r, g, b },{ r, g, b } };  // HSV-Abstufungen in RGB umgewandelt!!!			
		}
			initTriangle(vertices, colors, Triangle.at(iCount));
			// Modify model matrix: Dreieckeun Nullpunkt rotieren!!!
			// Struktur => glm::rotate(Model, angle_in_radians, glm::vec3(x, y, z)); 
			Triangle.at(iCount).model = glm::rotate(glm::mat4(1.0f), (iCount*dAngleIRad), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	return true;
}
//macht aus den Dreiecken einen Kreis
void renderCircle()
{
	initAllTriangles();

	for (unsigned int i = 0; i < Triangle.size(); i++)
		renderTriangle(Triangle.at(i));
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{
	// !!! OpenGL: Set "background" color and enable depth testing. !!!

	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);		// !!! gr�n

	// Construct view matrix.
	glm::vec3 eye(0.0f, 0.0f, 4.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(eye, center, up);
	/*Im Kontext von OpenGL (auch Direct3D) ist ein Shader ein Programm, das auf der Grafikhardware ausgef�hrt wird.
	OpenGL dr�ckt ein Shader-Programm �ber eine C-�hnliche Programmiersprache aus,
	die als OpenGL Shading Language oder GLSL bezeichnet wird.
	Im folgenden Code haben wir bereits zwei GLSL-Programme erstellt, eines f�r die Verarbeitung pro Vertex
	und eines f�r die Verarbeitung pro Fragment:
	Ein Vertex-Shader arbeitet auf Per-Vertex-Basis und �ndert die �bergebenen Attribute des Vertex.
	Ein Fragment-Shader bearbeitet ein Per-Fragment und �ndert die */

	/*n der einfachsten m�glichen Konfiguration ben�tigen Sie zwei Shader:
	1. einen mit dem Namen "Vertex Shader", der f�r jeden Scheitelpunkt ausgef�hrt wird
	2. einen mit "Fragment Shader", der f�r jedes Sample(Fragmente) ausgef�hrt wird.

	Und da wir 4x Antialising verwenden, haben wir 4 Samples(Fragmente) in jedem Pixel.

	Shader werden in einer Sprache namens GLSL: GL Shader Language programmiert, die Teil von OpenGL ist.
	Wenn Sie Ihre Anwendung starten, alle Ihre Shader neu kompiliert werden.*/

	// Create a shader program and set light direction.
	/*The first line tells the compiler that we will use OpenGL 3�s syntax:
	#version 330 core
	The second line declares the input data :

	layout(location = 0) in vec3 vertexPosition_modelspace;

	->"vec3" ist ein Vektor von 3 Komponenten in GLSL: eEs ist �hnlich (aber anders) zu glm :: vec3
	->�Layout (location = 0)� bezieht sich auf den Puffer, den wir verwenden,
	um das "vertexPosition_modelspace-Attribut" einzugeben.
	Jeder Scheitelpunkt kann zahlreiche Attribute haben: Eine Position, eine oder mehrere Farben,
	eine oder mehrere Texturkoordinaten, viele andere Dinge. OpenGL wei� nicht,
	was eine Farbe ist: Sie sieht nur ein vec3. Wir m�ssen ihm also sagen,
	welcher Puffer welcher Eingabe entspricht.
	Wir tun dies, indem wir das Layout auf den gleichen Wert wie den ersten Parameter
	f�r glVertexAttribPointer setzen. Der Wert "0" ist nicht wichtig, es k�nnte 12 sein
	(aber nicht mehr als glGetIntegerv (GL_MAX_VERTEX_ATTRIBS, & v)).
	->"VertexPosition_modelspace" k�nnte einen anderen Namen haben. Sie enth�lt die Position des Scheitelpunkts
	f�r jeden Lauf des Scheitelpunkt-Shakers.
	->"in" bedeutet, dass dies einige Eingangsdaten sind. Bald sehen wir das Schl�sselwort "out"

	Unsere Hauptfunktion setzt lediglich die Position des Scheitelpunkts auf den Inhalt des Puffers.
	Wenn wir also (1,1) gaben, w�rde das Dreieck einen seiner Scheitelpunkte in der rechten oberen Ecke
	des Bildschirms haben:

	gl_Position.xyz = vertexPosition_modelspace;
	gl_Position.w = 1.0;
	Siehe http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
	*/

	//F�r unseren ersten Vertex-Shader:
	// Create a shader program and set light direction.
	if (!program.compileShaderFromFile("shader/simple.vert", cg::GLSLShader::VERTEX))
	{
		std::cerr << program.log();
		return false;
	}

	/*F�r unseren ersten Fragment-Shader:
	(Denken Sie daran, es gibt 4 Fragmente in einem Pixel, da wir 4x AA verwenden.)*/
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

	// Create objects:
	initAllTriangles();	//Initialisierung Dreiecke f�r den Kreis

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
	for (unsigned int i = 0; i < Triangle.size(); i++)
	{
		releaseObject(Triangle.at(i));
	}
}

/*
 Rendering.
 */
void render()
{
	/*
	OpenGL-Funktionsaufruf, der bestimmte durch seine Parameter festgelegte Puffer reinigt.
	Dies bedeutet, dass vor der Wiederverwendung des Puffers alle Pixel im Puffer
	auf einen bestimmten Wert gesetzt werden.
	Der Back-Puffer wird beispielsweise mit dem RGB-Farbwert gel�scht,
	der zuvor in der Funktion Initialisieren von glClearColor angegeben wurde.

	Der Back-Puffer wird gel�scht mit dem Flag GL_COLOR_BUFFER_BIT
	Neben dem Back-Buffer l�schen wir auch den Tiefenpuffer, indem wir das GL_DEPTH_BUFFER_BIT-Flag. */

	glClear(GL_COLOR_BUFFER_BIT);
	renderCircle();
}

/*
Display callback.
Wo das Zeichnen (Rendern) von Objekten und das Austauschen der hinteren und vorderen Puffer erfolgt.
*/
void glutDisplay ()
{
   GLCODE(render());
   glutSwapBuffers();
}

/*
Resize callback.

Bei jeder Gr��en�nderung des Fensters wird eine neue Fenstergr��e definiert und
an die Anwendung �bergeben. Wir erfassen diese neuen Werte in "glutResize" und
speichern die Werte in "width" und "height".
*/
void glutResize (int width, int height)
{
	// Division by zero is bad...
	height = height < 1 ? 1 : height;

	/*Ein Ansichtsfenster definiert den von OpenGL gezeichneten Bereich.
	Ein Punkt, der au�erhalb des Ansichtsfensters liegt, wird nicht gezeichnet.
	Der Grund, warum dieses Bildfenster als Ansichtsfenster bezeichnet wird,
	liegt darin, dass es ein Fenster in die Szene ist und nur einen kleinen Bereich
	einer m�glicherweise viel gr��eren Szene.
	Dies kann sich beispielsweise als n�tzlich erweisen, wenn Sie OpenGL-Grafiken
	in eine Benutzeroberfl�che integrieren m�chten.*/

	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}

/*
 Callback for char input.
 */
//Tastatureingaben
void glutKeyboard (unsigned char keycode, int x, int y)
{
	switch (keycode)
	{
	case 27: // ESC
	  glutDestroyWindow ( glutID );
	  return;
	  
	case '+':
		// Anzahl der Dreiecke der Kreis-Approximation vergr��ern
		if(iCountTriangle < MAX_COUNT_TRIANGLE)
			iCountTriangle++;
		break;
	case '-':
		// Anzahl der Dreiecke der Kreis-Approximation verkleinern
		if (iCountTriangle > MIN_COUNT_TRIANGLE)
			iCountTriangle--;
		break;
	case 'q':
		//  Radius vergr��ern
		if (dRadiusApproxCircle < 2)
			dRadiusApproxCircle += 0.5;
		break;
	case 'w':
		// Radius verkleinern
		if (dRadiusApproxCircle > 1.0)
			dRadiusApproxCircle -= 0.5;
		break;
	case '1':
		// Aufgabenteil 1 zeigen
		if (iTaskNr == 2)
			iTaskNr = 1;
		glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
		break;
	case '2':
		//  Aufgabenteil 2 zeigen
		if (iTaskNr == 1)
			iTaskNr = 2;
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	
	///  START cratewindow: 
	// GLUT: Initialize the FreeGLUT library (window toolkit)
	glutInit(&argc, argv); // FreeGLUT ben�tigt mehrere Parameter (siehe main(...)) f�r das Programm-Kontolle...
						   /*This function does not return anything, but simply sets up FreeGLUT for use in your application.
						   In any program, this should be the first FreeGLUT function you should call!*/

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(750, 0);

	/*FreeGLUT mitteilen, welche Art von OpenGL-Kontext wir f�r unser Programm verwenden m�chten:*/
	glutInitContextVersion(4, 3);	// GLUT: Create a window and opengl context (version 4.3 core profile).
									/*Wenn in der Befehlszeile OpenGL 4.0 nicht angezeigt wird, ist
									bei der Erstellung des Kontexts ein Fehler aufgetreten,
									oder Ihr Treiber hat Ihre Anforderung nach einem OpenGL 4.0-Kontext nicht erf�llt!*/
	glutInitContextProfile(GLUT_CORE_PROFILE);
	/*Wir bitten FreeGLUT, einen vorw�rtskompatiblen OpenGL 4.3-Kernprofilkontext zur�ckzugeben.*/
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);

	/*Welche Art von OpenGL-Kontext wir w�nschen und wie das Ger�t unsere Szene rendern soll:
	Parameter:
	GLUT_RGB, GLUT_RGBA   : ist ein Flag, das die Art und Weise definiert,
		wie Farben unter Verwendung einzelner Rot-, Gr�n-, Blau- und Alpha-Werte zusammengesetzt werden.
	GLUT_DEPTH : erm�glicht die Verwendung des Tiefenpuffers, einem wichtigen Mechanismus in der 3D - Computergrafik.
		Der Tiefenpuffer(auch Z - Puffer genannt) enth�lt die Flie�komma - Z - Tiefeninformation
		jedes auf dem Bildschirm gerenderten Pixels.
		Dieser Mechanismus ist wichtig beim Rendern neuer Objekte, um sicherzustellen,
		dass sie keine Objekte �berlappen, die sich n�her am Bildschirm befinden
		(und somit auch bestimmt wird, ob das neue Pixel das vorhandene Pixel �berschreiben soll).
	GLUT_DOUBLE: Verwendung von Doppelpufferung erm�glicht, eine Funktion, die das Bildflimmern reduziert.
		Bei Doppelpufferung werden alle Zeichenbefehle in einem Puffer au�erhalb des Bildschirms ausgef�hrt,
		der an den Bildschirm gesendet wird, wenn alle Zeichnungen f�r einen Rahmen abgeschlossen sind,
		sodass keine unvollst�ndigen Bilder angezeigt werden.
		Der aktuell angezeigte Puffer wird als vorderer Puffer bezeichnet, und der Puffer, in den wir ziehen,
		wird als (Sie ahnen Sie es) Back-Puffer bezeichnet. Wenn alle Zeichenbefehle abgeschlossen sind,
		werden diese Puffer ausgetauscht, so dass der hintere Puffer zum vorderen Puffer wird und umgekehrt.
	*/
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	/*Sicherstellen, dass die glutMainLoop-Funktion in main zum Programm zur�ckkehrt
	und das Programm nicht beendet, wenn es fertig ist.

	Die urspr�ngliche GLUT-Bibliothek kehrte nicht zum Programm zur�ck.
	Nachdem das Rendern von GLUT abgeschlossen war, wurde das Programm beendet.
	Dies bedeutete, dass wenn Sie Speicher zugewiesen hatten, es keine M�glichkeit gab,
	Speicherlecks zu vermeiden, wenn Sie nicht in die GLUT-Bibliothek gehackt wurden.
	glutSetOption(
	GLUT_ACTION_ON_WINDOW_CLOSE,
	GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);*/

	/*Fenster und damit unseren Rendering-Kontext erstellen*/
	glutCreateWindow(WINDOW_TITLE_PREFIX);  //. Fenster erstellen: "Aufgabenblatt 02"
	glutID = glutGetWindow();				// glutID->window handle created by FreeGLUT

	if (glutID < 1)
	{
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	// GLEW: Load opengl extensions
	glewExperimental = GL_TRUE;

	// Um OpenGL 4.0-Funktionen unterst�tzen zu k�nnen, ben�tigt unser Programm Hilfe von der GLEW-Bibliothek!!!
	GLenum GlewInitResult = glewInit();	// Adding GLEW (Werkzeuge!)

	if (GlewInitResult != GLEW_OK)
	{
		/*Wenn dies nicht der Fall ist, schreiben wir eine Fehlernachricht in die Befehlszeile und
		beenden das Programm. Die Fehlernachricht enth�lt den tats�chlichen Fehler,
		der von GLEW durch den Funktionsaufruf "glewGetErrorString" zur�ckgegeben wird.*/
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));

		exit(EXIT_FAILURE);
	}

	// GLUT: Set CALLBACS (R�ckruffunktionen: glutResize, glutDisplay) for events:
	glutReshapeFunc(glutResize);	// Ver�ndern der Fenstergr��e: Funktion zum Umformen wird jedes Mal aufgerufen, wenn die Gr��e des Fensters ge�ndert wird
	glutDisplayFunc(glutDisplay);	// Rendern der Szene: Anzeigefunktion wird jedes Mal aufgerufen, wenn die Szene auf den Bildschirm gezeichnet wird.
									//glutIdleFunc   (glutDisplay); 

									/*Da wir zu diesem Zeitpunkt einen OpenGL-Kontext haben, ist es sicher, OpenGL-Funktionen aufzurufen.
									Als erstes rufen wir glGetString mit GL_VERSION als Parameter auf,
									um die erstellte Version des OpenGL-Kontexts abzurufen.*/
	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));
	///  END create window

	/// ********* Kontext ist g�ltig und wir sind zum Zeichnen bereit! ********

	// GLUT: Set CALLBAC (R�ckruffunktion: glutKeyboardFunc) for keyboard-events:
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
	/*das Herz der Anwendung. Diese Funktion wird ausgef�hrt, solange das Fenster aktiv ist und
	das Fenster nicht geschlossen wurde.
	Daraufhin werden Zeichenbefehle ausgegeben und Fensteroperationen ausgef�hrt.*/
	glutMainLoop ();	// rendering & event handling

	// Clean up everything on termination.
	release();

	return 0;	// success, oder ->exit(EXIT_SUCCESS);
}

/*
https://stackoverflow.com/questions/24017636/gldrawelements-only-draws-first-triangle-specified-by-indices
 // rotate, translate usw...
https://glm.g-truc.net/0.9.2/api/a00245.html

http://www.falloutsoftware.com/tutorials/gl/gl3.htm
http://www-home.htwg-konstanz.de/~bittel/ain_robo/Vorlesung/02_PositionUndOrientierung.pdf
https://www.studocu.com/en/document/universitaet-siegen/computergraphik-i/summaries/computergrafik-zusammenfassung/1478628/view
*/