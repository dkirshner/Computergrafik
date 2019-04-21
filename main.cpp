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

// Standard window width
const int WINDOW_WIDTH  = 640;
// Standard window height
const int WINDOW_HEIGHT = 480;
// GLUT window id/handle
int glutID = 0;

cg::GLSLProgram program;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar  = 100.0f;

/*
Struct to hold data for object rendering.
*/
class Object
{
public:
  inline Object ()
    : vao(0),
      positionBuffer(0),
      colorBuffer(0),
      indexBuffer(0)
  {}

  inline ~Object () { // GL context must exist on destruction
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteBuffers(1, &positionBuffer);
  }

  GLuint vao;        // vertex-array-object ID
  
  GLuint positionBuffer; // ID of vertex-buffer: position
  GLuint colorBuffer;    // ID of vertex-buffer: color
  
  GLuint indexBuffer;    // ID of index-buffer
  
  glm::mat4x4 model; // model matrix
};


Object quad;


void renderQuad()
{
  // Create mvp.
  glm::mat4x4 mvp = projection * view * quad.model;
  
  // Bind the shader program and set uniform(s).
  program.use();
  program.setUniform("mvp", mvp);
  
  // Bind vertex array object so we can render the 2 triangles.
  glBindVertexArray(quad.vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
  glBindVertexArray(0);
}

void initQuad(float RotAnteil, float GruenAnteil, float BlauAnteil)
{
  // Construct triangle. These vectors can go out of scope after we have send all data to the graphics card.
  const std::vector<glm::vec3> vertices = { { -1.0f, 1.0f, 0.0f }, { -1.0, -1.0, 0.0 }, { 1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } };
  const std::vector<glm::vec3> colors   = { {RotAnteil, GruenAnteil, BlauAnteil}, {RotAnteil, GruenAnteil, BlauAnteil }, { RotAnteil, GruenAnteil, BlauAnteil }, { RotAnteil, GruenAnteil, BlauAnteil } };
  const std::vector<GLushort>  indices  = { 0, 1, 2, 0, 2, 3 };

  GLuint programId = program.getHandle();
  GLuint pos;
  
  // Step 0: Create vertex array object.
  glGenVertexArrays(1, &quad.vao);
  glBindVertexArray(quad.vao);
  
  // Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
  glGenBuffers(1, &quad.positionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, quad.positionBuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
  
  // Bind it to position.
  pos = glGetAttribLocation(programId, "position");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);
  
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
  
  // Modify model matrix.
  quad.model = glm::translate(glm::mat4(1.0f), glm::vec3(1.25f, 0.0f, 0.0f));
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init(float r, float g, float b)
{
  // OpenGL: Set "background" color and enable depth testing.
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  
  // Construct view matrix.
  glm::vec3 eye(0.0f, 0.0f, 4.0f);
  glm::vec3 center(0.0f, 0.0f, 0.0f);
  glm::vec3 up(0.0f, 1.0f, 0.0f);
  
  view = glm::lookAt(eye, center, up);
  
  // Create a shader program and set light direction.
  if (!program.compileShaderFromFile("shader/simple.vert", cg::GLSLShader::VERTEX)) {
    std::cerr << program.log();
    return false;
  }
  
  if (!program.compileShaderFromFile("shader/simple.frag", cg::GLSLShader::FRAGMENT)) {
    std::cerr << program.log();
    return false;
  }
  
  if (!program.link()) {
    std::cerr << program.log();
    return false;
  }

  // Create all objects.
  initQuad(r,g,b);
  
  return true;
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderQuad();
}

void glutDisplay ()
{
   render();
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
  switch (keycode) {
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
  
  glutCreateWindow("Aufgabenblatt 01");
  glutID = glutGetWindow();
  
  // GLEW: Load opengl extensions
  //glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    return -1;
  }
#if _DEBUG
  if (glDebugMessageCallback) {
    std::cout << "Register OpenGL debug callback " << std::endl;
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(cg::glErrorVerboseCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE,
			  GL_DONT_CARE,
			  GL_DONT_CARE,
			  0,
			  nullptr,
			  true); // get all debug messages
  } else {
    std::cout << "glDebugMessageCallback not available" << std::endl;
  }
#endif

  // GLUT: Set callbacks for events.
  glutReshapeFunc(glutResize);
  glutDisplayFunc(glutDisplay);
  //glutIdleFunc   (glutDisplay); // redisplay when idle
  
  glutKeyboardFunc(glutKeyboard);
  
  // init vertex-array-objects.

  float r = 1.0f;
  float g = 0.0f;
  float b = 0.0f;

  float c = 1.0f-r;
  float m = 1.0f-g;
  float y = 1.0f-b;

  int h = 1;
  float s = 0.0f;
  float v = 0.0f;
  //Eingabefunktion

  std::cout << "Bitte Farbmodell waehlen: (RGB, CMY, HSV) \n";
  std::string eingabe = "";
 
  bool farb = true;
  int farbwert = 0;

  while (farbwert==0) {
	  std::cin >> eingabe;
	  if (eingabe == "RGB" || eingabe == "rgb") {
		 farbwert = 1;
	  }
	  else if (eingabe == "CMY" || eingabe == "cmy") {
		 farbwert = 2;
	  }
	  else if(eingabe =="HSV"||eingabe == "hsv"){  
		farbwert = 3;
	  }
	  else {
		  std::cout << "Falsche eingabe, RGB/CMY/HSV\n";
	  }
  }
  while (farb) {
	  switch (farbwert) {
	  case 1://RGB
		 std::cout << "Bitte geben sie den Wert fuer Rot an: (Werteberreich 0-255)";
		while (!(std::cin >> r)) {
			std::cout << "Falsche Eingabe (Werteberreich 0-255)" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n'); 
		 }
		 std::cout << "Bitte geben sie den Wert fuer Gruen an: (Werteberreich 0-255)";
		 while (!(std::cin >> g)) {
			 std::cout << "Falsche Eingabe (Werteberreich 0-255)" << std::endl;
			 std::cin.clear();
			 std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		 }
		 std::cout << "Bitte geben sie den Wert fuer Blau an: (Werteberreich 0-255)";
		 while (!(std::cin >> b)) {
			 std::cout << "Falsche Eingabe (Werteberreich 0-255)" << std::endl;
			 std::cin.clear();
			 std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		 }
		
		 if (r < 0 || r > 255) {
		  std::cout << "\nEingabe nur 0-255.\n\n";
		 }
		 else if (g < 0 || g > 255) {
		  std::cout << "\nEingabe nur 0-255.\n\n";
		 }
		 else if (b < 0 || b > 255) {
		  std::cout << "\nEingabe nur 0-255.\n\n";
		 }
		 else {
		  farb = false;
		 }

		 //C=1.0−R M=1.0−G Y=1.0−B  RGB -> CMY

		 c = 255 - r;
		 m = 255 - g;
		 y = 255 - b;
		  
		 //RGB -> HSV
		 float MAX, MIN;
		 
		 //finde das MAX der RGB Werte
		 if (r >= b&&r >= g) {
			  MAX = r;
		 }
		 else if (b > r&& b > g) {
		  MAX = b;
		 }
		 else if (g>r&&g>b) {
			  MAX = g;
		 }
		 //Finde das MIN der RGB Werte
		 if (r >= b && r >= b) {
			  MIN = b;
		 }
		 else if (b >= r&& b >= r) {
			  MIN = r;
		 }
		 else if (b >= g && r >= g) {
			  MIN = g;
		 }
		  //Definiere Hue/farbwert
		 if (r == g && r == b) {
			  h = 0;
		 }
		 else if(MAX==r){
			  h = 60 * ((g - b) /( MAX - MIN));
		 }
		 else if (MAX == g) {
			  h = 60 * (2 + (b - r) / (MAX - MIN));
		 }
		 else if (MAX = b) {
			  h = 60 * (4 + (r - g) / (MAX - MIN));
		 }
		 while (h < 0) {
			  h = h + 360;
		 }

		  //Definiere Satturation/Sättigung
		 if (MAX == 0) {
			  s = 0;
		 }
		 else {
			  s = (MAX - MIN) / MAX;
		 }

		  //Definiere Value/Helligkeit
		  v = MAX/255;
		  break;

	  case 2://CMY
		  std::cout << "Bitte geben sie den Wert fuer Cyan an: (Werteberreich 0-255)\n";
		  while (!(std::cin >> c)) {
			  std::cout << "Falsche Eingabe (Werteberreich 0-255)" << std::endl;
			  std::cin.clear();
			  std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		  }
		  std::cout << "Bitte geben sie den Wert fuer Magenta an: (Werteberreich 0-255)\n";
		  while (!(std::cin >> m)) {
			  std::cout << "Falsche Eingabe (Werteberreich 0-255)" << std::endl;
			  std::cin.clear();
			  std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		  }
		  std::cout << "Bitte geben sie den Wert fuer Gelb an: (Werteberreich 0-255)\n";
		  while (!(std::cin >> y)) {
			  std::cout << "Falsche Eingabe (Werteberreich 0-255)" << std::endl;
			  std::cin.clear();
			  std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		  }

		  if (c < 0 || c > 255) {
			  std::cout << "\nEingabe nur 0-255.\n\n";
		  }
		  else if (m < 0 || m > 255) {
			  std::cout << "\nEingabe nur 0-255.\n\n";
		  }
		  else if (y < 0 || y > 255) {
			  std::cout << "\nEingabe nur 0-255.\n\n";
		  }
		  else {
			  farb = false;
		  }

		  //R=1.0−C	G=1.0−M B=1.0−Y  CMY -> RGB
		  r = 255 - c;
		  g = 255 - m;
		  b = 255 - y;

		  //RGB -> HSV
		  //finde das MAX der RGB Werte
		  if (r >= b && r >= g) {
			  MAX = r;
		  }
		  else if (b > r&& b > g) {
			  MAX = b;
		  }
		  else if (g>r&&g>b) {
			  MAX = g;
		  }
		  //Finde das MIN der RGB Werte
		  if (r >= b && r >= b) {
			  MIN = b;
		  }
		  else if (b >= r && b >= r) {
			  MIN = r;
		  }
		  else if (b >= g && r >= g) {
			  MIN = g;
		  }
		  //Definiere Hue/farbwert
		  if (r == g && r == b) {
			  h = 0;
		  }
		  else if (MAX == r) {
			  h = 60 * ((g - b) / (MAX - MIN));
		  }
		  else if (MAX == g) {
			  h = 60 * (2 + (b - r) / (MAX - MIN));
		  }
		  else if (MAX = b) {
			  h = 60 * (4 + (r - g) / (MAX - MIN));
		  }
		  while (h < 0) {
			  h = h + 360;
		  }

		  //Definiere Satturation/Sättigung
		  if (MAX == 0) {
			  s = 0;
		  }
		  else {
			  s = (MAX - MIN) / MAX;
		  }

		  //Definiere Value/Helligkeit
		  v = MAX/255;

		  break;

	  case 3://HSV
		  std::cout << "Bitte geben sie den Wert fuer Hue an: (Werteberreich 0-359)\n";
		  while (!(std::cin >> h)) {
			  std::cout << "Falsche Eingabe (Werteberreich 0-359)" << std::endl;
			  std::cin.clear();
			  std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		  }
		  std::cout << "Bitte geben sie den Wert fuer Satturation an: (Werteberreich 0-100)\n";
		  while (!(std::cin >> s)) {
			  std::cout << "Falsche Eingabe (Werteberreich 0-100)" << std::endl;
			  std::cin.clear();
			  std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		  }
		  std::cout << "Bitte geben sie den Wert fuer Value an: (Werteberreich 0-100)\n";
		  while (!(std::cin >> v)) {
			  std::cout << "Falsche Eingabe (Werteberreich 0-100)" << std::endl;
			  std::cin.clear();
			  std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		  }

		  if (h < 0 || h > 359) {
			  std::cout << "\nEingabe Hue nur 0-359.\n\n";
		  }
		  else if (s < 0 || s > 100) {
			  std::cout << "\nEingabe nur 0-100.\n\n";
		  }
		  else if (v < 0 || v > 100) {
			  std::cout << "\nEingabe nur 0-100.\n\n";
		  }
		  else {
			  farb = false;
		  }
		  s = s / 100;
		  v = v / 100;

		
		  //HSV -> RGB
		  float a, x, n, mod;
		  a = v * s;
		  mod = ((h / 60) % 2) - 1;
		  if (mod < 0) {
			  mod = mod * (-1);
		  }
		  x = a * (1 - mod);
		  n = v - a;

		  if (h >= 0 && h < 60) {
			  r = a;
			  g = x;
			  b = 0;
		  }
		  else if (h >= 60 && h < 120) {
			  r = x;
			  g = a;
			  b = 0;
		  }
		  else if (h >= 120 && h < 180) {
			  r = 0;
			  g = a;
			  b = x;
		  }
		  else if (h >= 180 && h < 240) {
			  r = 0;
			  g = x;
			  b = a;
		  }
		  else if (h >= 240 && h < 300) {
			  r = x;
			  g = 0;
			  b = a;
		  }
		  else if (h >= 300 && h < 360) {
			  r = a;
			  g = 0;
			  b = x;
		  }
		  r = (r + n) * 255;
		  g = (g + n) * 255;
		  b = (b + n) * 255;
		
		  //RGB -> CMY
		  c = 255 - r;
		  m = 255 - g;
		  y = 255 - b;

		  break;

	  default://Fehler
		  std::cout << "Fehler im Programm, abbruch.";
		  farb = false;
		  break;

	  }

  }

  std::cout << "\nRGB:\nRot: ";
  std::cout << r;
  std::cout << "\nGruen: ";
  std::cout << g;
  std::cout << "\nBlau: ";
  std::cout << b;
  std::cout << "\nCMY:\nCyan: ";
  std::cout << c;
  std::cout << "\nMagenta: ";
  std::cout << m;
  std::cout << "\nYellow: ";
  std::cout << y;
  std::cout << "\nHSV:\nHue ";
  std::cout << h;
  std::cout << "\nSatturation: ";
  std::cout << s;
  std::cout << "\nValue: ";
  std::cout << v;
  std::cout << "\n\n\n\nNachfolgendes Standard Ausgabe";



  r = r / 255;
  g = g / 255;
  b = b / 255;
 
  bool result = init(r,g,b);   
  if (!result) {
    return -2;
  }

  // GLUT: Loop until the user closes the window
  // rendering & event handling
  glutMainLoop ();
  
  // Cleanup in destructors:
  // Objects will be released in ~Object
  // Shader program will be released in ~GLSLProgram
  
  return 0;
}
