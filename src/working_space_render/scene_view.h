#ifndef HJ_WORKING_SPACE_RENDER_SCENE_VIEW_H_
#define HJ_WORKING_SPACE_RENDER_SCENE_VIEW_H_

#include "conf.h"

#include <osgViewer/Viewer>
#include <osg/Matrix>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include "../working_space/locked_shared_ptr.h"
#include "../working_space/model.h"
#include "../working_space/message_queue.h"

namespace framework
{
  namespace render
  {
    enum class view_type
    {
      V3D,
      V2D
    };

    class working_space_scene_view : public osgViewer::Viewer
    {
    public:
      explicit working_space_scene_view(const std::string &view_name, view_type vt);
      ~working_space_scene_view();

      void post_update();

      view_type get_view_type() const { return vt_;}
      boost::property_tree::ptree & get_render_config(){ return render_config_; }

      osg::ref_ptr<osg::Group> get_render_tree(){ return g_; }

      bool is_message_queue_empty();
      void message_push_back(const framework::scene::info &);
      void wait_to_clear_message_queue();
      const framework::scene::info message_pop_front();
      
    private:
      void update_node(const std::string &name, const locked_shared_ptr<framework::scene::model_base> & lsp);

      void add_render_node(const std::string & name, const locked_shared_ptr<framework::scene::model_base> & lsp);

      void remove_render_node(const std::string & name, const locked_shared_ptr<framework::scene::model_base> & lsp);
    private:
      osg::ref_ptr<osg::Group> g_;
      std::map<std::string, osg::Group*> named_nodes_;
      boost::property_tree::ptree render_config_;
      view_type vt_;
      framework::scene::message_queue mq_;
    };
  }
}

#endif
