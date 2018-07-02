#include "HE.h"
class HalfEdge {
	
};

HE::HE()
{
}


HE::~HE()
{
}

HE::obj HE::readObjFile()
{
	std::vector<glm::vec3> vertices = {};
	std::vector<glm::vec3>::iterator itv;

	itv = vertices.end();

	ifstream file;
	file.open("A1_testcubeBig_trans.obj");

	int x, y, z; 
	char a; 
	while ((file >> a >> x >> y >> z) && (a == 'v'))
	{
		vertices.insert(itv, { x,y,z });
		itv = vertices.end();
	}

	std::vector<glm::vec4> faces = {};
	std::vector<glm::vec4>::iterator itf;
	itf = faces.end();

	int g, h, i, j;
	char a;
	while ((file >> a >> g >> h >> i >> j) && (a == 'f'))
	{
		faces.insert(itf, { g,h,i,j });
		itf = faces.end();
	}

	file.close();

	HE::obj object;
	object.faces = faces;
	object.vertices = vertices;

	return object;
}
