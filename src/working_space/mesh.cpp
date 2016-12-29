#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "mesh.h"

namespace hj { namespace mesh {

using namespace zjucad::matrix;

static bool consistent_fi_vti(const matrix<double> &vt, const matrix<int> &fi,
							  matrix<int> &vti, matrix<double> &vt0)
{
	if(max(vti) != max(fi)) return false;
	vt0 = vt;
	for(int i = 0; i < fi.size(); ++i)
		vt0(colon(), fi[i]) = vt(colon(), vti[i]);
	vti = fi;
	return true;
}

bool tri_mesh::load(const char *path)
{
	// return load_obj_mesh(path,
	// 	&vertex_, &triangle_, &normal_,
	// 	&text_coor_, &text_coor_idx_,
	// 	&mat_stride_, &mtl_);
}

bool tri_mesh::save(const char *path) const
{
  //	return save_obj_mesh(path, vertex_, triangle_);
}

}}
