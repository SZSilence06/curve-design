#pragma once

#include "Mesh.h"

class CurveGenerator
{
public:
    struct Point
    {
        int a, b;
        double t;
        double desiredCurvature;
        double lastCurvature;
        bool is_control_point = false;
        std::vector<int> control_points;
    };

    struct CriticalPointInfo
    {
        int move_to_index;
        std::vector<int> points;
    };

    typedef std::vector<Point> Curve;

private:
     Mesh& mesh;
     Curve curve;
     double t;
     double error_percentage;
     int current_index;

     double desired_mean_curvature;

     std::vector< std::vector<size_t> > vertex_neighbours;

public:
     bool initialize(std::vector<size_t> &control_points, bool is_loop);

     matrixr_t getCoordinate(Point p);
     bool isVertex(Point p);
     int getVertex(Point p);
     int getAnotherVertex(Point p);

     bool isFinished();
     void smooth();
     void handlePoint(int point_index);

     bool inSameFace(const Point& a, const Point& b, const Point& c);
     bool onSameEdge(const Point& a, const Point& b);
     int getCommonVertex(const Point& a, const Point& b);
     void push_unique(std::vector<int>& v, int a);

     void relocate(const matrixr_t& polar_minus, const matrixr_t& polar_plus,
                   const matrixr_t& polar_p2, int p2, Point& p);
     int split(int point_index);
     double computeLambda(const matrixr_t& polar_plus, const matrixr_t& polar_minus,
                          const matrixr_t& polar_p2, double theta);
     double computeCurvature(int point_index);
     void selectNeighbours(const matrixr_t& expMap, const std::vector<size_t>& neighbours, int vert,
                           Point plus, Point minus, std::vector<size_t>& N1, std::vector<size_t>& N2);

     void normalizeNeighbours(int bound, std::vector<size_t>& neighbours);

     void getPolar(Point p, int vert, const std::vector<size_t>& neighbours, const matrixr_t& expMap,
                   matrixr_t &polar);

     matrixr_t getExpMap(int vert, const std::vector<size_t>& neighbours);
     std::vector<Point> getSplitResult(const matrixr_t& expMap, const std::vector<size_t>& neighbours,
                                       const std::vector<size_t>& N, Point p,
                                       const matrixr_t& polar_plus, const matrixr_t polar_minus);
     double computeSplitLength(Point plus, Point minus, std::vector<Point>& split_result);
     double computeLength(Curve curve);
     double computeMeanCurvature(const CriticalPointInfo& info);

     void reverse(std::vector<size_t>& neighbours);

     void handleCriticalVertices();
     std::vector<CriticalPointInfo> findCriticalPoints();

     std::vector<int> merge(const std::vector<int> &a, const std::vector<int> &b);

public:
     CurveGenerator(Mesh& mesh);

     bool computeCurve(std::vector<size_t>& control_points, bool is_loop, double t, double error_percentage,
                       matrixr_t& outCurve);
};
