#include "trimesh.h"
#include <jtflib/mesh/io.h>
#include <jtflib/mesh/mesh.h>

using namespace framework::scene;

using namespace zjucad::matrix;

int trimesh::load(const std::string & file)
{
  int rtn = jtf::mesh::load_obj(file.c_str(),m_.mesh_, m_.node_);
  if(rtn == 0){
      nst_ = node_state_type::NEW_ADDED;
  }
  compute_average_edge_length();
  return rtn;
}

int trimesh::save(const std::string & file)
{
  return __LINE__;
}

void trimesh::set_name(const std::string &name)
{
  name_ = name;
}

model_type trimesh::get_model_type()const
{
  return model_type::TRIMESH;
}


node_state_type trimesh::get_node_state()const
{
  return nst_;
}

void trimesh::lock()
{
  lock_.lock();
}

void trimesh::unlock()
{
  lock_.unlock();
}

const std::string & trimesh::get_name()const
{
  return name_;
}

void trimesh::reset_state(const node_state_type nst)
{
  nst_ = nst;
}

const jtf::mesh::meshes & trimesh::get_mesh() const
{
  return m_;
}

void trimesh::compute_average_edge_length()
{
    size_t a = 0, b = 0, cnt = 0;
    double sum = 0;
    for (size_t i = 0; i < m_.mesh_.size(2); ++i) {
      for (size_t j = 0; j < 3; ++j) {
        a = j;
        b = (j+1)%3;
        sum += norm(m_.node_(colon(), m_.mesh_(a, i)) - m_.node_(colon(), m_.mesh_(b, i)));
        ++cnt;
      }
    }
    this->average_edge_length_ = sum / cnt;
}
