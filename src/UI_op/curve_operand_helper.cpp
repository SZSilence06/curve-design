#include "curve_operand_helper.h"
#include "../globals/GlobalData.h"
#include "../globals/debug_util.h"
#include "../working_space_render/scene_view.h"
#include "../working_space/trimesh.h"
#include "../working_space/sphere.h"
#include "../working_space/line.h"
#include "../working_space/data_tree.h"
#include "../alg/GeodesicGenerator.h"
#include "../alg/CurveGenerator.h"
#include "../alg/CurveGenerator2.h"
#include "../common/osg_util.h"
#include "../app/app.h"

curve_operand_helper* curve_operand_helper::get_instance()
{
    static curve_operand_helper instance_;

    return &instance_;
}

void curve_operand_helper::clear_curve()
{
    auto& dataTree = framework::scene::data_tree::get_instance();

    for(auto iter = dataTree.cbegin(); iter != dataTree.cend(); ++iter)
    {
        auto model = (*iter->second);
        std::string name = model->get_name();
        if(name.substr(0,5) == "curve" || name.substr(0, 13) == "control_point")
        {
            model->reset_state(framework::scene::node_state_type::DELETED);
        }
    }

    auto& scene_view = app::get_instance().get_scene_view("master_3d");
    scene_view.post_update();
    scene_view.wait_to_clear_message_queue();
}

void curve_operand_helper::fit_curve(bool is_loop)
{
    auto globalData = GlobalData::getInstance();
    auto& control_points = globalData->control_points_;

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

    const matrix<double> &vertices = triangle_mesh->get_mesh().node_;
    const matrix<size_t> &triangles = triangle_mesh->get_mesh().mesh_;

    Mesh mesh(vertices, triangles);

    matrixr_t curve;
    //CurveGenerator2 curve_generator(mesh);
    //curve_generator.compute_curve(control_points, curve, false);

    CurveGenerator curve_generator(mesh);
    DebugTimer timer("timer 1");
    timer.start();
    curve_generator.computeCurve(control_points, is_loop, 0.1, 0.01, curve);
    timer.end();

    clear_curve();

    for(int i = 0; i < curve.size(2); i++)
    {
        matrixr_t point;
        point = curve(colon(), i);

        auto node = dataTree.get_or_create_model(std::string("curve") + std::to_string(i),
                                                 framework::scene::model_type::SPHERE);
        auto sphere_node = node->cast<framework::scene::sphere>();

        sphere_node->setCenter(point[0], point[1], point[2]);
        sphere_node->setRadius(triangle_mesh->get_average_edge_length() / 5);
        sphere_node->setColor(0,1,0);
        sphere_node->reset_state(framework::scene::node_state_type::NEW_ADDED);
    }

    /*
    //draw line
    if(curve.size(2) > 1)
    {
        auto line_node_on_tree = dataTree.get_or_create_model(std::string("curve_line"),framework::scene::model_type::LINE);
        auto line_node = line_node_on_tree->cast<framework::scene::line>();

        line_node->setPoints(curve);
        line_node->setWidth(triangle_mesh->get_average_edge_length() / 5);
        line_node->setColor(0,1,0);
        line_node->reset_state(framework::scene::node_state_type::NEW_ADDED);
    }*/


    auto& scene_view = app::get_instance().get_scene_view("master_3d");
    scene_view.post_update();
    scene_view.wait_to_clear_message_queue();

    draw_control_points(triangle_mesh);
}

void curve_operand_helper::draw_control_points(const framework::scene::trimesh* triangle_mesh)
{
    auto globalData = GlobalData::getInstance();
    auto& control_points = globalData->control_points_;
    auto& dataTree = framework::scene::data_tree::get_instance();

    auto& vertex = triangle_mesh->get_mesh().node_;

    for(int i = 0; i < control_points.size(); i++)
    {
        auto node = dataTree.get_or_create_model(std::string("control_point ") + std::to_string(control_points[i]),
                                                 framework::scene::model_type::SPHERE);
        auto sphere_node = node->cast<framework::scene::sphere>();

        if(sphere_node->get_node_state() == framework::scene::node_state_type::UPDATED)
        {
            return;    //Already in scene, so return
        }
        sphere_node->setCenter(vertex(0, control_points[i]), vertex(1, control_points[i]), vertex(2, control_points[i]));
        sphere_node->setRadius(triangle_mesh->get_average_edge_length() / 4.9);
        sphere_node->setColor(1,0,0);
        sphere_node->reset_state(framework::scene::node_state_type::NEW_ADDED);
    }

    auto& scene_view = app::get_instance().get_scene_view("master_3d");
    scene_view.post_update();
    scene_view.wait_to_clear_message_queue();
}

void curve_operand_helper::update_curve()
{
    clear_curve();

    fit_curve(false);
}
