#include "def_ctrl_render.h"
#include "util.h"
using namespace zjucad::matrix;

#include <algorithm>
#include <limits>
#include <fstream>
using namespace std;

#include <GL/glut.h>
#include <GL/gl.h>

def_ctrl_render::def_ctrl_render(const def_ctrl &df)
:def_ctrl_(df), size_(0.02), color_table_(0)
{
}

void def_ctrl_render::bounding_box(float min_max[2][3]) const
{
	fill(min_max[0]+0, min_max[0]+3, +numeric_limits<float>::infinity());
	fill(min_max[1]+0, min_max[1]+3, -numeric_limits<float>::infinity());
	matrix<double> bb;
	def_ctrl::region_container::const_iterator i;
	int j;
	for(i = def_ctrl_.regions_.begin(); i != def_ctrl_.regions_.end(); ++i) {
		::bounding_box(bb, i->second.pos_);
		for(j = 0; j < 3; ++j) {
			min_max[0][j] = min(min_max[0][j], static_cast<float>(bb(j, 0)));
			min_max[1][j] = max(min_max[1][j], static_cast<float>(bb(j, 1)));
		}
	}
	const float r = 0.2;	// TODO: need to calculate the real sphere radius
	for(j = 0; j < 3; ++j) {
		min_max[0][j] -= size_;
		min_max[1][j] += size_;
	}
}

void def_ctrl_render::render(void)
{
	const double default_color[3] = {0.5, 0.5, 0.5};
	def_ctrl::region_container::const_iterator i;
	glColor3d(0, 0, 1);
	for(i = def_ctrl_.regions_.begin(); i != def_ctrl_.regions_.end(); ++i) {
		const matrix<double> &pos = i->second.pos_;
		const double *pcolor = color_table_?&(*color_table_)(0, i->first):default_color;
		if(i->first == def_ctrl_.active_region_)
			glColor3d(pcolor[0]*2, pcolor[1]*2, pcolor[2]*2);
		else
			glColor3dv(pcolor);
		for(int j = 0; j < pos.size(2); ++j) {
			glPushMatrix();
			glTranslated(pos(0, j), pos(1, j), pos(2, j));
			glutSolidSphere(size_, 10, 10);
			glPopMatrix();
		}
	}
}

void def_ctrl_render::set_color_table(const zjucad::matrix::matrix<double> &ct)
{
	color_table_ = &ct;
}
