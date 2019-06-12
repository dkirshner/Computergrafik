#include "Render.h"

// it needs to be defined somewhere
//extern  vector<GLushort> indicesSphere;
array< vector<GLushort>, 11> indicesSphereArr; // indicesSphereArr[0].push_back( 1 );
 //extern  vector<glm::vec3> colorsSphere;
array<vector<glm::vec3>, 11> colorsSphereArr; // indicesSphereArr[0].push_back( 1 );
//extern  vector<glm::vec3> verticesSphere;
array<vector<glm::vec3>, 11> verticesSphereArr; // indicesSphereArr[0].push_back( 1 );
// Aktueller Vektor wo alle Kugelteile gespeichert werden aus denen der Kugel entsteht
array<vector<Object>, 11> SpherePiesesArr;

cg::GLSLProgram program;

GraphicObject AxisSun, AxisPlanetSlope, AxisPlanetStraight;

 GLfloat rotateZ = 45.0f;

void renderSphere(glm::mat4x4 view, glm::mat4x4 projection, cg::GLSLProgram program, Object a_Sphere)
{
	const int iId = a_Sphere.iID;

	/*if (iId == 1)
	{
		SpherePiesesArr[1].at(0).model = glm::rotate(SpherePiesesArr[1].at(0).model, glm::radians((rotateZ)), glm::vec3(0.0f, 0.0f, 1.0f));		//	rotierem um 45° erste Hälfte gegen Uhrzeigersinn
		SpherePiesesArr[1].at(1).model = glm::rotate(SpherePiesesArr[1].at(1).model, glm::radians((rotateZ)), glm::vec3(0.0f, 0.0f, 1.0f));		//	rotierem um 45° zweite Hälfte gegen Uhrzeigersinn
	}*/

	// ransformationen kumulieren -> MVP erstellen: Die ModelViewProjection-Matrix!!
	glm::mat4x4 mvp = projection * view * a_Sphere.model;

	// inde das Shader-Programm und setze Uniform (en)
	program.use();
	program.setUniform("mvp", mvp);

	// Binden das Vertex-Array-Objekt, damit wir das Dreieck rendern können.
	glBindVertexArray(a_Sphere.vao);	 //Vertex Array Object

	int iSizeOfTriangles = (int)indicesSphereArr[iId].size(); // init

	// Minimale und Maximale Anzahl der Dreiecke definieren!
	if (iSizeOfTriangles < 24)
	{
		cout << "FEHLER renderSphere(): Anzahl Dreiecke ist unter 24!" << iSizeOfTriangles;
		iSizeOfTriangles = 24;
	}
	else if (iSizeOfTriangles > 200)
	{
		cout << "FEHLER renderSphere(): Anzahl Dreiecke ist höher 200!" << iSizeOfTriangles;
		iSizeOfTriangles = 24;
	}

	glDrawElements(GL_TRIANGLES, iSizeOfTriangles, GL_UNSIGNED_SHORT, 0); // Dreiecke (Anzahl: iSizeOfTriangles) als die Bestandsteile der Kugel verwenden
	glBindVertexArray(0);
}


// Stellt ein Koordinatensystem dar: Zeichne Achse für die Sonne
void renderAxisSun(glm::mat4x4 a_view, glm::mat4x4 a_projection, cg::GLSLProgram a_program)
{
	// Create mvp.
	glm::mat4x4 mvp = a_projection * a_view * AxisSun.model;

	// Das Shader-Programm einbinden und stellen Sie die Uniform (en) ein.
	a_program.use();
	a_program.setUniform("mvp", mvp);

	//  Das Vertex-Array-Objekt einbinden, damit wir die beiden Dreiecke rendern können.
	AxisSun.renderObject(6); // in Klammern: 6 - anzahl Vertisies
}

// Initialisiere Achse für den geneigten Planeten
void renderAxisPlanetSlope(glm::mat4x4 a_view, glm::mat4x4 a_projection, cg::GLSLProgram a_program)
{
	// Create mvp.
	glm::mat4x4 mvp = a_projection * a_view * AxisPlanetSlope.model;

	// Das Shader-Programm einbinden und stellen Sie die Uniform (en) ein.
	a_program.use();
	a_program.setUniform("mvp", mvp);

	//AxisPlanetSlope.model = glm::rotate(AxisPlanetSlope.model, glm::radians(rotateZ), glm::vec3(0.0, 0.0, 1.0));

	//  Das Vertex-Array-Objekt einbinden, damit wir die beiden Dreiecke rendern können.
	AxisPlanetSlope.renderObject(6); // in Klammern: 6 - anzahl Vertisies
}

// Initialisiere Achse für den geraden Planeten
void renderAxisPlanetStraight(glm::mat4x4 a_view, glm::mat4x4 a_projection, cg::GLSLProgram a_program)
{
	// Create mvp.
	glm::mat4x4 mvp = a_projection * a_view * AxisPlanetStraight.model;

	// Das Shader-Programm einbinden und stellen Sie die Uniform (en) ein.
	a_program.use();
	a_program.setUniform("mvp", mvp);

	//  Das Vertex-Array-Objekt einbinden, damit wir die beiden Dreiecke rendern können.
	AxisPlanetStraight.renderObject(6); // in Klammern: 6 - anzahl Vertisies
}