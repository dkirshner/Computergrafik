#include <iostream>
			//#include <vector>
#include <stdlib.h>     /* atof */
#include <ctype.h>		/*isalpha*/

#include <GL/glew.h>
//#include <GL/gl.h> // OpenGL header not necessary, included by GLEW
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GLSLProgram.h"	// shader program
#include "GLTools.h"

#define WINDOW_TITLE_PREFIX "Aufgabenblatt 01"
using namespace std;

// Standard window width (current dimensions of the window!)
const int WINDOW_WIDTH  = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle (window handle created by FreeGLUT)
int glutID = 0; 

cg::GLSLProgram program;	// shader program
glm::mat4x4 view;			// GLM Type: 4 * 4 matrix of double-precision floating-point numbers
glm::mat4x4 projection;		

float zNear = 0.1f;
float zFar  = 100.0f;

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

			// Object triangle;
Object quad;
// Funktions-Prototypen:
void renderQuad();

//überprüfung Eingabe auf gültigkeit
bool secureInput(const string a_strUserInput, float * a_ptrVal, bool a_bIsHue = false)
{
	char buffer[256];
	bool bIsDigit = true;
	int i = 0;
	float fMinVal = 0.0, fMaxVal = 0.0;

	if (a_bIsHue == false)
	{
		fMinVal = 0.0;
		fMaxVal = 1.0;
	}
	else
	{
		fMinVal = 0.0;
		fMaxVal = 360.0;
	}

	do
	{
		fflush(stdin);	// Tastatupuffer freigeben!
		int i = 0;		// re-init
		cout << a_strUserInput;
		cin >> buffer;

		while (buffer[i])
		{
			if (isdigit(buffer[i]) || (buffer[i] == '.'))// isdigit() ->überprüfung Eingabe auf Zahlen von 0 bis 9
			{
				bIsDigit = true;
				i++;
			}
			else
			{
				bIsDigit = false;
				break;
			}
		}

		if (bIsDigit)
			*a_ptrVal = (float)atof(buffer);

	} while (!bIsDigit || ((*a_ptrVal) < fMinVal || (*a_ptrVal) > fMaxVal));

	return true;
}

bool secureInputHue(const string a_strUserInput, float * a_ptrVal)
{
	char buffer[256];
	bool bIsDigit = true;
	int i = 0;

	do
	{
		fflush(stdin);	// Tastatupuffer freigeben!
		int i = 0;		// re-init
		cout << a_strUserInput;
		cin >> buffer;

		while (buffer[i])
		{
			if (isdigit(buffer[i]) || (buffer[i] == '.'))
			{
				bIsDigit = true;
				i++;
			}
			else
			{
				bIsDigit = false;
				break;
			}
		}

		if (bIsDigit)
			*a_ptrVal = (float)atof(buffer);

	} while (!bIsDigit || ((*a_ptrVal) < 0.0 || (*a_ptrVal) > 360.0));

	return true;
}
			
void renderQuad()
{
	// Cumulating transformations -> Create mvp: the ModelViewProjection matrix!
	glm::mat4x4 mvp = projection * view * quad.model;

	// Bind the shader program and set uniform(s).
	program.use();
	program.setUniform("mvp", mvp);
	
	// Bind vertex array object so we can render the 2 triangles.
	glBindVertexArray(quad.vao); //Vertex Array Object
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}
			
void initQuad(float a_iColorOptionA, float a_iColorOptionB, float a_iColorOptionC)
{
	// Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
	const std::vector<glm::vec3> vertices = { { -1.0f, 1.0f, 0.0f },{ -1.0, -1.0, 0.0 },{ 1.0f, -1.0f, 0.0f },{ 1.0f, 1.0f, 0.0f } };
	const std::vector<glm::vec3> colors = { { a_iColorOptionA, a_iColorOptionB, a_iColorOptionC },{ a_iColorOptionA, a_iColorOptionB, a_iColorOptionC },{ a_iColorOptionA, a_iColorOptionB, a_iColorOptionC },{ a_iColorOptionA, a_iColorOptionB, a_iColorOptionC } };
	const std::vector<GLushort> indices = { 0, 1, 2, 0, 2, 3 };

	GLuint programId = program.getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &quad.vao);	
	glBindVertexArray(quad.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &quad.positionBuffer);				// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glBindBuffer(GL_ARRAY_BUFFER, quad.positionBuffer); // The following commands will talk about our 'vertexbuffer' buffer
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	/*Vertex-Attribute können durch die glVertexAttribPointer-Funktion und ihre beiden Schwesterfunktionen glVertexAttribIPointer und glVertexAttribLPointer beschrieben werden.*/
	glVertexAttribPointer(pos,		// attribute 0. No particular reason for 0, but must match the layout in the shader.
						  3,		// size
			              GL_FLOAT,	// type
						  GL_FALSE, // normalized?
						  0,		// stride (Forschritt)
						  0);		// array buffer offset

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &quad.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &quad.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

	// !!!! Modify model matrix (Änderung des Position des Objekt im Fenster) !!!!
	quad.model = glm::translate(glm::mat4(1.0f), glm::vec3(1.65f, 0.7f, 0.0f));
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init(float r, float g, float b)
{
	/*Vier Parameter, die (in Reihenfolge) die Farbkanäle Rot, Grün, Blau und Alpha darstellen.*/
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	// Construct view matrix.
	glm::vec3 eye(0.0f, 0.0f, 4.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(eye, center, up);

	if (!program.compileShaderFromFile("shader/simple.vert", cg::GLSLShader::VERTEX))
	{
		std::cerr << program.log();
		return false;
	}

	/*Für unseren ersten Fragment-Shader machen wir etwas ganz einfaches:
	 Setzen Sie die Farbe jedes Fragments auf eine Farbe, z.B. Rot.
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

	// Create objects.
				//initTriangle();
	initQuad(r, g, b);

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
				//releaseObject(triangle);
	releaseObject(quad);
}

/*
 Rendering (Zeichnen).
 */
void render()
{
	/*
	OpenGL-Funktionsaufruf, der bestimmte durch seine Parameter festgelegte Puffer reinigt.
	Dies bedeutet, dass vor der Wiederverwendung des Puffers alle Pixel im Puffer
	auf einen bestimmten Wert gesetzt werden.
	Der Back-Puffer wird beispielsweise mit dem RGB-Farbwert gelöscht,
	der zuvor in der Funktion Initialisieren von glClearColor angegeben wurde.

	Der Back-Puffer wird gelöscht mit dem Flag GL_COLOR_BUFFER_BIT
	Neben dem Back-Buffer löschen wir auch den Tiefenpuffer, indem wir das GL_DEPTH_BUFFER_BIT-Flag. */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//renderTriangle();
	renderQuad();
}

/*
Display callback.
Wo das Zeichnen (Rendern) von Objekten und das Austauschen der hinteren und vorderen Puffer erfolgt.
*/
void glutDisplay ()
{
   GLCODE(render());	// Aufruf von Funktion render() -> "ZEICHNE"!
   glutSwapBuffers();

   glutPostRedisplay();
}

/*
 Resize callback.

 Bei jeder Größenänderung des Fensters wird eine neue Fenstergröße definiert und 
 an die Anwendung übergeben. Wir erfassen diese neuen Werte in "glutResize" und
 speichern die Werte in "width" und "height".
 */
void glutResize (int width, int height)
{
	// Division by zero is bad...
	height = height < 1 ? 1 : height;
	/*Ein Ansichtsfenster definiert den von OpenGL gezeichneten Bereich. 
	Ein Punkt, der außerhalb des Ansichtsfensters liegt, wird nicht gezeichnet.
	Der Grund, warum dieses Bildfenster als Ansichtsfenster bezeichnet wird,
	liegt darin, dass es ein Fenster in die Szene ist und nur einen kleinen Bereich
	einer möglicherweise viel größeren Szene. 
	Dies kann sich beispielsweise als nützlich erweisen, wenn Sie OpenGL-Grafiken
	in eine Benutzeroberfläche integrieren möchten.*/
	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}


bool RecolorQuad(void)
{
	string temp = "";
	int identifier = 0;
	float r, g, b;
	bool ende = true;
 
	cout << "\n\n\n ------------Start der Farbaenderung--------------------" << endl;
	cout << "Zur Farbaenderung des Vierecks bitte dieses Ausgabefenster anklicken!" << endl;
	cout << "Faerben Sie ein Viereck ein, entsprechend von Ihnen eingegebenen Werten!" << endl;
	cout << "Bitte geben Sie ein folgendes Modell ein: \"RGB\", \"CMY\" oder \"HSV\"" << endl;
	cout << "1. (r, g, b) RGB, mit r, g, b im Intervall [0, 1] oder" << endl;
	cout << "2. (c, m, y) CMY, mit c, m, y im Intervall [0, 1] oder" << endl;
	cout << "3. (h, s, v) HSV, mit s, v im Intervall [0, 1], h im Intervall[0, 360]" << endl;
	cout << "Bitte Ihre Eingabe(RGB, CMY, HSV?):" << endl;

	fflush(stdin);	// Tastatupuffer freigeben!
	cin >> temp;

	while (ende)
	{
		if (temp == "RGB" || temp == "rgb")
		{
			identifier = 1;
			ende = false;
		}
		else if (temp == "CMY" || temp == "cmy")
		{
			identifier = 2;
			ende = false;
		}
		else if (temp == "HSV" || temp == "hsv")
		{
			identifier = 3;
			ende = false;
		}
		else
		{
			cout << "Bitte geben Sie entweder RGB oder CMY oder HSV ein!" << endl;
			fflush(stdin);	// Tastatupuffer freigeben!
			cin >> temp;
		}			
	}

	ende = true;	// Wiederherstellen

	while (ende)
	{
		switch (identifier)
		{
		case 1:	
			secureInput("Rot eingeben\n", &r);
			secureInput("Gruen eingeben\n", &g);
			secureInput("Blau eingeben\n", &b);

			ende = false;
			break;
		case 2:
			secureInput("Cyan eingeben\n", &r);
			secureInput("Magenta eingeben\n", &g);
			secureInput("Yellow eingeben\n", &b);

			r = 1 - (r );
			g = 1 - (g );
			b = 1 - (b );
			ende = false;
			break;
		case 3:
			float H, S, V;
			secureInput("Hue eingeben\n", &H, true);
			secureInput("Saturation eingeben\n", &S);
			secureInput("Value eingeben\n", &V);

			if (S == 0)
			{
				r = V;
				g = V;
				b = V;
			}
			else
			{
				int i;
				float f, p, q, t;

				if (H == 360)
					H = 0;
				else
					H = H / 60;

				i = (int)trunc(H);
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
			ende = false;
			break;

		default:
			cout << "Das war kein passendes System";
			break;
		}
	}
	cout << "\n\n\n****** Start der Ausgabe vom Schaeder-Program (und Lichtrichtung)! ********" << endl;
	/* Init VAO (Vertex Array Object)->create and use Vertex Buffer Objects (VBO)
	   Ein Vertex Array Object (oder VAO) ist ein Objekt, 
	   das beschreibt, wie die Vertex-Attribute in einem Vertex Buffer Objects Vertex-Puffer-Objekt (VBO) gespeichert werden.
	   Dies bedeutet, dass der VAO nicht das eigentliche Objekt ist, das die Vertexdaten speichert, 
	   sondern der Deskriptor der Vertexdaten.
	*/
	{
		GLCODE(bool result = init(r, g, b));

		if (!result)
		{
			release();
			cout << "FEHLER bie Init VAO!";
		}
	}

	cout << "****** Ende der Ausgabe vom Schaeder-Programm!********" << endl;
	cout << "\n\n\n----------------- Ende der Farbaenderung-----------------" << endl;
	cout << "\n#1. Im Fall, wenn Sie erneut die Farbaenderung vornehmen moechten:" << endl;
	cout << "       1. Das Fenster mit dem Ueberschrift \"Aufgabe 01\" einklicken" << endl;
	cout << "       2. Die Taste \"1\" betaetigen;" << endl;
	cout << "\n#2. Im Fall, wenn Sie das Programm beenden moechten:" << endl;
	cout << "       1. Das Fenster mit dem Ueberschrift \"Aufgabe 01\" einklicken" << endl;
	cout << "       2. Die Taste \"Esc\" betaetigen;" << endl;

	fflush(stdin);	// Tastatupuffer freigeben!
	return 0;
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
	  
	case '+':
		// do something
		break;
	case '-':
		// do something
		break;
	case 'x':
		// do something
		break;
	case 'y':
		// do something
		break;
	case 'z':
		// do something
		break;
	case '1':
		RecolorQuad(); // Aufgabe 1.2: Färben Sie ein Viereck ein nach vom Benutzer eingegebenen Werten
		break;
	default:
		// do something
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
				///  START cratewindow: 
	// GLUT: Initialize the FreeGLUT library (window toolkit)
	glutInit(&argc, argv); // FreeGLUT benötigt mehrere Parameter (siehe main(...)) für das Programm-Kontolle...
	/*This function does not return anything, but simply sets up FreeGLUT for use in your application.
	  In any program, this should be the first FreeGLUT function you should call!*/

    glutInitWindowSize    (WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(750, 0);

	/*FreeGLUT mitteilen, welche Art von OpenGL-Kontext wir für unser Programm verwenden möchten:*/
	glutInitContextVersion(4, 3);	// GLUT: Create a window and opengl context (version 4.3 core profile).
	/*Wenn in der Befehlszeile OpenGL 4.0 nicht angezeigt wird, ist 
	  bei der Erstellung des Kontexts ein Fehler aufgetreten,
	  oder Ihr Treiber hat Ihre Anforderung nach einem OpenGL 4.0-Kontext nicht erfüllt!*/
	glutInitContextProfile(GLUT_CORE_PROFILE);
	/*Wir bitten FreeGLUT, einen vorwärtskompatiblen OpenGL 4.3-Kernprofilkontext zurückzugeben.*/
	glutInitContextFlags  (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	
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
	glutCreateWindow(WINDOW_TITLE_PREFIX);  //. Fenster erstellen: "Aufgabenblatt 01"
	glutID = glutGetWindow();				// glutID->window handle created by FreeGLUT
	  
	if (glutID < 1)
	{
		fprintf( stderr, "ERROR: Could not create a new rendering window.\n");
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
		fprintf(stderr,	"ERROR: %s\n",	glewGetErrorString(GlewInitResult));

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
	glutKeyboardFunc(glutKeyboard);		//	Tastatureingabe wird als CALLBAC vearbeitet!

	RecolorQuad();	// Aufgabe 1.2: Färben Sie ein Viereck ein nach vom Benutzer eingegebenen Werten

	// GLUT: Loop until the user closes the window
	
	glutMainLoop ();	// rendering & event handling
	
	release();	// Clean up everything on termination.

	return 0;	// success, oder ->exit(EXIT_SUCCESS);
}

