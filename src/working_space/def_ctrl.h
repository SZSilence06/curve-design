#ifndef HJ_DEF_CTRL_H_
#define HJ_DEF_CTRL_H_

#include "conf.h"

#include <map>
#include <zjucad/matrix/matrix.h>

class HJ_WORKING_SPACE_API def_ctrl
{
public:
	def_ctrl();
	class HJ_WORKING_SPACE_API region
	{
	public:
		region();
		zjucad::matrix::matrix<int> idx_;
		zjucad::matrix::matrix<double> pos_, weight_;
		void init_weight(const zjucad::matrix::matrix<double> &v);
	};
	typedef std::map<int, region> region_container;
	region_container regions_;
	int active_region_;
	bool dirty_;

	bool pick_region(int v_idx);
	void collect(zjucad::matrix::matrix<int> &idx, zjucad::matrix::matrix<double> &pts) const;

	bool load(const char *path);
	bool save(const char *path) const;

	bool load_bin(const char *path);
	bool save_bin(const char *path) const;

	bool load_txt(const char *path);
	bool save_txt(const char *path) const;
};

#endif
