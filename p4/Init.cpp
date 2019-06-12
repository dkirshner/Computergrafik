#include "Init.h"

unsigned short iSubdivision = 0, iPrevSubdivision = 0;	// init 

void initBaseSphere(int a_iId)
{
	// Konstruiere Dreiecke. Diese Vektoren können den Gültigkeitsbereich verlassen, nachdem wir alle Daten an die Grafikkarte gesendet haben.
	// Jede Seite hat zwei Dreiecke mit 3 Eckpunkten

	verticesSphereArr[a_iId] = {	// Punkte der Dreiecke
		{ 0.5f, 0.0f, -0.5f }, //front
		{ 0.5f, 0.0f,  0.5f },
		{ 0.0f, 0.87f, 0.0f },

		{ -0.5f, 0.0f, 0.5f },
		{ -0.5f, 0.0f, -0.5f },
		{ 0.0f, -0.87f, 0.0f }
	};

	colorsSphereArr[a_iId] = {	// Einheitliche Farbe gelb!
		{ 1.0f, 1.0f, 0.0f }, // front
		{ 1.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f },

		{ 1.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f }, // end front

		{ 1.0f, 1.0f, 0.0f }, //bottom
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

	// Die Indizes der Punkte, von vorne beginnend
	indicesSphereArr[a_iId] = {
		0, 1, 2,
		2, 1, 3,
		2, 3, 4,
		2, 4, 0,
		5, 4, 0,
		5, 1, 0,
		5, 1, 3,
		5, 3, 4
	};
}

// 	GLuint programId = program.getHandle();
void initSphere(GLuint a_programId, Object* a_Sphere, double a_dRadius, int a_iID, bool a_bSubDivReset)
{
	if (a_bSubDivReset)
	{
		iSubdivision = 0;
		a_bSubDivReset = false;
	}

	if (iSubdivision == 0)
	{
		a_Sphere->iID = a_iID;
		initBaseSphere(a_iID);

		iPrevSubdivision = iSubdivision;
		iSubdivision += 1;
		SubDivisionAlgorithm(a_dRadius, a_Sphere);
	}

	// Schritt 0: Ein Vertex-Array-Objekt erstellen
	glGenVertexArrays(1, &a_Sphere->vao);
	glBindVertexArray(a_Sphere->vao);

	// Schritt 1: Ein Vertex-Pufferobjekt für das Positionsattribut erstellen und binden Sie es an das zugehörige "Shader-Attribut".
	glGenBuffers(1, &a_Sphere->positionBuffer);				// Generieren Sie 1 Puffer und geben Sie den resultierenden Bezeichner in den Vertexbuffer ein
	glBindBuffer(GL_ARRAY_BUFFER, a_Sphere->positionBuffer);	// Die folgenden Befehle sprechen über unseren 'Vertexbuffer'-Puffer
															// Geben Sie unsere Eckpunkte an OpenGL.
	glBufferData(GL_ARRAY_BUFFER, verticesSphereArr[a_iID].size() * sizeof(glm::vec3), verticesSphereArr[a_iID].data(), GL_STATIC_DRAW);

	// Bind it to position.
	GLuint pos = glGetAttribLocation(a_programId, "position");
	glEnableVertexAttribArray(pos);
	/*Vertex-Attribute können durch die glVertexAttribPointer-Funktion und ihre beiden Schwesterfunktionen glVertexAttribIPointer und glVertexAttribLPointer beschrieben werden.*/
	glVertexAttribPointer(	pos,			// attribute 0. Kein besonderer Grund für 0, muss aber mit dem Layout im Shader übereinstimmen.
							3,				// size
							GL_FLOAT,		// type
							GL_FALSE,		// normalized?
							0,				// stride (Forschritt)
							0);				// array buffer offset

					// Schritt 2: Ein Vertex-Pufferobjekt für das Farbattribut erstellen und anbinden ...
	glGenBuffers(1, &a_Sphere->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, a_Sphere->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colorsSphereArr[a_iID].size() * sizeof(glm::vec3), colorsSphereArr[a_iID].data(), GL_STATIC_DRAW);

	// Binde es an die Farbe.
	pos = glGetAttribLocation(a_programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Schritt 3: Vertex-Pufferobjekt für Indizes erstellen. Hier ist keine Bindung erforderlich.
	glGenBuffers(1, &a_Sphere->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a_Sphere->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSphereArr[a_iID].size() * sizeof(GLushort), indicesSphereArr[a_iID].data(), GL_STATIC_DRAW);

	// Löse die Bindung des Vertex - Array - Objekts(zurück zur Standardeinstellung).
	glBindVertexArray(0);
	// INIT: Transformation der Kugel
	// Modify model matrix.
	a_Sphere->model = glm::scale(glm::mat4(1.0f), glm::vec3(a_dRadius, a_dRadius, a_dRadius)); 
}

// Ist schon ein Punkt in einer aktuellen Liste enthalten
bool IsVertexSaved(glm::vec3 a_Pnt, int *a_Index, int a_iID)
{
	for (int i = 0; i < verticesSphereArr[a_iID].size(); i++)
	{
		double dVert_X = ceilf(verticesSphereArr[a_iID].at(i).x * 1000) / 1000;
		double dVert_Y = ceilf(verticesSphereArr[a_iID].at(i).y * 1000) / 1000;
		double dVert_Z = ceilf(verticesSphereArr[a_iID].at(i).z * 1000) / 1000;

		double dPnt_X = ceilf(a_Pnt.x * 1000) / 1000;
		double dPnt_Y = ceilf(a_Pnt.y * 1000) / 1000;
		double dPnt_Z = ceilf(a_Pnt.z * 1000) / 1000;

		if (dVert_X == dPnt_X &&
			dVert_Y == dPnt_Y &&
			dVert_Z == dPnt_Z)
		{
			*a_Index = i;
			return true;
		}
	}

	return false;
}

// clear actual data
bool ClearActualData(const int a_iID)
{
	verticesSphereArr[a_iID].clear();
	indicesSphereArr[a_iID].clear();
	colorsSphereArr[a_iID].clear();
	SpherePiesesArr[a_iID].clear();

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Mittelpunkt von 2 Eckpunkten finden
// HINWEIS: Die Größe des neuen Scheitelpunkts muss geändert werden, damit die Länge dem Radius entspricht
///////////////////////////////////////////////////////////////////////////////
void computeHalfVertex(glm::vec3 v1, glm::vec3 v2, glm::vec3 *newV, const double a_dRadius)
{
	newV->x = v1[0] + v2[0];    // x
	newV->y = v1[1] + v2[1];    // y
	newV->z = v1[2] + v2[2];    // z
	double dResult = sqrt(newV->x * newV->x + newV->y * newV->y + newV->z * newV->z);
	const double scale = a_dRadius / dResult;
	newV->x = newV->x * (float)scale;
	newV->y = newV->y * (float)scale;
	newV->z = newV->z * (float)scale;
}

// Der Unterteilungsalgorithmus teilt die drei Kantenlinien jedes Dreiecks in zwei Hälften und 
// extrudiert dann den neuen Mittelpunkt nach außen, sodass seine Länge(der Abstand vom Mittelpunkt)
// dem Radius der Kugel entspricht.
int SubDivisionAlgorithm(const double a_dRadius, Object* a_Sphere)
{
	const int iID = a_Sphere->iID;
	int LoopCount = 2;

	if (iID == 0)
		LoopCount = 3;

	if (iSubdivision > 3)
		return false;

	for ( ; iSubdivision <= LoopCount; iSubdivision++)
	{
		vector<glm::vec3>tmpColors;
		vector<glm::vec3>tmpVertices;
		vector<GLushort> tmpIndices;

		glm::vec3 newV1, newV2, newV3; // new vertex positions
		unsigned int index;

		// copy prev vertex/index arrays and clear

		for (int i = 0; i < verticesSphereArr[iID].size(); i++)
			tmpVertices.push_back(verticesSphereArr[iID].at(i));

		for (int i = 0; i < indicesSphereArr[iID].size(); i++)
			tmpIndices.push_back(indicesSphereArr[iID].at(i));

		for (int i = 0; i < colorsSphereArr[iID].size(); i++)
			tmpColors.push_back(colorsSphereArr[iID].at(i));

		ClearActualData(iID);	// Aktuelle Daten löschen

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

			computeHalfVertex(v1, v2, &newV1, a_dRadius);
			computeHalfVertex(v2, v3, &newV2, a_dRadius);
			computeHalfVertex(v1, v3, &newV3, a_dRadius);

			int iIndex_0 = index;
			int iIndex_1 = index + 1;
			int iIndex_2 = index + 2;
			int iIndex_3 = index + 3;
			int iIndex_4 = index + 4;
			int iIndex_5 = index + 5;

			// add 4 new triangles to vertex array
			if (IsVertexSaved(v1, &iIndex_0, iID) == false)
			{
				verticesSphereArr[iID].push_back(v1);		// #0
				iIndex_0 = (int)verticesSphereArr[iID].size() - 1;
			}

			if (IsVertexSaved(v2, &iIndex_1, iID) == false)
			{
				verticesSphereArr[iID].push_back(v2);		// #1
				iIndex_1 = (int)verticesSphereArr[iID].size() - 1;
			}

			if (IsVertexSaved(v3, &iIndex_2, iID) == false)
			{
				verticesSphereArr[iID].push_back(v3);		// #2
				iIndex_2 = (int)verticesSphereArr[iID].size() - 1;
			}

			if (IsVertexSaved(newV1, &iIndex_3, iID) == false)
			{
				verticesSphereArr[iID].push_back(newV1);	// #3
				iIndex_3 = (int)verticesSphereArr[iID].size() - 1;
			}

			if (IsVertexSaved(newV2, &iIndex_4, iID) == false)
			{
				verticesSphereArr[iID].push_back(newV2);	// #4
				iIndex_4 = (int)verticesSphereArr[iID].size() - 1;
			}

			if (IsVertexSaved(newV3, &iIndex_5, iID) == false)
			{
				verticesSphereArr[iID].push_back(newV3);	// #6
				iIndex_5 = (int)verticesSphereArr[iID].size() - 1;
			}

			// Vektoren normalisieren!
			for (int i = 0; i < verticesSphereArr[iID].size(); i++)
			{	
				float x = verticesSphereArr[iID].at(i).x;
				float y = verticesSphereArr[iID].at(i).y;
				float z = verticesSphereArr[iID].at(i).z;
				verticesSphereArr[iID].at(i) *= 1.0f / sqrt(x*x + y*y + z*z);
			}

			////////////////  indices   ////////////////

			indicesSphereArr[iID].push_back(GLushort(iIndex_0));
			indicesSphereArr[iID].push_back(GLushort(iIndex_3));
			indicesSphereArr[iID].push_back(GLushort(iIndex_5));

			indicesSphereArr[iID].push_back(GLushort(iIndex_3));
			indicesSphereArr[iID].push_back(GLushort(iIndex_1));
			indicesSphereArr[iID].push_back(GLushort(iIndex_4));

			indicesSphereArr[iID].push_back(GLushort(iIndex_3));
			indicesSphereArr[iID].push_back(GLushort(iIndex_4));
			indicesSphereArr[iID].push_back(GLushort(iIndex_5));

			indicesSphereArr[iID].push_back(GLushort(iIndex_5));
			indicesSphereArr[iID].push_back(GLushort(iIndex_4));
			indicesSphereArr[iID].push_back(GLushort(iIndex_2));

			//////////////   colors   //////////////////////////

			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));
			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));
			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));

			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));
			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));
			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));

			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));
			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));
			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));

			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));
			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));
			colorsSphereArr[iID].push_back(glm::vec3(1.0f, 1.0f, 0.0f));

			index += 6;

			if (index == 96)
			{
				initSphere(program.getHandle(), a_Sphere, a_dRadius, a_Sphere->iID);
				SpherePiesesArr[a_Sphere->iID].push_back(*a_Sphere);
				bNoBreak = false;
			}
		}

		if (iSubdivision == 2)
		{
			initSphere(program.getHandle(), a_Sphere, a_dRadius, a_Sphere->iID);
			// Bogenmass in Radian: Umrechnung von Grad in Bogenmaß
			// degree = radian * 180/π
			// radian = degree * π/180

			// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
			a_Sphere->model = glm::rotate(glm::mat4(1.0f), ((float)M_PI), glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(a_dRadius, a_dRadius, a_dRadius));

			SpherePiesesArr[a_Sphere->iID].push_back(*a_Sphere);
		}
		else if (iSubdivision == 3)
		{
			// Körper oben #2
			initSphere(program.getHandle(), a_Sphere, a_dRadius, a_Sphere->iID);
			// Bogenmass in Radian: Umrechnung von Grad in Bogenmaß
			// degree =v radian * 180/π
			// radian = degree * π/180
			float dAngle = (float)(M_PI) / (-2.0);

			// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
			a_Sphere->model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(a_dRadius, a_dRadius, a_dRadius));

			SpherePiesesArr[a_Sphere->iID].push_back(*a_Sphere);

			// Körper oben #3
			initSphere(program.getHandle(), a_Sphere, a_dRadius, a_Sphere->iID);

			dAngle = (float)(M_PI) / 2.0;

			// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
			a_Sphere->model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(a_dRadius, a_dRadius, a_dRadius));

			SpherePiesesArr[a_Sphere->iID].push_back(*a_Sphere);

			// Körper oben #4
			initSphere(program.getHandle(), a_Sphere, a_dRadius, a_Sphere->iID);
			dAngle = (float)(M_PI);

			// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
			a_Sphere->model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(a_dRadius, a_dRadius, a_dRadius));

			SpherePiesesArr[a_Sphere->iID].push_back(*a_Sphere);

			// Körper unten #1
			initSphere(program.getHandle(), a_Sphere, a_dRadius, a_Sphere->iID);
			dAngle = (float)(M_PI);

			// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
			a_Sphere->model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(a_dRadius, a_dRadius, a_dRadius));

			SpherePiesesArr[a_Sphere->iID].push_back(*a_Sphere);

			// Körper unten #2
			initSphere(program.getHandle(), a_Sphere, a_dRadius, a_Sphere->iID);
			dAngle = (float)(M_PI) / 2.0;
			float dAngle_2 = (float)(M_PI);

			// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
			a_Sphere->model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(a_dRadius, a_dRadius, a_dRadius));

			SpherePiesesArr[a_Sphere->iID].push_back(*a_Sphere);

			// Körper unten #3
			initSphere(program.getHandle(), a_Sphere, a_dRadius, a_Sphere->iID);
			dAngle = (float)(M_PI) / 2.0;
			dAngle_2 = (float)(M_PI);

			// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
			a_Sphere->model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(a_dRadius, a_dRadius, a_dRadius));

			SpherePiesesArr[a_Sphere->iID].push_back(*a_Sphere);

			// Körper unten #3
			initSphere(program.getHandle(), a_Sphere, a_dRadius, a_Sphere->iID);
			dAngle = (float)(M_PI) / 2.0;
			dAngle_2 = (float)(M_PI)*(-1.0);
			float dAngle_3 = (float)(M_PI) / 2.0;

			// Modifiziere "model matrix": Kugel um Nullpunkt und Z-Achse rotieren!!!
			a_Sphere->model = glm::rotate(glm::mat4(1.0f), dAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), dAngle_2, glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), dAngle_3, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(a_dRadius, a_dRadius, a_dRadius));

			SpherePiesesArr[a_Sphere->iID].push_back(*a_Sphere);
		}

		if (iSubdivision < 3)
			initSphere(program.getHandle(), a_Sphere, a_dRadius, a_Sphere->iID);

		if (tmpVertices.size())
			tmpVertices.clear();

		if (tmpIndices.size())
			tmpIndices.clear();

		if (tmpColors.size())
			tmpColors.clear();

		iPrevSubdivision = iSubdivision;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initAxisSun(GLuint programId)
{
	// Dreieck konstruieren. Diese Vektoren können den Gültigkeitsbereich verlassen, nachdem wir alle Daten an die Grafikkarte gesendet haben.
	const vector<glm::vec3> vertices = { { 0.0f, 1.3, 0.0f },{ 0.0f, -1.3f, 0.0f } };
	// Farbe
	const vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const vector<GLushort> indices = { 1,0 };

	AxisSun.initObject(vertices, colors, indices, programId);
}

void initAxisPlanetStraight(GLuint programId)
{
	// Dreieck konstruieren. Diese Vektoren können den Gültigkeitsbereich verlassen, nachdem wir alle Daten an die Grafikkarte gesendet haben.
	const vector<glm::vec3> vertices = { { -1.8f, 0.7, 0.0f },{ -1.8f, -0.7f, 0.0f } };
	// Farbe
	const vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const vector<GLushort> indices = { 1,0 };

	AxisPlanetStraight.initObject(vertices, colors, indices, programId);
}

void initAxisPlanetSlope(GLuint programId)
{
	// Dreieck konstruieren. Diese Vektoren können den Gültigkeitsbereich verlassen, nachdem wir alle Daten an die Grafikkarte gesendet haben.
	const vector<glm::vec3> vertices = { { 4.2f, 1.3, 0.0f },{ 1.4f, -1.3f, 0.0f } };
	// Farbe
	const vector<glm::vec3> colors = { { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } }; // rot
	const vector<GLushort> indices = { 1,0 };

	AxisPlanetSlope.initObject(vertices, colors, indices, programId);
}
 
