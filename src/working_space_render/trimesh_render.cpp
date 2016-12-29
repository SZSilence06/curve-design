#include "trimesh_render.h"
#include "../working_space/trimesh.h"
#include <osg/Geode>
#include <osg/Geometry>
#include <osgUtil/SmoothingVisitor>
#include <osgFX/Scribe>

namespace framework
{
  namespace render
  {
    template <typename MESH>
    void mesh2osg(const MESH &m, const osg::ref_ptr<osg::Vec3Array> &vertex,
                  const osg::ref_ptr<osg::DrawElementsUInt> & tri_face)
    {
      for(size_t fi = 0; fi < m.mesh_.size(2); ++fi)
        {
          for(size_t di = 0; di < m.mesh_.size(1); ++di)
            {
              tri_face->push_back(m.mesh_(di,fi));
            }
        }

      osg::Vec3 temp;
      for(size_t vi = 0; vi < m.node_.size(2); ++vi)
        {
          for(size_t di = 0; di < m.node_.size(1); ++di)
            {
              temp[di] = m.node_(di,vi);
            }
          vertex->push_back(temp);
        }
    }
    
    template <typename MESH>
    osg::ref_ptr<osg::Geode> create_trimesh_render_node(const MESH &m, trimesh_render_node &trn)
    {
      if(!trn.geode_.get())
        trn.geode_ = new osg::Geode();
      if(!trn.geometry_.get())
        trn.geometry_ = new osg::Geometry();
      if(!trn.vertex_.get())
        trn.vertex_ = new osg::Vec3Array();
      if(!trn.triface_.get())
        trn.triface_ = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES);


      mesh2osg(m, trn.vertex_, trn.triface_);

      trn.geometry_->setVertexArray(trn.vertex_);
      trn.geometry_->getPrimitiveSetList().clear();
      trn.geometry_->addPrimitiveSet(trn.triface_);

      trn.geode_->removeDrawables(0, trn.geode_->getNumDrawables());
      trn.geode_->addDrawable(trn.geometry_.get());

      osgUtil::SmoothingVisitor sv;
      trn.geode_->accept(sv);

      return trn.geode_;
    }
    
    void trimesh_render::init()
    {
      assert(mb_ != nullptr);
      if((*mb_)->get_model_type() != scene::model_type::TRIMESH)
        throw std::logic_error("Invalid Type For Trimesh Render.");

      auto tm = mb_->cast<const framework::scene::trimesh>();

      osg::ref_ptr<osg::Geode> surface = create_trimesh_render_node(tm->get_mesh(), trn);

      osg::ref_ptr<osgFX::Scribe> scribe = new osgFX::Scribe();
      scribe->setWireframeColor(osg::Vec4(0.0, 0.0, 1.0, 1.0));
      scribe->addChild(surface);

      addChild(scribe);
      setAllChildrenOn();
    }

    void trimesh_render::update(const locked_shared_ptr<framework::scene::model_base> * lsp, const boost::property_tree::ptree & render_config)
    {
      throw std::logic_error("Error.");
    }
  }
}
