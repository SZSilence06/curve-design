#ifndef WORKING_SPACE_MESH_RENDER_H
#define WORKING_SPACE_MESH_RENDER_H

#include <osg/Switch>
#include "../working_space/model.h"
#include "../working_space/locked_shared_ptr.h"
#include <boost/property_tree/ptree.hpp>

namespace framework
{
  namespace render
  {
    class mesh_render : public osg::Switch
    {
    public:
      virtual ~mesh_render(){}
      virtual void update(const locked_shared_ptr<framework::scene::model_base> * lsp, const boost::property_tree::ptree & render_config) = 0;
    };
  }
}
#endif // WORKING_SPACE_MESH_RENDER_H
