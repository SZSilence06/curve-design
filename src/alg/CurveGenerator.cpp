#include "CurveGenerator.h"
#include "GeodesicGenerator.h"
#include "../globals/geometry.h"

CurveGenerator::CurveGenerator(Mesh &mesh) : mesh(mesh)
{
    auto& halfEdgeMesh = mesh.getHalfEdgeMesh();
    for(auto vert = halfEdgeMesh.verts().begin(); vert != halfEdgeMesh.verts().end(); ++vert)
    {
        std::vector<size_t> result;
        auto edge = vert->edge();
        do{
            result.push_back(edge->oppo()->vert()->id_);
            edge = edge->next()->oppo();
        }while(edge != vert->edge());

        vertex_neighbours.push_back(result);
    }
}

bool CurveGenerator::computeCurve(std::vector<size_t> &control_points, bool is_loop, double t,
                                  double error_percentage, matrixr_t &outCurve)
{
    this->t = t;
    this->error_percentage = error_percentage;
    if(initialize(control_points, is_loop) == false)
    {
        return false;
    }

    int i = 0;
    while (true)
    {
        i++;
        smooth();     
        if(isFinished() || i >= 100)
        {
            std::cout << "Finished smoothing after " << i << " iterations." << std::endl;
            break;
        }
        handleCriticalVertices();
    }

    outCurve = matrixr_t(3, curve.size());
    for(int i = 0; i < curve.size(); i++)
    {
        outCurve(colon(), i) = getCoordinate(curve[i]);
    }

    return true;
}

bool CurveGenerator::initialize(std::vector<size_t> &control_points, bool is_loop)
{
    GeodesicGenerator generator(mesh);
    std::vector<int> geodesic;

    if(generator.generateGeodesic(control_points, is_loop, geodesic) == false)
    {
        return false;
    }

    curve.clear();
    for(int i = 0; i < geodesic.size(); i++)
    {
        Point p;
        p.a = geodesic[i];
        p.b = -1;
        p.t = 1;

        for(int j = 0; j < control_points.size(); j++)
        {
            if(control_points[j] == p.a)
            {
                p.is_control_point = true;
                p.control_points.push_back(control_points[j]);
            }
        }

        curve.push_back(p);
    }

    desired_total_curvature = 0;

    for(int i = 1; i < curve.size() - 1; i++)
    {
        double curvature = computeCurvature(i);
        curve[i].desiredCurvature = curvature * t;
        curve[i].lastCurvature = curve[i].desiredCurvature;
        desired_total_curvature += curve[i].desiredCurvature;
    }

    return true;
}

void CurveGenerator::smooth()
{
    for(current_index = 1; current_index < curve.size() - 1; current_index++)
    {
        handlePoint(current_index);
    }
}

bool CurveGenerator::onSameEdge(const Point &a, const Point &b)
{
    /*if(isVertex(a))
    {
        return b.a == getVertex(a) || b.b == getVertex(a);
    }
    if(isVertex(b))
    {
        return a.a == getVertex(b) || a.b == getVertex(b);
    }*/
    return (a.a == b.a && a.b == b.b) || (a.b == b.a && a.a == b.b);
}

void CurveGenerator::push_unique(std::vector<int> &v, int a)
{
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i] == a)
        {
            return;
        }
    }
    v.push_back(a);
}

bool CurveGenerator::inSameFace(const Point& a, const Point& b, const Point& c)
{
    std::vector<int> appeared_vertices;
    if(isVertex(a))
    {
        push_unique(appeared_vertices, a.a);
    }
    else
    {
        push_unique(appeared_vertices, a.a);
        push_unique(appeared_vertices, a.b);
    }
    if(isVertex(b))
    {
        push_unique(appeared_vertices, b.a);
    }
    else
    {
        push_unique(appeared_vertices, b.a);
        push_unique(appeared_vertices, b.b);
    }
    if(isVertex(c))
    {
        push_unique(appeared_vertices, c.a);
    }
    else
    {
        push_unique(appeared_vertices, c.a);
        push_unique(appeared_vertices, c.b);
    }

    if(appeared_vertices.size() > 3)
    {
        return false;
    }

    if(appeared_vertices.size() == 2)
    {
        return true;
    }

    bool exist1 = false, exist2 = false;
    auto& neighbours = vertex_neighbours[appeared_vertices[0]];
    for(int i = 0; i < neighbours.size(); i++)
    {
        if(neighbours[i] == appeared_vertices[1])
        {
            exist1 = true;
        }
        if(neighbours[i] == appeared_vertices[2])
        {
            exist2 = true;
        }
    }
    if(!(exist1 && exist2))
    {
        return false;
    }

    bool exist3 = false, exist4 = false;
    auto& neighbours2 = vertex_neighbours[appeared_vertices[1]];
    for(int i = 0; i < neighbours2.size(); i++)
    {
        if(neighbours2[i] == appeared_vertices[0])
        {
            exist3 = true;
        }
        if(neighbours2[i] == appeared_vertices[2])
        {
            exist4 = true;
        }
    }
    if(!(exist3 && exist4))
    {
        return false;
    }
    return true;
}

int CurveGenerator::getCommonVertex(const Point &a, const Point &b)
{
    if(a.a == b.a)
    {
        return a.a;
    }
    if(a.a == b.b)
    {
        return a.a;
    }
    if(a.b == b.a)
    {
        return a.b;
    }
    if(a.b == b.b && a.b >= 0)
    {
        return a.b;
    }
    return -1;
}

void CurveGenerator::handlePoint(int point_index)
{
    Point& point = curve[point_index];

    if(point.is_control_point)
    {
        //return;
    }

    if(inSameFace(curve[point_index - 1], curve[point_index], curve[point_index + 1]))
    {
        curve[point_index - 1].is_control_point |= curve[point_index].is_control_point;
        if(curve[point_index].is_control_point)
        {
            curve[point_index - 1].control_points = merge(curve[point_index - 1].control_points,
                    curve[point_index].control_points);
        }

        curve[point_index + 1].is_control_point |= curve[point_index].is_control_point;
        if(curve[point_index].is_control_point)
        {
            curve[point_index + 1].control_points = merge(curve[point_index + 1].control_points,
                    curve[point_index].control_points);
        }

        auto iter = curve.begin() + point_index;
        curve.erase(iter);
        current_index --;

        while(current_index > 0 && inSameFace(curve[current_index-1], curve[current_index],
                                              curve[current_index+1]))
        {
            curve[point_index - 1].is_control_point |= curve[point_index].is_control_point;
            if(curve[point_index].is_control_point)
            {
                curve[point_index - 1].control_points = merge(curve[point_index - 1].control_points,
                        curve[point_index].control_points);
            }

            curve[point_index + 1].is_control_point |= curve[point_index].is_control_point;
            if(curve[point_index].is_control_point)
            {
                curve[point_index + 1].control_points = merge(curve[point_index + 1].control_points,
                        curve[point_index].control_points);
            }

            iter = curve.begin() + current_index;
            curve.erase(iter);
            current_index--;
        }
        return;
    }

    if(isVertex(point))
    {
        current_index += split(point_index);
        current_index--;
    }
    else
    {
        auto& neighbours = vertex_neighbours[point.a];
        matrixr_t expMap = getExpMap(point.a, neighbours);
        matrixr_t polar_plus, polar_minus, polar_p2;
        getPolar(curve[point_index - 1], point.a, neighbours, expMap, polar_minus);
        getPolar(curve[point_index + 1], point.a, neighbours, expMap, polar_plus);

        for(int i = 0; i < neighbours.size(); i++)
        {
            if(neighbours[i] == point.b)
            {
                polar_p2 = expMap(colon(), i);
            }
        }
        relocate(polar_minus, polar_plus, polar_p2, point.b, point);
    }
}

void CurveGenerator::relocate(const matrixr_t &polar_minus, const matrixr_t &polar_plus,
                              const matrixr_t &polar_p2, int p2, Point& p)
{
    auto& vertices = mesh.getVertices();

    //std::cout << "polar_plus" << std::endl << polar_plus << std::endl
    //          << "polar minus" << std::endl << polar_minus << std::endl
    //          << "polar_p2" << std::endl << polar_p2 << std::endl;

    double lambda;
    if(p.is_control_point == false)
    {
        lambda = 1;
        //computeLambda(polar_plus, polar_minus, polar_p2, PI - fabs(p.desiredCurvature));
    }
    else
    {
        lambda = 0.25f;
    }

    double theta_plus_p_p2 = fabs(polar_plus[1] - polar_p2[1]);
    if(theta_plus_p_p2 > PI)
    {
        theta_plus_p_p2 = 2 * PI - theta_plus_p_p2;
    }
    double plus_proj = polar_plus[0] * sin(theta_plus_p_p2);
    double p_proj_plus = polar_plus[0] * cos(theta_plus_p_p2);

    double theta_minus_p_p2 = fabs(polar_minus[1] - polar_p2[1]);
    if(theta_minus_p_p2 > PI)
    {
        theta_minus_p_p2 = 2 * PI - theta_minus_p_p2;
    }
    double minus_proj = polar_minus[0] * sin(theta_minus_p_p2);
    double p_proj_minus = polar_minus[0] * cos(theta_minus_p_p2);

    double edge_length = norm(vertices(colon(), p.a) - vertices(colon(), p2));
    double p_length = (1 - p.t) * edge_length;
    double t_minus = 1 - p_proj_minus / edge_length;
    double t_plus = 1 - p_proj_plus / edge_length;
    double t_new;

    //decide whether minus and plus are on diffrent sides of line segment pp2.
    double polar_bigger = polar_minus[1] > polar_plus[1] ? polar_minus[1] : polar_plus[1];
    double polar_smaller = polar_minus[1] < polar_plus[1] ? polar_minus[1] : polar_plus[1];
    double polar_bigger_2 = polar_bigger + PI;
    if(polar_bigger_2 > 2 * PI)
    {
        polar_bigger_2 -= 2 * PI;
    }
    double polar_smaller_2 = polar_smaller + PI;
    if(polar_smaller_2 > 2 * PI)
    {
        polar_smaller_2 -= 2 * PI;
    }

    bool on_different_side = false;
    bool on_different_side_1, on_different_side_2;

    if(polar_bigger - polar_smaller < PI)
    {
        on_different_side_1 = polar_p2[1] > polar_smaller && polar_p2[1] < polar_bigger;
    }
    else
    {
        on_different_side_1 = polar_p2[1] < polar_smaller || polar_p2[1] > polar_bigger;
    }
    if(polar_bigger_2 - polar_smaller_2 < PI)
    {
        on_different_side_2 = polar_p2[1] > polar_smaller_2 && polar_p2[1] < polar_bigger_2;
    }
    else
    {
        on_different_side_2 = polar_p2[1] < polar_smaller_2 || polar_p2[1] > polar_bigger_2;
    }
    on_different_side = on_different_side_1 || on_different_side_2;

    if(on_different_side)
    {
        //minus and plus are on diffrent sides of line segment pp2.
        double omega_plus = minus_proj / (minus_proj + plus_proj);
        double omega_minus = plus_proj / (minus_proj + plus_proj);
        t_new = (1 - lambda) * p.t + lambda * (omega_minus * t_minus + omega_plus * t_plus);
    }
    else
    {
        /*double omega_plus = minus_proj / (minus_proj - plus_proj);
        double omega_minus = plus_proj / (plus_proj - minus_proj);
        t_new = (1 - lambda) * p.t + lambda * (omega_minus * t_minus + omega_plus * t_plus);*/
        t_new = 1;
    }
    if(t_new < 0)
    {
        p.a = p.b;
        p.b = -1;
        t_new = 1;
    }
    else if(t_new >= 1)
    {
        t_new = 1;
        p.b = -1;
    }
    p.t = t_new;
}

int CurveGenerator::split(int point_index)
{
    Point p = curve[point_index];
    Point pplus = curve[point_index + 1];
    Point pminus = curve[point_index - 1];

    auto& vertices = mesh.getVertices();

    matrixr_t coorp = vertices(colon(), p.a);

    auto& neighbours = vertex_neighbours[p.a];
    matrixr_t expMap = getExpMap(p.a, neighbours);

    //std::cout << "expMap" << std::endl << expMap << std::endl;

    //compute polar coordinate of pplus,pminus
    matrixr_t polar_plus(2,1), polar_minus(2,1);
    getPolar(pplus, p.a, neighbours, expMap, polar_plus);
    getPolar(pminus, p.a, neighbours, expMap, polar_minus);

    std::vector<size_t> N1,N2;
    selectNeighbours(expMap, neighbours, p.a, pplus, pminus, N1, N2);

    auto split_result_1 = getSplitResult(expMap, neighbours, N1, p, polar_plus, polar_minus);
    auto split_result_2 = getSplitResult(expMap, neighbours, N2, p, polar_plus, polar_minus);;

    double length1 = computeSplitLength(pplus, pminus, split_result_1);
    double length2 = computeSplitLength(pplus, pminus, split_result_2);

    curve.erase(curve.begin() + point_index);
    if(length1 < length2)
    {
        int i = 0;
        for(auto iter = curve.begin() + point_index; i < split_result_1.size(); ++iter, ++i)
        {
            iter = curve.insert(iter, split_result_1[i]);
        }
        return split_result_1.size();
    }
    else
    {
        int i = 0;
        for(auto iter = curve.begin() + point_index; i < split_result_2.size(); ++iter, ++i)
        {
            iter = curve.insert(iter, split_result_2[i]);
        }
        return split_result_2.size();
    }
}

matrixr_t CurveGenerator::getExpMap(int vert, const std::vector<size_t>& neighbours)
{
    auto& vertices = mesh.getVertices();

    matrixr_t coorp = vertices(colon(), vert);

    matrixr_t expMap(2, neighbours.size());
    double theta = 0;
    for(int i = 0; i < neighbours.size(); i++)
    {
        int a = i;
        int b = (i+1) % neighbours.size();

        matrixr_t coora = vertices(colon(), neighbours[a]);
        matrixr_t coorb = vertices(colon(), neighbours[b]);
        matrixr_t pa = coora - coorp;
        matrixr_t pb = coorb - coorp;

        double angle = acos(dot(pa, pb) / (norm(pa) * norm(pb)));
        expMap(0, a) = norm(pa);
        expMap(1, a) = theta;
        theta += angle;
    }
    double ratio = 2 * PI / theta;
    for(int i = 0; i < neighbours.size(); i++)
    {
        expMap(1, i) *= ratio;
    }
    return expMap;
}

void CurveGenerator::selectNeighbours(const matrixr_t &expMap, const std::vector<size_t> &neighbours,
                                      int vert, Point plus, Point minus, std::vector<size_t> &N1,
                                      std::vector<size_t>& N2)
{
    int region = 0;
    int prev_neighbour = -1;
    int need_reverse_region;
    int bound[2] = {0, 0};

    //for test
    if(isVertex(plus))
    {
        assert(plus.b == -1);
    }
    if(isVertex(minus))
    {
        assert(minus.b == -1);
    }

    N1.clear();
    N2.clear();

    for(int i = 0; i < neighbours.size(); i++)
    {
        bool equals_plus = isVertex(plus) && getVertex(plus) == neighbours[i];
        bool equals_minus = (isVertex(minus) && getVertex(minus) == neighbours[i]);
        if(equals_plus || equals_minus)
        {
            if(region == 0)
            {
                bound[0] = N1.size();
            }
            else
            {
                bound[1] = N2.size();
            }
            if(equals_minus)
            {
                need_reverse_region = region;
            }
            else
            {
                need_reverse_region = !region;
            }
            region = !region;
            prev_neighbour = neighbours[i];             
            continue;
        }
        if(prev_neighbour >= 0)
        {
            if((plus.a == neighbours[i] && plus.b == prev_neighbour)
                    || (plus.b == neighbours[i] && plus.a == prev_neighbour))
            {
                if(region == 0)
                {
                    bound[0] = N1.size();
                }
                else
                {
                    bound[1] = N2.size();
                }
                region = !region;
                need_reverse_region = region;
            }
            if((minus.a == neighbours[i] && minus.b == prev_neighbour)
                    || (minus.b == neighbours[i] && minus.a == prev_neighbour))
            {
                if(region == 0)
                {
                    bound[0] = N1.size();
                }
                else
                {
                    bound[1] = N2.size();
                }
                need_reverse_region = region;
                region = !region;
            }
        }
        prev_neighbour = neighbours[i];

        if(region == 0)
        {
            N1.push_back(i);
        }
        else
        {
            N2.push_back(i);
        }
    }

    normalizeNeighbours(bound[0], N1);
    normalizeNeighbours(bound[1], N2);

    if(need_reverse_region == 0)
    {
        reverse(N1);
    }
    else if(need_reverse_region == 1)
    {
        reverse(N2);
    }
}

void CurveGenerator::normalizeNeighbours(int bound, std::vector<size_t> &neighbours)
{
    assert(bound >=0 && bound <= neighbours.size());
    std::vector<size_t> temp;
    for(int i = 0; i < bound; i++)
    {
        temp.push_back(neighbours[i]);
    }
    for(int i = bound; i < neighbours.size(); i++)
    {
        neighbours[i - bound] = neighbours[i];
    }
    for(int i = 0; i < temp.size(); i++)
    {
        neighbours[neighbours.size() - temp.size() + i] = temp[i];
    }
}

void CurveGenerator::reverse(std::vector<size_t>& neighbours)
{
    for(int i = 0; i < neighbours.size() / 2; i++)
    {
        auto temp = neighbours[i];
        neighbours[i] = neighbours[neighbours.size() - i - 1];
        neighbours[neighbours.size() - i - 1] = temp;
    }
}

std::vector<CurveGenerator::Point> CurveGenerator::getSplitResult(const matrixr_t &expMap, const std::vector<size_t>& neighbours,
                                                  const std::vector<size_t> &N, Point p,
                                                  const matrixr_t &polar_plus, const matrixr_t polar_minus)
{
    matrixr_t polar_minus_temp = polar_minus;
    std::vector<Point> result;
    for(int i = 0; i < N.size(); i++)
    {
        Point splited_point;
        splited_point.a = getVertex(p);
        splited_point.b = neighbours[N[i]];
        splited_point.desiredCurvature = p.desiredCurvature;
        splited_point.t = 1;
        splited_point.is_control_point = p.is_control_point;
        splited_point.control_points = p.control_points;

        relocate(polar_minus_temp, polar_plus, expMap(colon(), N[i]), splited_point.b, splited_point);

        if(isVertex(splited_point))
        {
            if(getVertex(p) == getVertex(splited_point))
            {
                result.push_back(splited_point);
                return result;
            }
        }

        result.push_back(splited_point);
        getPolar(splited_point, getVertex(p), neighbours, expMap, polar_minus_temp);
    }
    return result;
}

void CurveGenerator::getPolar(Point p, int vert, const std::vector<size_t>& neighbours, const matrixr_t& expMap,
                              matrixr_t &polar)
{
    polar = matrixr_t(2,1);
    matrixr_t a(2,1), b(2,1), c(2,1);
    for(int i = 0; i < neighbours.size(); i++)
    {
        if(p.a == neighbours[i] && p.b == vert)
        {
            polar[0] = p.t * expMap(0, i);
            polar[1] = expMap(1, i);
            return;
        }
        else if(p.b == neighbours[i] && p.a == vert)
        {
            polar[0] = (1 - p.t) * expMap(0, i);
            polar[1] = expMap(1, i);
            return;
        }
        else
        {
            if(p.a == neighbours[i])
            {
                a[0] = expMap(0, i) * cos(expMap(1, i));
                a[1] = expMap(0, i) * sin(expMap(1,           i));
            }
            else if(p.b == neighbours[i])
            {
                b[0] = expMap(0, i) * cos(expMap(1, i));
                b[1] = expMap(0, i) * sin(expMap(1, i));
            }
        }
    }
    c = p.t * a + (1 - p.t) * b;
    polar[0] = sqrt(c[0] * c[0] + c[1] * c[1]);
    polar[1] = get_2d_angle(c[0], c[1]);
}

double CurveGenerator::computeCurvature(int point_index)
{
    Point point = curve[point_index];
    assert(point_index > 0 && point_index < curve.size() - 1);
    Point plus = curve[point_index + 1];
    Point minus = curve[point_index - 1];

    matrixr_t coor_plus = getCoordinate(plus);
    matrixr_t coor_minus = getCoordinate(minus);
    matrixr_t coor_point = getCoordinate(point);

    matrixr_t a = coor_plus - coor_point;
    matrixr_t b = coor_minus - coor_point;

    double beta = acos(dot(a,b) / (norm(a) * norm(b)));
    double theta;
    if(isVertex(point))
    {
        theta = mesh.computeVertexAngle(point.a);
    }
    else
    {
        theta = 2 * PI;
    }

    return PI - (2 * PI * beta / theta);
}

double CurveGenerator::computeLambda(const matrixr_t &polar_plus, const matrixr_t &polar_minus,
                                     const matrixr_t &polar_p2, double theta)
{
    matrixr_t coor_plus(2,1);
    matrixr_t coor_minus(2,1);
    matrixr_t coor_p2(2,1);

    coor_plus[0] = polar_plus[0] * cos(polar_plus[1]);
    coor_plus[1] = polar_plus[0] * sin(polar_plus[1]);
    coor_minus[0] = polar_minus[0] * cos(polar_minus[1]);
    coor_minus[1] = polar_minus[0] * sin(polar_minus[1]);
    coor_p2[0] = polar_p2[0] * cos(polar_p2[1]);
    coor_p2[1] = polar_p2[0] * sin(polar_p2[1]);

    matrixr_t minus_plus  = coor_plus - coor_minus;

    double u, gamma;

    double theta_p_minus_plus = acos(dot(-coor_minus, minus_plus) /
                                     (polar_minus[0] * norm(minus_plus)));
    if(theta_p_minus_plus > PI / 2)   //proj,minus,star,plus
    {
        double projp = -polar_minus[0] * cos(theta_p_minus_plus);
        double theta_minus_p_proj = PI / 2 - (PI - theta_p_minus_plus);
        double minus_proj = polar_minus[0] * sin(theta_minus_p_proj);

        double theta_minus_p_star = fabs(polar_p2[1] - polar_minus[1]);
        if(theta_minus_p_star > PI)
        {
            theta_minus_p_star = 2 * PI - theta_minus_p_star;
        }
        double theta_proj_p_star = theta_minus_p_proj + theta_minus_p_star;
        double proj_star = projp * tan(theta_proj_p_star);
        u = proj_star - minus_proj;
        gamma = PI / 2 + theta_proj_p_star;
    }
    else
    {
        double projp = polar_minus[0] * sin(theta_p_minus_plus);
        double theta_minus_p_proj = PI / 2 - theta_p_minus_plus;
        double minus_proj = polar_minus[0] * sin(theta_minus_p_proj);
        double theta_minus_p_star = fabs(polar_p2[1] - polar_minus[1]);
        if(theta_minus_p_star > PI)
        {
            theta_minus_p_star = 2 * PI - theta_minus_p_star;
        }
        if(theta_minus_p_star > theta_minus_p_proj)  //minus,proj,star,plus
        {
            double theta_proj_p_star = theta_minus_p_star - theta_minus_p_proj;
            double proj_star = projp * tan(theta_proj_p_star);
            u = minus_proj + proj_star;
            gamma = PI / 2 + theta_proj_p_star;
        }
        else
        {
            double theta_proj_p_star = theta_minus_p_proj - theta_minus_p_star;
            double proj_star = projp * tan(theta_proj_p_star);
            u = minus_proj - proj_star;
            gamma = PI / 2 - theta_proj_p_star;
        }
    }

    double alpha = 1 + 1 / (tan(gamma) * tan(gamma));
    double L = norm(minus_plus);
    double T = tan(theta - PI);
    double beta = L / T + (L - 2 * u) / tan(gamma);

    double sqrt_value = beta * beta / (4 * alpha * alpha) + u * (L - u) / alpha;
    if(fabs(sqrt_value) < 1e-3)
    {
        sqrt_value = 0;
    }
    assert(sqrt_value >= 0);
    double ystar = beta / (2 * alpha) + sqrt(sqrt_value);

    double theta_for_cross = acos(dot(coor_minus, minus_plus) / (norm(coor_minus) * norm(minus_plus)));
    double d = fabs(norm(coor_minus) * norm(minus_plus) * sin(theta_for_cross)) / L;
    assert(d != 0);
    return 1 - ystar / d;
}

double CurveGenerator::computeSplitLength(Point plus, Point minus, std::vector<Point> &split_result)
{
    Curve curve;
    curve.push_back(minus);
    for(int i = 0; i < split_result.size(); i++)
    {
        curve.push_back(split_result[i]);
    }
    curve.push_back(plus);

    return computeLength(curve);
}

double CurveGenerator::computeLength(Curve curve)
{
    if(curve.size() < 1)
    {
        return 0;
    }
    matrixr_t coor_prev = getCoordinate(curve[0]);
    matrixr_t coor_current;
    double length = 0;
    for(int i = 1; i < curve.size(); i++)
    {
        coor_current = getCoordinate(curve[i]);
        length += norm(coor_current - coor_prev);
        coor_prev = coor_current;
    }

    return length;
}

bool CurveGenerator::isFinished()
{   
    bool result = true;
    double total_curvature = 0;
    for(int i = 1; i < curve.size() - 1; i++)
    {
        if(curve[i].is_control_point)
        {
            Point& p = curve[i];
            for(int j = 0; j < p.control_points.size(); j++)
            {
                if(mesh.howManyRing(p.a ,p.control_points[j]) > 2 ||
                        (p.b >= 0 && mesh.howManyRing(p.b ,p.control_points[j]) > 2))
                {
                    return true;
                }
            }
        }

        double curvature = computeCurvature(i);
        total_curvature += curvature;
        if( fabs(curvature - curve[i].lastCurvature) / curve[i].lastCurvature > error_percentage)
        {
            result = false;
        }
        curve[i].lastCurvature = curvature;
    }
    if(desired_total_curvature == 0)
    {
        return true;
    }
    if(fabs(total_curvature - desired_total_curvature) / desired_total_curvature < error_percentage)
    {
        return true;
    }
    return result;
}

bool CurveGenerator::isVertex(Point p)
{
    return p.t == 0 || p.t == 1;
}

int CurveGenerator::getVertex(Point p)
{
    if(p.t == 0)
    {
        return p.b;
    }
    return p.a;
}

int CurveGenerator::getAnotherVertex(Point p)
{
    if(p.t == 0)
    {
        return p.a;
    }
    return p.b;
}

matrixr_t CurveGenerator::getCoordinate(Point p)
{
    auto& vertices = mesh.getVertices();

    if(isVertex(p))
    {
        return vertices(colon(), p.a);
    }
    return vertices(colon(), p.a) * p.t + vertices(colon(), p.b) * (1 - p.t);
}

void CurveGenerator::handleCriticalVertices()
{
    auto critical_points = findCriticalPoints();
    for(int i = 0; i < critical_points.size(); i++)
    {
        Curve try_curve_1, try_curve_2;
        const CriticalPointInfo& info = critical_points[i];
        assert(info.points[0] > 0);

        try_curve_1.push_back(curve[info.points[0] - 1]);
        try_curve_2.push_back(curve[info.points[0] - 1]);
        for(int j = 0; j < info.points.size(); j++)
        {
            try_curve_1.push_back(curve[info.points[j]]);
        }
        assert(info.points[info.points.size() - 1] + 1 < curve.size());
        try_curve_1.push_back(curve[info.points[info.points.size() - 1] + 1]);

        Point p;
        p.a = info.move_to_index;
        p.b = -1;
        p.desiredCurvature = curve[info.points[0]].desiredCurvature;
        p.lastCurvature = computeMeanCurvature(info);
        p.t = 1;
        for(int j = 0; j < info.points.size(); j++)
        {
            if(curve[info.points[j]].is_control_point)
            {
                p.is_control_point = true;
                p.control_points = merge(p.control_points, curve[info.points[j]].control_points);
            }
        }
        try_curve_2.push_back(p);
        try_curve_2.push_back(curve[info.points[info.points.size() - 1] + 1]);

        double length1 = computeLength(try_curve_1);
        double length2 = computeLength(try_curve_2);

        if(length2 < length1)
        {
            for(int j = 0; j < info.points.size(); j++)
            {
                curve[info.points[j]].a = try_curve_2[1].a;
                curve[info.points[j]].b = try_curve_2[1].b;
                curve[info.points[j]].t = try_curve_2[1].t;
                curve[info.points[j]].desiredCurvature = try_curve_2[1].desiredCurvature;
                curve[info.points[j]].lastCurvature = try_curve_2[1].lastCurvature;
            }
        }
    }

    //merge same points
    int prev_vertex = -1;
    for(auto iter = curve.begin(); iter != curve.end(); ++iter)
    {
        if(isVertex(*iter))
        {
            if(getVertex(*iter) == prev_vertex)
            {  
                if(iter->is_control_point)
                {
                    auto iter_prior = iter - 1;
                    iter_prior->is_control_point = true;
                    iter_prior->control_points = merge(iter_prior->control_points, iter->control_points);
                }
                iter = curve.erase(iter);
                --iter;
            }
            else
            {
                prev_vertex = getVertex(*iter);
            }
        }
    }
}

std::vector<CurveGenerator::CriticalPointInfo> CurveGenerator::findCriticalPoints()
{
    int prev_moving_to = -1;
    std::vector<int> points;
    std::vector<CriticalPointInfo> result;
    for(int i = 1; i < curve.size(); i++)
    {
        if(isVertex(curve[i]))
        {
            if(prev_moving_to >= 0)
            {
                CriticalPointInfo info;
                info.move_to_index = prev_moving_to;
                info.points = points;
                result.push_back(info);
                points.clear();
                prev_moving_to = -1;
            }
            continue;
        }
        if(curve[i].a == prev_moving_to || curve[i].b == prev_moving_to)
        {
            points.push_back(i);
        }
        else
        {
            if(prev_moving_to >= 0)
            {
                CriticalPointInfo info;
                info.move_to_index = prev_moving_to;
                info.points = points;
                result.push_back(info);
            }
            points.clear();
            if(curve[i - 1].a == curve[i].a || curve[i - 1].a == curve[i].b)
            {
                prev_moving_to = curve[i - 1].a;
                points.push_back(i - 1);
                points.push_back(i);
            }
            else if(curve[i - 1].b == curve[i].a || curve[i - 1].b == curve[i].b)
            {
                prev_moving_to = curve[i - 1].b;
                points.push_back(i - 1);
                points.push_back(i);
            }
            else
            {
                prev_moving_to = -1;
            }
        }

    }
    return result;
}

double CurveGenerator::computeMeanCurvature(const CriticalPointInfo &info)
{
    double result = 0;
    for(int i = 0; i < info.points.size();i++)
    {
        result += curve[info.points[i]].lastCurvature;
    }
    return result / info.points.size();
}

std::vector<int> CurveGenerator::merge(const std::vector<int> &a, const std::vector<int> &b)
{
    std::vector<int> result = a;
    for(int i = 0 ; i < b.size(); i++)
    {
        bool existed = false;
        for(int j = 0; j < a.size(); j++)
        {
            if(b[i] == a[j])
            {
                existed = true;
                break;
            }

        }
        if(existed == false)
        {
            result.push_back(b[i]);
        }
    }
    return result;
}
