#include "working_space.h"

#include "def_ctrl.h"

#include "mesh.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

using namespace hj::mesh;

#include <hjlib/math/blas_lapack.h>
#include <zjucad/matrix/lapack.h>

#include <zjucad/matrix/io.h>

using namespace zjucad::matrix;

#include "util.h"

//#include <hjlib/util/mics.h>

#include <boost/bind.hpp>

// static bool load_object(const dom &node, working_space &ws)
// {
//   for(dom::children::const_iterator i = node.children_.begin(); i != node.children_.end(); ++i) {
//       if(i->type_ != ELEMENT) continue;
//       if(i->value_ == "mesh") {
//           ws.mesh_.reset(new tri_mesh);
//           if(!ws.mesh_->load(get<xml_util::word>(*i).c_str())) {
//               cout << "load mesh fail." << endl;
//               return false;
//             }
//           vertex_normal(ws.mesh_->normal_, ws.mesh_->vertex_, ws.mesh_->triangle_);
//         }
//       else if(i->value_ == "bk") {
//           ws.bk_mesh_.reset(new tri_mesh);
//           if(!ws.bk_mesh_->load(get<xml_util::word>(*i).c_str())) {
//               cout << "load mesh fail." << endl;
//               return false;
//             }
//           vertex_normal(ws.bk_mesh_->normal_, ws.bk_mesh_->vertex_, ws.bk_mesh_->triangle_);
//         }
//     }

//   return true;
// }

working_space::working_space()
{
  //ginterface4def_interf_.reset(new interface4def_interf(*this));
}

working_space::~working_space()
{
}

void working_space::init(void)
{
  x_ = mesh_->vertex_;
  n_ = mesh_->normal_;
}

void working_space::reset(void)
{
  x_ = mesh_->vertex_;

  def_ctrl::region_container &rc = def_ctrl_->regions_;
  def_ctrl::region_container::iterator i;
  for(i = rc.begin(); i != rc.end(); ++i) {
      def_ctrl::region &r = i->second;
      for(int j = 0; j < r.idx_.size(); ++j)
        r.pos_(colon(), j) = mesh_->vertex_(colon(), r.idx_[j]);
    }

  vertex_normal(n_, x_, mesh_->triangle_);
}

