#pragma once

#include "Mesh.h"

class CurveGenerator2
{
public:
    struct Point
    {
        matrixr_t position;
        matrixr_t bary;
        bool is_control_point = false;
    };

    typedef std::vector<Point> Curve;

private:
    const Mesh& mesh;
    Curve curve;
    Curve best_curve;

private:
    void initialize(const std::vector<size_t>& control_points, bool is_loop);
    void init_geodesic(const std::vector<size_t>& control_points, bool is_loop);
    void init_best_curve(const std::vector<size_t>& control_points, bool is_loop);

    bool is_finished();
    void smooth();

public:
    CurveGenerator2(const Mesh& mesh);

    bool compute_curve(const std::vector<size_t>& control_points, matrixr_t& out, bool is_loop);
};
