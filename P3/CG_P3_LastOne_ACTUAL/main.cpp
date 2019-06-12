#include "Header.h"

void renderSphere(Object a_cirle)
{
	// ransformationen kumulieren -> MVP erstellen: Die ModelViewProjection-Matrix!!
	glm::mat4x4 mvp = projection * view * a_cirle.model;

	// inde das Shader-Programm und setze Uniform (en)
	program.use();
	program.setUniform("mvp", mvp);

	// Binden das Vertex-Array-Objekt, damit wir das Dreieck rendern können.
    glBindVertexArray(a_cirle.vao);	 //Vertex Array Object

	int iSizeOfTriangles = (int)indicesSphere.size(); // init

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

void initSphere()
{
	GLuint programId = program.getHandle();
	GLuint pos;

	// Schritt 0: Ein Vertex-Array-Objekt erstellen
	glGenVertexArrays(1, &Sphere.vao);
	glBindVertexArray(Sphere.vao);

	// Schritt 1: Ein Vertex-Pufferobjekt für das Positionsattribut erstellen und binden Sie es an das zugehörige "Shader-Attribut".
	glGenBuffers(1, &Sphere.positionBuffer);				// Generieren Sie 1 Puffer und geben Sie den resultierenden Bezeichner in den Vertexbuffer ein
	glBindBuffer(GL_ARRAY_BUFFER, Sphere.positionBuffer);	// Die folgenden Befehle sprechen über unseren 'Vertexbuffer'-Puffer
															// Geben Sie unsere Eckpunkte an OpenGL.
	glBufferData(GL_ARRAY_BUFFER, verticesSphere.size() * sizeof(glm::vec3), verticesSphere.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	/*Vertex-Attribute können durch die glVertexAttribPointer-Funktion und ihre beiden Schwesterfunktionen glVertexAttribIPointer und glVertexAttribLPointer beschrieben werden.*/
	glVertexAttribPointer(pos,			// attribute 0. Kein besonderer Grund für 0, muss aber mit dem Layout im Shader übereinstimmen.
						  3,			// size
						  GL_FLOAT,		// type
						  GL_FALSE,		// normalized?
						  0,			// stride (Forschritt)
						  0);			// array buffer offset

	// Schritt 2: Ein Vertex-Pufferobjekt für das Farbattribut erstellen und anbinden ...
	glGenBuffers(1, &Sphere.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Sphere.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colorsSphere.size() * sizeof(glm::vec3), colorsSphere.data(), GL_STATIC_DRAW);

	// Binde es an die Farbe.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Schritt 3: Vertex-Pufferobjekt für Indizes erstellen. Hier ist keine Bindung erforderlich.
	glGenBuffers(1, &Sphere.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Sphere.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSphere.size() * sizeof(GLushort), indicesSphere.data(), GL_STATIC_DRAW);

	// Löse die Bindung des Vertex - Array - Objekts(zurück zur Standardeinstellung).
	glBindVertexArray(0);
	// INIT: Transformation der Kugel
	Sphere.model = glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));
}

// Stellt ein Koordinatensystem dar
// Zeichne Achse X
void renderXAxis()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * XAxis.model;

	// Das Shader-Programm einbinden und stellen Sie die Uniform (en) ein.
	program.use();
	program.setUniform("mvp", mvp);

	//  Das Vertex-Array-Objekt einbinden, damit wir die beiden Dreiecke rendern können.
	XAxis.renderObject(6);
}
// Zeichne Achse Y
void renderYAxis()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * YAxis.model;

	// Das Shader-Programm einbinden und stellen Sie die Uniform (en) ein.
	program.use();
	program.setUniform("mvp", mvp);

	//  Das Vertex-Array-Objekt einbinden, damit wir die beiden Dreiecke rendern können.
	YAxis.renderObject(6);
}
// Zeichne Achse Z
void renderZAxis()
{
	// Create mvp.
	glm::mat4x4 mvp = projection * view * ZAxis.model;

	// Das Shader-Programm einbinden und stellen Sie die Uniform (en) ein.
	program.use();
	program.setUniform("mvp", mvp);

	//  Das Vertex-Array-Objekt einbinden, damit wir die beiden Dreiecke rendern können.
	ZAxis.renderObject(6);
}

// Initialisiere Achse X
void initXAxis()
{
	// Dreieck konstruieren. Diese Vektoren können den Gültigkeitsbereich verlassen, nachdem wir alle Daten an die Grafikkarte gesendet haben.
	const vector<glm::vec3> vertices = { { -3.0f, 0.0f, 0.0f }, { 3.0f, 0.0f, 0.0f } };
	// Farbe
	const vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const vector<GLushort> indices = {1,0};

	GLuint programId = program.getHandle();
	XAxis.initObject(vertices, colors, indices, programId);
}

// Initialisiere Achse Y
void initYAxis()
{
	// Dreieck konstruieren. Diese Vektoren können den Gültigkeitsbereich verlassen, nachdem wir alle Daten an die Grafikkarte gesendet haben.
	const vector<glm::vec3> vertices = { { 0.0f, 3.0f, 0.0f },{ 0.0f, -3.0f, 0.0f } };
	//Farbe
	const vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const vector<GLushort> indices = { 1,0};

	GLuint programId = program.getHandle();

	YAxis.initObject(vertices, colors, indices, programId);
}

// Initialisiere Achse Z
void initZAxis()
{
	// Dreieck konstruieren. Diese Vektoren können den Gültigkeitsbereich verlassen, nachdem wir alle Daten an die Grafikkarte gesendet haben.
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
	// OpenGL: Die Hintergrundfarbe einstellen und die Tiefenprüfung aktivieren.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	initView();//Fkt f Perspektive + Kamerawanderung

	// Ein Vertex-Shaderprogramm erstellen und die Lichtrichtung festlegen.
	if (!program.compileShaderFromFile("shader/simple.vert", cg::GLSLShader::VERTEX))
	{
		cerr << program.log();
		return false;
	}

	// Ein Fragment-Shaderprogramm erstellen und die Lichtrichtung festlegen.
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

	// "WIRE-FRAME" Modus aktivieren
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Objekt Kugel initialisieren
	initSphere();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Bei Bedarf Anzeigemodus mit Flächen zurücksetzen!

	// Achsen X, Y. Z initialisieren:
	initXAxis();
	initYAxis();
	initZAxis();

	return true;
}

/*
Objektressourcen freigeben.
*/
void releaseObject(Object& obj)
{
	glDeleteVertexArrays(1, &obj.vao);
	glDeleteBuffers(1, &obj.indexBuffer);
	glDeleteBuffers(1, &obj.colorBuffer);
	glDeleteBuffers(1, &obj.positionBuffer);
}

/*

Ressourcen bei Beendigung freigeben.
*/
void release()
{
	// Das Shader-Programm wird nach Beendigung des Programms freigegeben
	releaseObject(Sphere);
	XAxis.deleteObject();
	YAxis.deleteObject();
	ZAxis.deleteObject();
}

/*

Rendern
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(iSubdivision >= 2)
	{
		for (unsigned int i = 0; i < SpherePieses.size(); i++)
			renderSphere(SpherePieses.at(i));
	}
	else
		renderSphere(Sphere);

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
 CALLBACK-Funktion bei Veränderung dr Größe des Fensters
 */
void glutResize (int width, int height)
{
	// Division durch Null ist nicht zulässig...
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	// Projektionsmatrix erstellen
	projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}

// Ist schon ein Punkt in einer aktuellen Liste enthalten
bool IsVertexSaved(glm::vec3 a_Pnt, int *a_Index)
{
	for (int i = 0; i < verticesSphere.size(); i++)
	{
		double dVert_X = ceilf(verticesSphere.at(i).x * 1000) / 1000;
		double dVert_Y = ceilf(verticesSphere.at(i).y * 1000) / 1000;
		double dVert_Z = ceilf(verticesSphere.at(i).z * 1000) / 1000;

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

// clear actual data
bool ClearActualData(void)
{
	if (verticesSphere.size())
		verticesSphere.clear();

	if (indicesSphere.size())
		indicesSphere.clear();

	if (colorsSphere.size())
		colorsSphere.clear();

	if (SpherePieses.size())
		SpherePieses.clear();

	return true;
}

// Werte von n=0 bis n= 3 sichern bei "+" und
// Werte von n = 0 bis n = 3 von gespeicherten Daten holen (keine 2-te Berechnung!) bei "-" 
bool CacheSphereData(void)
{
	if (verticesSphere.size() && indicesSphere.size() && colorsSphere.size())
	{
		if (iPrevSubdivision < iSubdivision)	// "+"
		{
			if (iSubdivision == 1)
			{
				if (verticesSphere_0.size() == 0 && indicesSphere_0.size() == 0 && colorsSphere_0.size() == 0)
				{
					for (int i = 0; i < verticesSphere.size(); i++)
						verticesSphere_0.push_back(verticesSphere[i]);

					for (int i = 0; i < indicesSphere.size(); i++)
						indicesSphere_0.push_back(indicesSphere[i]);

					for (int i = 0; i < colorsSphere.size(); i++)
						colorsSphere_0.push_back(colorsSphere[i]);
				}
			}
			else if (iSubdivision == 2)
			{
				if (verticesSphere_1.size() == 0 && indicesSphere_1.size() == 0 && colorsSphere_1.size() == 0)
				{
					for (int i = 0; i < verticesSphere.size(); i++)
						verticesSphere_1.push_back(verticesSphere[i]);

					for (int i = 0; i < indicesSphere.size(); i++)
						indicesSphere_1.push_back(indicesSphere[i]);

					for (int i = 0; i < colorsSphere.size(); i++)
						colorsSphere_1.push_back(colorsSphere[i]);
				}
			}
			else if (iSubdivision == 3)
			{
				if (verticesSphere_2.size() == 0 && indicesSphere_2.size() == 0 && colorsSphere_2.size() == 0 && SpherePieses_2.size() == 0)
				{
					for (int i = 0; i < verticesSphere.size(); i++)
						verticesSphere_2.push_back(verticesSphere[i]);

					for (int i = 0; i < indicesSphere.size(); i++)
						indicesSphere_2.push_back(indicesSphere[i]);

					for (int i = 0; i < colorsSphere.size(); i++)
						colorsSphere_2.push_back(colorsSphere[i]);

					if (SpherePieses.size() > 0)	// Vektor wo alle Kugelteile gespeichert werden aus denen der Kugel entsteht)
					{
						for (int i = 0; i < SpherePieses.size(); i++)
							SpherePieses_2.push_back(SpherePieses.at(i));
					}
				}
			}
		}
		else // "-"
		{			
			ClearActualData();	// Aktuelle Daten löschen

			if (iPrevSubdivision == 1)
			{
				for (int i = 0; i < verticesSphere_0.size(); i++)
					verticesSphere.push_back(verticesSphere_0.at(i));

				for (int i = 0; i < indicesSphere_0.size(); i++)
					indicesSphere.push_back(indicesSphere_0.at(i));

				for (int i = 0; i < colorsSphere_0.size(); i++)
					colorsSphere.push_back(colorsSphere_0.at(i));
			}
			else if (iPrevSubdivision == 2)
			{
				for (int i = 0; i < verticesSphere_1.size(); i++)
					verticesSphere.push_back(verticesSphere_1.at(i));

				for (int i = 0; i < indicesSphere_1.size(); i++)
					indicesSphere.push_back(indicesSphere_1.at(i));

				for (int i = 0; i < colorsSphere_1.size(); i++)
					colorsSphere.push_back(colorsSphere_1.at(i));
			}
			else if (iPrevSubdivision == 3)
			{
				for (int i = 0; i < verticesSphere_2.size(); i++)
					verticesSphere.push_back(verticesSphere_2.at(i));

				for (int i = 0; i < indicesSphere_2.size(); i++)
					indicesSphere.push_back(indicesSphere_2.at(i));

				for (int i = 0; i < colorsSphere_2.size(); i++)
					colorsSphere.push_back(colorsSphere_2.at(i));

				if (SpherePieses_2.size() > 0)	// Vektor wo alle Kugelteile gespeichert werden aus denen der Kugel entsteht)
				{
					for (int i = 0; i < SpherePieses_2.size(); i++)
					{
						SpherePieses.push_back(SpherePieses_2.at(i));
					}
				}
			}
			else  if (iPrevSubdivision == 4)
			{
				for (int i = 0; i < verticesSphere_3.size(); i++)
					verticesSphere.push_back(verticesSphere_3.at(i));

				for (int i = 0; i < indicesSphere_3.size(); i++)
					indicesSphere.push_back(indicesSphere_3.at(i));

				for (int i = 0; i < colorsSphere_3.size(); i++)
					colorsSphere.push_back(colorsSphere_3.at(i));

				if (SpherePieses_3.size() > 0)	// Vektor wo alle Kugelteile gespeichert werden aus denen der Kugel entsteht
				{
					for (int i = 0; i < SpherePieses_3.size(); i++)
					{
						SpherePieses.push_back(SpherePieses_3.at(i));
					}
				}
			}

			initSphere();
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Mittelpunkt von 2 Eckpunkten finden
// HINWEIS: Die Größe des neuen Scheitelpunkts muss geändert werden, damit die Länge dem Radius entspricht
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
	if (iSubdivision > 3)
		return false;

	// Start CACHE: Werte von n=0 bis n= 3 sichern bei "+" und
	// Werte von n = 0 bis n = 3 von gespeicherten Daten holen (keine 2-te Berechnung!) bei "-" 
	if (CacheSphereData())
		return true;

	vector<glm::vec3>tmpColors;
	vector<glm::vec3>tmpVertices;
	vector<GLushort> tmpIndices;  

	glm::vec3 newV1, newV2, newV3; // new vertex positions
	unsigned int index;

	// copy prev vertex/index arrays and clear

	for (int i = 0; i < verticesSphere.size(); i++)
		tmpVertices.push_back(verticesSphere[i]);

	for (int i = 0; i < indicesSphere.size(); i++)
		tmpIndices.push_back(indicesSphere[i]);

	for (int i = 0; i < colorsSphere.size(); i++)
		tmpColors.push_back(colorsSphere[i]);

	ClearActualData();	// Aktuelle Daten löschen

	index = 0;
	bool bNoBreak = true;

	// perform subdivision for each triangle
	for (int j = 0; j < tmpIndices.size() && bNoBreak; j += 3)
	{
		// get 3 vertices of a triangle
		glm::vec3 v1 = tmpVertices[tmpIndices[j]];
		glm::vec3 v2 = tmpVertices[tmpIndices[j + 1]];
		glm::vec3 v3 = tmpVertices[tmpIndices[j + 2]];

		//  3 neue Eckpunkte berechnen, indem die Hälfte an jeder Kante geteilt wird
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
			verticesSphere.push_back(v1);		// #0
			iIndex_0 = (int)verticesSphere.size() - 1;
		}

		if (IsVertexSaved(v2, &iIndex_1) == false)
		{
			verticesSphere.push_back(v2);		// #1
			iIndex_1 = (int)verticesSphere.size() - 1;
		}

		if (IsVertexSaved(v3, &iIndex_2) == false)
		{
			verticesSphere.push_back(v3);		// #2
			iIndex_2 = (int)verticesSphere.size() - 1;
		}

		if (IsVertexSaved(newV1, &iIndex_3) == false)
		{
			verticesSphere.push_back(newV1);	// #3
			iIndex_3 = (int)verticesSphere.size() - 1;
		}

		if (IsVertexSaved(newV2, &iIndex_4) == false)
		{
			verticesSphere.push_back(newV2);	// #4
			iIndex_4 = (int)verticesSphere.size() - 1;
		}

		if (IsVertexSaved(newV3, &iIndex_5) == false)
		{
			verticesSphere.push_back(newV3);	// #6
			iIndex_5 = (int)verticesSphere.size() - 1;
		}

		// Vektoren normalisieren!
		for (int i = 0; i < verticesSphere.size(); i++)
		{
			verticesSphere[i] *= 1.0f / sqrt(verticesSphere[i].x * verticesSphere[i].x + verticesSphere[i].y * verticesSphere[i].y + verticesSphere[i].z * verticesSphere[i].z);
		}

		////////////////  indices   ////////////////

		indicesSphere.push_back(GLushort(iIndex_0));
		indicesSphere.push_back(GLushort(iIndex_3));
		indicesSphere.push_back(GLushort(iIndex_5));

		indicesSphere.push_back(GLushort(iIndex_3));
		indicesSphere.push_back(GLushort(iIndex_1));
		indicesSphere.push_back(GLushort(iIndex_4));

		indicesSphere.push_back(GLushort(iIndex_3));
		indicesSphere.push_back(GLushort(iIndex_4));
		indicesSphere.push_back(GLushort(iIndex_5));

		indicesSphere.push_back(GLushort(iIndex_5));
		indicesSphere.push_back(GLushort(iIndex_4));
		indicesSphere.push_back(GLushort(iIndex_2));

		//////////////   colors   //////////////////////////

		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
		colorsSphere.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

		index += 6;

		if (index == 96)
		{
			initSphere();
			SpherePieses.push_back(Sphere);
			bNoBreak = false;
		}
	}

	if (iSubdivision == 2)
	{
		initSphere();
		// Bogenmass in Radian: Umrechnung von Grad in Bogenmaß
		// degree = radian * 180/π
		// radian = degree * π/180

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Sphere.model = glm::rotate(glm::mat4(1.0f), ((float)M_PI), glm::vec3(0.0f, 0.0f, 1.0f)) *
				        glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		SpherePieses.push_back(Sphere);
	}
	else if (iSubdivision == 3)
	{
		// Körper oben #2
		initSphere();
		// Bogenmass in Radian: Umrechnung von Grad in Bogenmaß
		// degree =v radian * 180/π
		// radian = degree * π/180
		float dAngle = (float)(M_PI) / (-2.0);

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Sphere.model =	glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		SpherePieses.push_back(Sphere);

		// Körper oben #3
		initSphere();

		dAngle = (float)(M_PI) / 2.0;

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Sphere.model =	glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
				        glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		SpherePieses.push_back(Sphere);

		// Körper oben #4
		initSphere();
		dAngle = (float)(M_PI);

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Sphere.model =	glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		SpherePieses.push_back(Sphere);

		// Körper unten #1
		initSphere();
		dAngle = (float)(M_PI);

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Sphere.model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 0.0f, 1.0f)) *
					   glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		SpherePieses.push_back(Sphere);

		// Körper unten #2
		initSphere();
		dAngle = (float)(M_PI) /2.0;
		float dAngle_2 = (float)(M_PI);

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Sphere.model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
					   glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(1.0f, 0.0f, 0.0f)) *
					   glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		SpherePieses.push_back(Sphere);

		// Körper unten #3
		initSphere();
		dAngle = (float)(M_PI) / 2.0;
		dAngle_2 = (float)(M_PI);

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Sphere.model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
			           glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(1.0f, 0.0f, 0.0f)) *
					   glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(0.0f, 1.0f, 0.0f)) *
			           glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		SpherePieses.push_back(Sphere);

		// Körper unten #3
		initSphere();
		dAngle = (float)(M_PI) / 2.0;
		dAngle_2 = (float)(M_PI)*(-1.0);
		float dAngle_3 = (float)(M_PI) / 2.0;

		// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
		Sphere.model =	glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(1.0f, 0.0f, 0.0f)) *
						glm::rotate(glm::mat4(1.0f), dAngle_3, glm::vec3(0.0f, 1.0f, 0.0f)) *
						glm::scale(glm::mat4(1.0f), glm::vec3(dRadius, dRadius, dRadius));

		SpherePieses.push_back(Sphere);

		if (verticesSphere_3.size() == 0 && indicesSphere_3.size() == 0 && colorsSphere_3.size() == 0)
		{
			for (int i = 0; i < verticesSphere.size(); i++)
				verticesSphere_3.push_back(verticesSphere.at(i));

			for (int i = 0; i < indicesSphere.size(); i++)
				indicesSphere_3.push_back(indicesSphere.at(i));

			for (int i = 0; i < colorsSphere.size(); i++)
				colorsSphere_3.push_back(colorsSphere.at(i));
		}

		// Casche Teile der Kugel für den n= 3 
		if (SpherePieses.size() > 0 && SpherePieses_3.size() == 0)	// Vektor wo alle Kugelteile gespeichert werden aus denen der Kugel entsteht)
		{
			for (int i = 0; i < SpherePieses.size(); i++)
				SpherePieses_3.push_back(SpherePieses.at(i));
		}
	}
 
	if (iSubdivision != 3)
		initSphere();

	if (tmpVertices.size())
		tmpVertices.clear();

	if (tmpIndices.size())
		tmpIndices.clear();

	if (tmpColors.size())
		tmpColors.clear();

	return 0;
}

/*
Rückruf-Funktion für die Zeicheneingabe per Tastatur.
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

				if (iSubdivision >= 2)
				{
					for (unsigned int i = 0; i < SpherePieses.size(); i++)
						SpherePieses.at(i).model = SpherePieses.at(i).model * glm::mat4x4{ { 0.9, 0,0,0 },{ 0,0.9,0,0 },{ 0,0,0.9,0 },{ 0,0,0,1 } };
				}
				else
					Sphere.model = Sphere.model * glm::mat4x4{ {0.9, 0,0,0}, {0,0.9,0,0}, {0,0,0.9,0}, {0,0,0,1}};
			}
 
			break;

		case 'R':
			if (dRadius < 2.0) {
				dRadius += 0.1;
			
				if (iSubdivision >= 2)
				{
					for (unsigned int i = 0; i < SpherePieses.size(); i++)
						SpherePieses.at(i).model = SpherePieses.at(i).model * glm::mat4x4{ { 1.1, 0,0,0 },{ 0,1.1,0,0 },{ 0,0,1.1,0 },{ 0,0,0,1 } };
				}
				else
					Sphere.model = Sphere.model * glm::mat4x4{ { 1.1, 0,0,0 },{ 0,1.1,0,0 },{ 0,0,1.1,0 },{ 0,0,0,1 } };
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

		/*case 'q':
			if (Z_VIEW < 0) {
				Z_VIEW += 0.2;
				Y_VIEW += 0.2;
				X_VIEW += 0.2;
			}
			initView();
			break;

		case 'w':
			if (Z_VIEW > -5) {
				Z_VIEW -= 0.2;
				Y_VIEW -= 0.2;
				X_VIEW -= 0.2;
			}
			initView();
			break;*/

		case 'z':
			if (iSubdivision >= 2)
			{
				for (unsigned int i = 0; i < SpherePieses.size(); i++)
					SpherePieses.at(i).model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0, 0, 1)) * SpherePieses.at(i).model;
			}
			else
				Sphere.model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0, 0, 1)) * Sphere.model;

			break;
		case 'y':
			if (iSubdivision >= 2)
			{
				for (unsigned int i = 0; i < SpherePieses.size(); i++)
					SpherePieses.at(i).model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0, 1, 0)) * SpherePieses.at(i).model;
			}
			else
				Sphere.model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0, 1, 0)) * Sphere.model;
			break;
		case 'x':
			if (iSubdivision >= 2)
			{
				for (unsigned int i = 0; i < SpherePieses.size(); i++)
					SpherePieses.at(i).model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(1, 0, 0)) * SpherePieses.at(i).model;
			}
			else
				Sphere.model = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(1, 0, 0)) * Sphere.model;
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
				iPrevSubdivision = iSubdivision;
				iSubdivision -= 1;
				SubDivisionAlgorithm();
			}
			break;

		default:
			break;
		}

	glutPostRedisplay();	// markiert das aktuelle Fenster als "neu anzuzeigen"
}

int main(int argc, char** argv)
{
					///  START: erzeuge Fenster
	// Initialisiere "FreeGLUT" - Bibliothek (window toolkit)
	glutInit(&argc, argv); // FreeGLUT benötigt mehrere Parameter (siehe main(...)) für das Programm-Kontolle...
						   /*This function does not return anything, but simply sets up FreeGLUT for use in your application.
						   In any program, this should be the first FreeGLUT function you should call!*/

	// GLUT: Initialisiere "FreeGLUT" - Bibliothek (window toolkit).
    glutInitWindowSize    (WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(40,40);

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
