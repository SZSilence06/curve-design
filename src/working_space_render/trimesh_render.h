#ifndef WORKING_SPACE_TRIMESH_RENDER_H
#define WORKING_SPACE_TRIMESH_RENDER_H

#include "mesh_render.h"
#include <osg/Drawable>

namespace framework
{
  namespace render
  {
    class trimesh_render_node
    {
    public:
      osg::ref_ptr<osg::Geode> geode_;
      osg::ref_ptr<osg::Geometry> geometry_;
      osg::ref_ptr<osg::Vec3Array> vertex_;
      osg::ref_ptr<osg::DrawElementsUInt> triface_;
    };
    
    class trimesh_render: public mesh_render
    {
    public:
    trimesh_render(const locked_shared_ptr<framework::scene::model_base> * mb, const boost::property_tree::ptree & render_config)
      :mb_(mb), render_config_(render_config){init();}
      virtual ~trimesh_render(){}
      
      virtual void update(const locked_shared_ptr<framework::scene::model_base> * lsp, const boost::property_tree::ptree & render_config);
      
    private:
      void init();
    private:
      const boost::property_tree::ptree & render_config_;
      locked_shared_ptr<framework::scene::model_base> const* mb_;
      trimesh_render_node trn;
    };
  }
}

#endif //WORKING_SPACE_TRIMESH_RENDER_H
