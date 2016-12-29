#pragma once

#include "Mesh.h"

class GeodesicGenerator
{
public:
    struct EdgeNode{
        int dest;
        double length;
    };

private:
    const Mesh& mesh;
    std::vector<std::vector<EdgeNode> > adj_table;
    std::vector<bool> used;

private:
    void buildAdjTable();
    bool findShortestPath(int start, int end, std::vector<int>& shortest_path);

public:
    GeodesicGenerator(const Mesh& mesh) : mesh(mesh) {}
    virtual ~GeodesicGenerator() {}

    bool generateGeodesic(const std::vector<size_t>& control_points, bool is_loop, std::vector<int>& geodesic);
};
