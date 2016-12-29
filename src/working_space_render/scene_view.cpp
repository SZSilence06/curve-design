#include "scene_view.h"
#include "tri_mesh_render.h"
#include "def_ctrl_render.h"

#include "../working_space/working_space.h"
#include <osg/ShapeDrawable>
#include "../common/osg_util.h"
using namespace osg;

#include "../globals/globals.h"

using namespace hj::mesh;

#include <iostream>
using namespace std;

#include "../working_space/data_tree.h"
#include "../working_space/message_queue.h"
#include "trimesh_render.h"
#include "sphere_render.h"
#include "line_render.h"
#include <boost/property_tree/ptree.hpp>

namespace framework
{
  namespace render
  {
    class GroupCallBack: public osg::NodeCallback
    {
    public:
      GroupCallBack(const boost::property_tree::ptree &render_config,
                    view_type vt):render_config_(render_config),vt_(vt){}
      virtual ~GroupCallBack(){}
      virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
      {
        auto group = dynamic_cast<osg::Group*>(node);
        auto viewer_ptr = dynamic_cast<working_space_scene_view*>(node->getUserData());

        while(viewer_ptr->is_message_queue_empty() == false){
            auto info = viewer_ptr->message_pop_front();
            if(std::get<1>(info) == framework::scene::node_state_type::NEW_ADDED){
                auto model = std::get<2>(info);
                osg::ref_ptr<framework::render::mesh_render> tr;
                switch ((*model)->get_model_type()) {
                case scene::model_type::TRIMESH:
                    tr = new framework::render::trimesh_render(model, render_config_);
                    break;
                case scene::model_type::SPHERE:
                    tr = new sphere_render(model, render_config_);
                    break;
                case scene::model_type::LINE:
                    tr = new line_render(model, render_config_);
                    break;
                default:
                    break;
                }
                tr->setName(std::get<0>(info));
                group->addChild(tr);
              }else if(std::get<1>(info) == framework::scene::node_state_type::DELETED)
              {
                //TODO: should remove the node by info from name_nodes
                auto name = std::get<0>(info);
                removeChildrenByName(group, name);
              }
          }
        traverse(node,nv);
      }
    private:
      void removeChildrenByName(osg::Group* group, const std::string& name)
      {
          for(int i = 0; i < group->getNumChildren(); i++)
          {
              auto child = group->getChild(i);
              if(child->getName() == name)
              {
                  group->removeChildren(i, 1);
              }
          }
      }

    private:
      const boost::property_tree::ptree & render_config_;
      const view_type vt_;
    };


    working_space_scene_view::working_space_scene_view(const std::string & name, view_type vt)
      :vt_(vt)
    {
      setName(name);
      g_ = new osg::Group();
      g_->setDataVariance(osg::Object::DYNAMIC);
      osg::ref_ptr<GroupCallBack> gcb = new GroupCallBack(render_config_, vt_);
      g_->setUpdateCallback(gcb);
      g_->setUserData(this);

      setSceneData(g_);
      setThreadingModel(osgViewer::Viewer::AutomaticSelection);
    }

    working_space_scene_view::~working_space_scene_view()
    {}

    void working_space_scene_view::post_update()
    {
      auto &tree = framework::scene::data_tree::get_instance();
      for(auto it = tree.cbegin(); it != tree.cend(); ++it)
        {
          if(((*it->second)->get_model_type() == framework::scene::model_type::PATCH2D) &&
             vt_ == view_type::V3D )
            continue; // 2d models in a 3d viewer, none of my buinese

          if(((*it->second)->get_model_type() != framework::scene::model_type::PATCH2D) &&
             vt_ == view_type::V2D )
            continue; // 3d models in a 2d viewer, none of my buinese

          if((*it->second)->get_node_state() == framework::scene::node_state_type::ORDINARY)
            continue;

          if((*it->second)->get_node_state() == framework::scene::node_state_type::NEW_ADDED)
            add_render_node(it->first, *it->second);

          if((*it->second)->get_node_state() == framework::scene::node_state_type::DELETED)
            remove_render_node(it->first, *it->second);

          if((*it->second)->get_node_state() == framework::scene::node_state_type::UPDATED)
            update_node(it->first, *it->second);
        }
    }

    void working_space_scene_view::add_render_node(const std::string & name, const locked_shared_ptr<framework::scene::model_base> & lsp)
    {
      framework::scene::info i(name, framework::scene::node_state_type::NEW_ADDED, &lsp);
      mq_.push_back(i);
    }

    void working_space_scene_view::remove_render_node(const std::string & name, const locked_shared_ptr<framework::scene::model_base> & lsp)
    {
      framework::scene::info i(name, framework::scene::node_state_type::DELETED, &lsp);
      mq_.push_back(i);
    }

    void working_space_scene_view::update_node(const std::string & name, const locked_shared_ptr<framework::scene::model_base> & lsp)
    {
      throw std::logic_error("Invalid") ;
    }

    bool working_space_scene_view::is_message_queue_empty()
    {
      return mq_.is_queue_empty();
    }

    void working_space_scene_view::message_push_back(const framework::scene::info & i)
    {
      mq_.push_back(i);
    }

    const framework::scene::info working_space_scene_view::message_pop_front()
    {
      return mq_.pop_front();
    }

    void working_space_scene_view::wait_to_clear_message_queue()
    {
      return mq_.wait_to_clear_queue();
    }
  }
}



//working_space_scene_view::working_space_scene_view()
//  :switch_(0), ctrl_size_(1.0/50)
//{
//}

//#include "xml_util.h"
//HJ_XML_NAMESPACE_USE
//bool working_space_scene_view::load(const hj::xml::dom &node)
//{
//  for(dom::children::const_iterator i = node.children_.begin(); i != node.children_.end(); ++i) {
//      if(i->type_ != ELEMENT) continue;
//      if(i->value_ == "ctrl_size") {
//          ctrl_size_ = get<double>(*i);
//        }
//    }

//  return true;
//}

//void working_space_scene_view::init(const working_space &ws)
//{
//  setDefaults();
//  setSceneData(new Group());

//  switch_ = new Switch;
//  {
//    Group *g = getSceneData()->asGroup();
//    g->addChild(switch_);
//  }
//  tri_mesh_node *tmn = new tri_mesh_node(0x01|0x02|0x04, &ws.x_, &ws.n_, &ws.mesh_->triangle_,
//                                         &ws.mesh_->mat_stride_, &ws.mesh_->mtl_, &ws.mesh_->text_coor_, &ws.mesh_->text_coor_idx_);
//  tmn->v_color_ = &ws.v_color_;

//  switch_->addChild(tmn);
//  named_nodes_["tmn"] = tmn;

//  if(ws.bk_mesh_.get()) {
//      tri_mesh_node *tmn = new tri_mesh_node(
//            0x01|0x02|0x04, &ws.bk_mesh_->vertex_, &ws.bk_mesh_->normal_, &ws.bk_mesh_->triangle_,
//            &ws.bk_mesh_->mat_stride_, &ws.bk_mesh_->mtl_, &ws.bk_mesh_->text_coor_, &ws.bk_mesh_->text_coor_idx_);
//      switch_->addChild(tmn);
//      named_nodes_["bk"] = tmn;
//    }

//  osg_drawable<def_ctrl_render> *dcr_ = create_osg_drawable(new def_ctrl_render(*ws.def_ctrl_));
//  dcr_->setUseDisplayList(false);
//  dcr_->drawable_->size_ = getSceneData()->getBound().radius()*ctrl_size_;
//  matrix<double> *ct = 0;
//  if(get_globals().get("color table", &ct) && ct)
//    dcr_->drawable_->set_color_table(*ct);
//  Geode *geode = new Geode;
//  geode->addDrawable(dcr_);
//  switch_->addChild(geode);
//  named_nodes_["dcr"] = geode;
//}

//osg::Matrixd working_space_scene_view::scene2screen(void) const
//{
//  const osg::Matrixd mv(getViewMatrix().ptr()),
//      proj = getProjectionMatrix(),
//      wm = getViewport()->computeWindowMatrix();
//  return mv*proj*wm;
//}

//int working_space_scene_view::dirtyBound(const char *node_name)
//{
//  int rtn = 0;
//  if(!strcmp("tmn", node_name)) {
//      tri_mesh_node *tmn = dynamic_cast<tri_mesh_node *>(named_nodes_["tmn"]);
//      if(!tmn) return -1;
//      tmn->dirtyBound();
//    }
//  else
//    if(!strcmp("dcr", node_name)) {
//        Geode *geode = dynamic_cast<Geode *>(named_nodes_["dcr"]);
//        if(!geode) rtn = -1;
//        geode->getDrawable(0)->dirtyBound();	// Geode and Node::dirtyBound do not call into Drawable::dirtyBound.
//      }
//  return rtn;
//}

//void working_space_scene_view::on_reshape(int width, int height)
//{
//  double fov, tmp;
//  getProjectionMatrixAsPerspective(fov, tmp, tmp, tmp);

//  setProjectionMatrixAsPerspective(fov, float(width)/height, 1, 10);
//  setViewport(0, 0, width, height);
//}
