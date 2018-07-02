#include <iostream>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <sstream>
#include <string>
using namespace std;

#pragma once
class HE
{
	struct HE_edge {
		struct HE_vert* vert;
		struct HE_edge* pair;
		struct HE_face* face;
		struct HE_edge* next;
	};
	struct HE_vert {
		float x;
		float y;
		float z;
		HE_edge* edge;
	};
	struct HE_face {
		HE_edge* edge;
	};
	struct obj {
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec4> faces;
	};
public:
	HE();
	~HE();

	obj readObjFile();
};

