#include "def_ctrl.h"
#include "util.h"

#include <fstream>
using namespace std;

#include <zjucad/matrix/io.h>
using namespace zjucad::matrix;

def_ctrl::def_ctrl()
:active_region_(-1), dirty_(true)
{
}

bool def_ctrl::pick_region(int v_idx)
{
	if(v_idx < 0) {
		active_region_ = -1;
		return false;
	}
	region_container::const_iterator i;
	for(i = regions_.begin(); i != regions_.end(); ++i) {
		if(find(i->second.idx_, v_idx) >= 0)
			break;
	}
	if(i == regions_.end()) {
		active_region_ = -1;
		return false;
	}
	active_region_ = i->first;
	return true;
}

def_ctrl::region::region()
{
}

void def_ctrl::region::init_weight(const zjucad::matrix::matrix<double> &v)
{
	weight_.resize(v.size(2), idx_.size());
	for(int j = 0; j < idx_.size(); ++j) {
		for(int i = 0; i < weight_.size(1); ++i) {
			double len = norm(v(colon(), i)-pos_(colon(), j));
			if(len < 1e-10) len = 1e-10;	// for convenience currently
			weight_(i, j) = 1.0/pow(len, 2);
		}
	}
}

void  def_ctrl::collect(matrix<int> &idx, matrix<double> &pts) const
{
	int pn = 0;
	region_container::const_iterator i;
	for(i = regions_.begin(); i != regions_.end(); ++i)
		pn += i->second.idx_.size();
	idx.resize(pn);
	pts.resize(3, pn);
	for(pn = 0, i = regions_.begin(); i != regions_.end(); ++i) {
		for(int j = 0; j < i->second.idx_.size(); ++j, ++pn) {
			idx(pn) = i->second.idx_[j];
			pts(colon(), pn) = i->second.pos_(colon(), j);
		}
	}
}

bool def_ctrl::load(const char *path)
{
	// string suf = hj::util::suffix(path);
	// if(suf == "ctrl.bin")
	// 	return load_bin(path);
	// if(suf == "ctrl.txt")
	// 	return load_txt(path);
	// return false;
}

bool def_ctrl::save(const char *path) const
{
	// string suf = hj::util::suffix(path);
	// if(suf == "ctrl.bin")
	// 	return save_bin(path);
	// if(suf == "ctrl.txt")
	// 	return save_txt(path);
	// return false;
}

bool def_ctrl::load_bin(const char *path)
{
	ifstream ifs;
	ifs.open(path, ifstream::binary);
	if(ifs.fail()) return false;
	region r;
	int key;
	while(!ifs.eof()) {
		read_raw_val(ifs, key);
		if(!ifs.good()) break;
		region &r = regions_[key];
		read(ifs, r.idx_);
		read(ifs, r.pos_);
	}
	ifs.close();
	dirty_ = true;
	return true;
}

bool def_ctrl::save_bin(const char *path) const
{
	ofstream ofs;
	ofs.open(path, ofstream::binary);
	if(ofs.fail()) return false;
	region_container::const_iterator i;
	for(i = regions_.begin(); i != regions_.end(); ++i) {
		write_raw_val(ofs, i->first);
		write(ofs, i->second.idx_);
		write(ofs, i->second.pos_);
	}
	ofs.close();
	return true;
}

bool def_ctrl::load_txt(const char *path)
{
	ifstream ifs;
	ifs.open(path);
	if(ifs.fail()) return false;
	region r;
	int region_num;
	ifs >> region_num;
	int key;
	while(!ifs.eof()) {
		ifs >> key;
		if(!ifs.good()) break;
		region &r = regions_[key];
		ifs >> r.idx_;
		ifs >> r.pos_;
	}
	ifs.close();
	dirty_ = true;
	return true;
}

bool def_ctrl::save_txt(const char *path) const
{
	ofstream ofs;
	ofs.open(path);
	if(ofs.fail()) return false;
	ofs << regions_.size() << endl;
	region_container::const_iterator i;
	for(i = regions_.begin(); i != regions_.end(); ++i) {
		ofs << i->first << '\n';
		ofs << i->second.idx_;
		ofs << i->second.pos_;
	}
	ofs.close();
	return true;
}
