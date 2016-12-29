#include "GeodesicGenerator.h"
#include <limits>
#include <queue>

struct MinDist      //used for dijkstra
{
    int index;
    double dist;
};

void GeodesicGenerator::buildAdjTable()
{
    adj_table.clear();
    auto& vertices = mesh.getVertices();
    auto half_edge_mesh = mesh.getHalfEdgeMesh();
    auto verts = half_edge_mesh.verts();
    auto vert = verts.begin();

    for(int i = 0; i < vertices.size(2); i++)
    {
        auto neighbours = mesh.findOneRingVertices((itrc_vert_t)vert);

        std::vector<GeodesicGenerator::EdgeNode> vertNode;
        for(int j = 0 ; j < neighbours.size(); j++)
        {
            GeodesicGenerator::EdgeNode edge;
            edge.dest = neighbours[j];
            edge.length = norm(vertices(colon(), i) - vertices(colon(), neighbours[j]));
            vertNode.push_back(edge);
        }
        adj_table.push_back(vertNode);

        ++vert;
    }
}

bool GeodesicGenerator::generateGeodesic(const std::vector<size_t>& control_points, bool is_loop,
                                         std::vector<int>& geodesic)
{
    buildAdjTable();

    auto& vertices = mesh.getVertices();

    used.clear();
    for(int i = 0; i < vertices.size(2); i++)
    {
        used.push_back(false);
    }

    for(int i = 0; i + 1 < control_points.size(); i++)
    {
        int start = control_points[i];
        int end = control_points[i+1];

        if(findShortestPath(end, start, geodesic) == false)
        {
            return false;
        }
    }

    if(is_loop)
    {
        if(findShortestPath(control_points[0], control_points[control_points.size()-1], geodesic) == false)
        {
            return false;
        }
        geodesic.push_back(control_points[0]);
    }
    else
    {
        geodesic.push_back(control_points[control_points.size() - 1]);
    }
    return true;
}

struct cmp{
    bool operator()(MinDist a,MinDist b){
        return a.dist > b.dist;
    }
};

bool GeodesicGenerator::findShortestPath(int start, int end, std::vector<int>& shortest_path)
{
    std::vector<bool> visited;
    std::vector<MinDist> minDist;
    std::vector<int> prev;

    auto& vertices = mesh.getVertices();

    for(int i = 0; i < vertices.size(2); i++)
    {
        MinDist vert;
        vert.index = i;
        vert.dist = std::numeric_limits<double>::max();
        visited.push_back(false);
        minDist.push_back(vert);
        prev.push_back(-1);
    }

    minDist[start].dist = 0;
    used[start] = used[end] = false;

    std::priority_queue<MinDist, vector<MinDist>, cmp> queue;
    queue.push(minDist[start]);

    while(!queue.empty())
    {
        MinDist vert_min = queue.top();
        queue.pop();
        if(vert_min.index == end)
        {
            break;
        }
        if(visited[vert_min.index] || used[vert_min.index])
        {
            continue;
        }
        visited[vert_min.index] = true;
        vector<EdgeNode>& adj = adj_table[vert_min.index];
        for(int i = 0; i < adj.size(); i++)
        {
            EdgeNode edge = adj[i];
            if(!visited[edge.dest] && !used[edge.dest] && minDist[edge.dest].dist
                    > minDist[vert_min.index].dist + edge.length)
            {
                minDist[edge.dest].dist = minDist[vert_min.index].dist + edge.length;
                prev[edge.dest] = vert_min.index;
                queue.push(minDist[edge.dest]);
            }
        }
    }

    for(int i = end; i!= start; i = prev[i])
    {
        shortest_path.push_back(i);
        used[i] = true;
        if(prev[i] < 0)   //start and end are not connected
        {
            return false;
        }
    }
    return true;
}
