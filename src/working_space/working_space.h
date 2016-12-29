#ifndef HJ_WORKING_SPACE_H_
#define HJ_WORKING_SPACE_H_

#include "conf.h"

#include "mesh.h"

#include <memory>

#include <zjucad/matrix/matrix.h>

class tet_mesh;
class def_ctrl;

class HJ_WORKING_SPACE_API working_space
{
public:
	working_space();
	~working_space();
	bool deform(void);
	void reset(void);

	std::unique_ptr<hj::mesh::tri_mesh> bk_mesh_;
	std::unique_ptr<hj::mesh::tri_mesh> mesh_;
	std::unique_ptr<def_ctrl> def_ctrl_;
	zjucad::matrix::matrix<double> v_color_, x_, n_;

protected:
	void init(void);
};

#endif
