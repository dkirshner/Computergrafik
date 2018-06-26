struct HE_edge {
	HE_vert* vert;
	HE_edge* pair;
	HE_face* face;
	HE_edge* next;
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

void initobj() {

};
