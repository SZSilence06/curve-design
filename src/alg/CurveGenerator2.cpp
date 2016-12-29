#include "CurveGenerator2.h"
#include "GeodesicGenerator.h"
#include "curve_interp.h"
#include "../globals/geometry.h"
#include "../globals/debug_util.h"
#include "projection.h"
#include <time.h>

CurveGenerator2::CurveGenerator2(const Mesh &mesh) : mesh(mesh)
{

}

bool CurveGenerator2::compute_curve(const std::vector<size_t>& control_points, matrixr_t &out, bool is_loop)
{
    initialize(control_points, is_loop);

    while(!is_finished())
    {
        smooth();
    }

    out.resize(3, curve.size());
    for(int i = 0 ; i < curve.size(); i++)
    {
        out(colon(), i) = curve[i].bary;
    }
    return true;
}

void CurveGenerator2::smooth()
{

}

void CurveGenerator2::initialize(const std::vector<size_t>& control_points, bool is_loop)
{
    init_geodesic(control_points, is_loop);
    init_best_curve(control_points, is_loop);
}

void CurveGenerator2::init_geodesic(const std::vector<size_t>& control_points, bool is_loop)
{
    curve.clear();

    auto& vertices = mesh.getVertices();
    auto& triangles = mesh.getTriangles();
    auto& vn = mesh.getVerticesNormals();
    auto& fn = mesh.getFaceNormals();

    GeodesicGenerator geodesic_generator(mesh);
    std::vector<int> geodesic;
    geodesic_generator.generateGeodesic(control_points, is_loop, geodesic);

    matrixr_t bary = zeros<real_t>(3, vertices.size(2));
    for(int i = 0; i < triangles.size(2); i++){
        bary(colon(), triangles(colon(), i)) = eye<real_t>(3);
        bary(2, triangles(colon(), i)) = i;
    }

    matrixr_t bary_geodesic(3, geodesic.size());
    matrixr_t normal_geodesic(3, geodesic.size());
    for(int i = 0; i < geodesic.size(); i++)
    {
        bary_geodesic(colon(), i) = bary(colon(), geodesic[i]);
        normal_geodesic(colon(), i) = vn(colon(), geodesic[i]);
    }

    matrixr_t Q,QN;
    matrixs_t control_point_pos;
    curve_interp(vertices, triangles, bary_geodesic, 0, 0, mesh.getAverageEdgeLength() / 5,
                 Q, control_point_pos, is_loop);
    matrixr_t projected_Q(3, Q.size(2));
    QN.resize(3, Q.size(2));

    for(int i = 0; i < control_point_pos.size() - 1; i++)
    {
        for(int j = control_point_pos[i]; j < control_point_pos[i+1]; j++)
        {
            QN(colon(), j) = normal_geodesic(colon(), i);
        }
    }
    QN(colon(), QN.size(2) - 1) = normal_geodesic(colon(), geodesic.size() - 1);

    for(int i = 0 ; i < Q.size(2); i++)
    {
        matrixr_t coor = Q(colon(), i);
        matrixr_t projected(3, 1);

        project(vertices, triangles, fn, coor, QN(colon(), i), projected);

        projected_Q(colon(), i) = projected;
    }

    for(int i = 0; i < projected_Q.size(2); i++)
    {
        Point point;
        point.bary = projected_Q(colon(), i);
        curve.push_back(point);
    }

    for(int i = 0 ; i < control_point_pos.size(2); i++)
    {
        curve[control_point_pos[i]].is_control_point = true;
    }
}

void CurveGenerator2::init_best_curve(const std::vector<size_t>& control_points, bool is_loop)
{
    best_curve.clear();

    auto& vertices = mesh.getVertices();
    auto& triangles = mesh.getTriangles();
    auto& vn = mesh.getVerticesNormals();
    auto& fn = mesh.getFaceNormals();

    matrixr_t bary = zeros<real_t>(3, vertices.size(2));
    for(int i = 0; i < triangles.size(2); i++){
        bary(colon(), triangles(colon(), i)) = eye<real_t>(3);
        bary(2, triangles(colon(), i)) = i;
    }

    matrixr_t bary_control_points(3, control_points.size());
    for(int i = 0; i < control_points.size(); i++)
    {
        bary_control_points(colon(), i) = bary(colon(), control_points[i]);
    }

    matrixr_t Q;
    matrixs_t control_point_pos;
    curve_interp(vertices, triangles, bary_control_points, 0, 0,  mesh.getAverageEdgeLength() / 5,
                 Q, control_point_pos, is_loop);

    for(int i = 0; i < Q.size(2); i++)
    {
        Point point;
        point.position = Q(colon(), i);
        best_curve.push_back(point);
    }

    for(int i = 0; i < control_point_pos.size(); i++)
    {
        best_curve[control_point_pos[i]].is_control_point = true;
    }
}

bool CurveGenerator2::is_finished()
{
    return false;
}
