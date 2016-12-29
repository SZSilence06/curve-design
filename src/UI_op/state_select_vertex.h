#pragma once


#include "fsm.h"
#include "../working_space_render/scene_view.h"
#include <zjucad/matrix/matrix.h>

using namespace zjucad::matrix;

class state_select_vertex : public hj::fsm::state<fsm_glwnd_interface, state_key, boost::any>
{
public:
    state_select_vertex(const std::string fsm_name) : fsm_name_(fsm_name) {}

    virtual ~state_select_vertex() {}

    virtual state_key key(void) const override { return "select_vertex"; }

    virtual event_interface::event_return  on_gui_event(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa) override;
    virtual event_interface::event_return  on_button_click(const std::string &button_name) override;
    virtual event_interface::event_return  on_cevent(const std::string &event_name, const boost::any &param) override;

private:
    std::string fsm_name_;
    int picked_point_count_ = 0;

private:
    void pickVertex(framework::render::working_space_scene_view* view, double x, double y);
    void deleteVertex(framework::render::working_space_scene_view* view, double x, double y);

    osg::Vec3 generateRayDir(osg::Vec3 eye, osg::Vec3 lookAt, osg::Vec3 up, double fov,
                     double x, double y, double width, double height);
    bool compute_intersection(osgViewer::Viewer *viewer, double x, double y, osg::Vec3 &intersect_point);

    void add_control_point(size_t id);
    void remove_control_point(size_t id);

    matrix<double> osg_vec_to_matrix(osg::Vec3 vec);
};
