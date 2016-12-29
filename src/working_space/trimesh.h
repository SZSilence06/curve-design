#ifndef WORKING_SPACE_TRIMESH_H
#define WORKING_SPACE_TRIMESH_H

#include "model.h"
#include <boost/thread/recursive_mutex.hpp>
#include <jtflib/mesh/mesh.h>

namespace framework
{
  namespace scene
  {
    class trimesh : public model_base
    {
    public:
      trimesh():nst_(node_state_type::ORDINARY){}
      trimesh(const std::string & name):nst_(node_state_type::ORDINARY), name_(name){}
      virtual ~trimesh(){}
      virtual int load(const std::string & file);
      virtual int save(const std::string & file);
      virtual void set_name(const std::string &name);
      virtual model_type get_model_type()const;
      virtual node_state_type get_node_state()const;
      virtual const std::string & get_name()const;
      virtual void reset_state(const node_state_type );
      virtual void lock();
      virtual void unlock();
      const jtf::mesh::meshes & get_mesh() const;

      double get_average_edge_length() const { return average_edge_length_; }

    private:
      void compute_average_edge_length();

    private:
      std::string name_;
      node_state_type nst_;
      boost::recursive_mutex lock_;
      jtf::mesh::meshes m_;

      double average_edge_length_;
    };
  }
}

#endif // WORKING_SPACE_TRIMESH_H
