#ifndef HJ_TRI_MESH_H
#define HJ_TRI_MESH_H

#include <zjucad/matrix/matrix.h>
#include <vector>


namespace hj { namespace mesh {

using zjucad::matrix::matrix;

class tri_mesh
{
public:
	// geometry
	matrix<double>	vertex_, normal_;
	matrix<int>		triangle_;
	// appearance
	matrix<int>  mat_stride_;
	matrix<double> text_coor_;
	matrix<int> text_coor_idx_;
	//	std::vector<material> mtl_;
	// io
	bool load(const char *path);
	bool save(const char *path) const;
};

}}

#endif
