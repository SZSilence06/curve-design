#ifndef HJ_DEF_CTRL_RENDER_H_
#define HJ_DEF_CTRL_RENDER_H_

#include "conf.h"

#include "../working_space/def_ctrl.h"

class WSRAPI def_ctrl_render
{
public:
	def_ctrl_render(const def_ctrl &df);
	void set_color_table(const zjucad::matrix::matrix<double> &ct);
	void bounding_box(float min_max[2][3]) const;
	void render(void);
	double size_;
private:
	const zjucad::matrix::matrix<double> *color_table_;
	const def_ctrl &def_ctrl_;
};

#endif
