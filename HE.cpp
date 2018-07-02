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

