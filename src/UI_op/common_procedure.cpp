#include "common_procedure.h"

#include <string>
#include "../working_space/data_tree.h"
#include "../app/app.h"
#include "../working_space_render/scene_view.h"
#include "../working_space/trimesh.h"
#include "../working_space/message_queue.h"

namespace framework
{
  const std::string get_postfix(const std::string & s)
  {
    auto i = s.find_last_of('.');
    if(i == std::string::npos)
      throw std::logic_error("can not get string postfix");
    return s.substr(i+1,s.size()-i-1);
  }

  void load_model_to_scene(const std::string & file, const std::string & viewer_name)
  {
    std::cout << "Load model." << std::endl;
    const std::string postfix = get_postfix(file);
    if(postfix == "obj") {
        framework::scene::smart_ptr* ptr = framework::scene::data_tree::get_instance().get_or_create_model("trim", framework::scene::model_type::TRIMESH);
        auto p = ptr->cast<framework::scene::trimesh>();
        if(p->load(file)){
            std::cout << "[warning] can not load triangle mesh" << std::endl;
          }
      }else if(postfix == "dxf"){
        framework::scene::smart_ptr* ptr = framework::scene::data_tree::get_instance().get_or_create_model("dxf", framework::scene::model_type::TRIMESH);
        auto p = ptr->cast<framework::scene::trimesh>();
        if(p->load(file)){
            std::cout << "[warning] can not load triangle mesh" << std::endl;
          }
      }

    app::get_instance().get_scene_view(viewer_name).post_update();
    app::get_instance().get_scene_view(viewer_name).wait_to_clear_message_queue();
    app::get_instance().get_scene_view(viewer_name).getCameraManipulator()->home(1.0);
  }
}
