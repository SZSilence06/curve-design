#include "state_select_vertex.h"
#include "../working_space_render/scene_view.h"
#include "../working_space/data_tree.h"
#include "../working_space/trimesh.h"
#include "../working_space/sphere.h"
#include <GL/glu.h>
#include "../common/util.h"
#include "../common/osg_util.h"
#include "../globals/geometry.h"
#include "../app/app.h"
#include "../globals/GlobalData.h"
#include "curve_operand_helper.h"

using namespace zjucad::matrix;

event_interface::event_return state_select_vertex::on_gui_event(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    auto view = dynamic_cast<framework::render::working_space_scene_view*>(aa.asView());
    assert(view->getName() == fsm_name_);

    switch(ea.getEventType())
    {
    case osgGA::GUIEventAdapter::RELEASE:
        switch(ea.getButton())
        {
        case osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON:
            pickVertex(view, ea.getX(), ea.getY());
            break;
        }
        break;
    case osgGA::GUIEventAdapter::KEYDOWN:
        switch(ea.getKey())
        {
        case osgGA::GUIEventAdapter::KEY_Delete:
            deleteVertex(view, ea.getX(),ea.getY());
            break;
        }
    }

    return event_interface::event_return("", false);
}

event_interface::event_return state_select_vertex::on_button_click(const std::string &button_name)
{
    return event_interface::event_return("", false);
}

event_interface::event_return state_select_vertex::on_cevent(const std::string &event_name, const boost::any &param)
{
    return event_interface::event_return("", false);
}

class hit_record_less
{
public:
  bool operator()(GLuint *a, GLuint *b) {
    return a[1]<b[1];
  }
};

matrixr_t state_select_vertex::osg_vec_to_matrix(osg::Vec3 vec)
{
    matrixr_t result(3,1);
    result[0] = vec.x();
    result[1] = vec.y();
    result[2] = vec.z();
    return result;
}

void state_select_vertex::pickVertex(framework::render::working_space_scene_view* view, double x, double y)
{
    auto& dataTree = framework::scene::data_tree::get_instance();
    framework::scene::trimesh* triangle_mesh;
    for(auto iter = dataTree.cbegin(); iter != dataTree.cend(); ++iter)
    {
        if((*iter->second)->get_model_type() == framework::scene::model_type::TRIMESH)
        {
            triangle_mesh = iter->second->cast<framework::scene::trimesh>();
            break;                //Only supports one mesh now
        }
    }

    const matrix<double> &vertex = triangle_mesh->get_mesh().node_;
    const matrix<size_t> &triangle = triangle_mesh->get_mesh().mesh_;

    auto camera = view->getCamera();
    osg::Vec3 eye,lookAt,up;
    double fov,aspect,znear,zfar;
    camera->getProjectionMatrixAsPerspective(fov,aspect,znear,zfar);
    camera->getViewMatrixAsLookAt(eye,lookAt,up);

    auto viewport = camera->getViewport();

    int picked_vertex = pick_mesh_vertex(vertex, triangle, osg_vec_to_matrix(eye), osg_vec_to_matrix(lookAt),
                                         osg_vec_to_matrix(up), fov, x, y, viewport->width(), viewport->height(),
                                         triangle_mesh->get_average_edge_length() / 5);

    if(picked_vertex >= 0)
    {
        add_control_point(picked_vertex);

        std::cout << "Picked vertex " << picked_vertex << "." << std::endl;

        curve_operand_helper::get_instance()->update_curve();
    }
    else
    {
        std::cout<< "No Pick." <<std::endl;
    }
}

void state_select_vertex::deleteVertex(framework::render::working_space_scene_view *view, double x, double y)
{
    auto& dataTree = framework::scene::data_tree::get_instance();
    framework::scene::trimesh* triangle_mesh;
    for(auto iter = dataTree.cbegin(); iter != dataTree.cend(); ++iter)
    {
        if((*iter->second)->get_model_type() == framework::scene::model_type::TRIMESH)
        {
            triangle_mesh = iter->second->cast<framework::scene::trimesh>();
            break;                //Only supports one mesh now
        }
    }

    const matrix<double> &vertex = triangle_mesh->get_mesh().node_;
    const matrix<size_t> &triangle = triangle_mesh->get_mesh().mesh_;

    auto camera = view->getCamera();
    osg::Vec3 eye,lookAt,up;
    double fov,aspect,znear,zfar;
    camera->getProjectionMatrixAsPerspective(fov,aspect,znear,zfar);
    camera->getViewMatrixAsLookAt(eye,lookAt,up);

    auto viewport = camera->getViewport();

    int picked_vertex = pick_mesh_vertex(vertex, triangle, osg_vec_to_matrix(eye), osg_vec_to_matrix(lookAt),
                                         osg_vec_to_matrix(up), fov, x, y, viewport->width(), viewport->height(),
                                         triangle_mesh->get_average_edge_length() / 3);

    if(picked_vertex >= 0)
    {
        remove_control_point(picked_vertex);

        std::cout<<"Deselect vertex " << picked_vertex << "." <<std::endl;

        curve_operand_helper::get_instance()->update_curve();
    }
}

void state_select_vertex::add_control_point(size_t id)
{
    auto globalData = GlobalData::getInstance();

    auto& control_points = globalData->control_points_;

    for(int i = 0; i < control_points.size(); i++)
    {
        if(control_points[i] == id)
        {
            return;    //Already exists
        }
    }
    control_points.push_back(id);
}

void state_select_vertex::remove_control_point(size_t id)
{
    auto globalData = GlobalData::getInstance();

    auto& control_points = globalData->control_points_;

    for(auto iter = control_points.begin(); iter != control_points.end(); ++iter)
    {
        if(*iter == id)
        {
            control_points.erase(iter);
            return;
        }
    }
}
