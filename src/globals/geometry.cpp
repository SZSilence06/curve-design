#include "geometry.h"
#include "math.h"
#include <zjucad/matrix/colon.h>
#include <vector>
#include <limits>

//get 2D angle from 2d coordinate. Range from [0, 2*PI).
double get_2d_angle(double x, double y)
{
    if(x == 0)
    {
        if(y > 0)
        {
            return PI / 2;
        }
        else if(y < 0)
        {
            return 3 * PI / 2;
        }
        return 0;
    }
    if(x > 0)
    {
        if( y >= 0)
        {
            return atan( y / x);
        }
        return atan(y / x) + PI * 2;
    }
    return atan(y / x) + PI;
}

//Transform 3D triangle to 2D. A will be the original point.
void tri3D_to_tri2D(const matrixr_t &a,const matrixr_t &b,const matrixr_t &c,
                    matrixr_t &b1,matrixr_t &c1)
{
    real_t ab = norm(b-a);
    real_t ac = norm(c-a);
    real_t bc = norm(c-b);
    real_t theta = acos((ab*ab+ac*ac-bc*bc)/(2*ab*ac));

    b1 = matrixr_t(2,1);
    c1 = matrixr_t(2,1);

    b1[0] = ab;
    b1[1] = 0;
    c1[0] = ac * cos(theta);
    c1[1] = ac * sin(theta);
}

//Transform 2D barycenter to coordinates
void bary2D_to_coor2D(const matrixr_t &a,const matrixr_t &b,const matrixr_t &c,
                      const matrixr_t &bary,matrixr_t &coor)
{
    coor = bary[0]*a + bary[1]*b + bary[2]*c;
}

//Test whether AB and CD have intersections.
//if ray == true, then cd is a ray whose direction is from c to d
//return 0: no intersection;
//return 1: intersect in the lines;
//return 2: intersect on point A
//return 3: intersect on point B
//return 4: intersect on point C
//return 5: intersect on point D
int intersect(const matrixr_t &a,const matrixr_t &b,
               const matrixr_t &c,const matrixr_t &d,
               bool ray)
{
    matrixr_t ab = b - a;
    matrixr_t ac = c - a;
    matrixr_t cd = d - c;
    matrixr_t temp(2,2);
    temp(colon(),0) = ab;
    temp(colon(),1) = -cd;

    real_t det = temp(0,0) * temp(1,1) - temp(0,1) * temp(1,0);
    if(ZERO(det)){
        return 0;
    }
    matrixr_t inv(2,2);
    matrixr_t T;
    inv(0,0) = temp(1,1);
    inv(0,1) = -temp(0,1);
    inv(1.0) = -temp(1,0);
    inv(1,1) = temp(0,0);
    inv /= det;
    T =  inv * ac;
    if(ray){
        if(T[0]<0 || T[0] > 1 || T[1]<0){
            return 0;
        }
    }
    else{
        if(T[0]<0 || T[0] > 1 || T[1]<0 || T[1]>1){
            return 0;
        }
    }
    if(ZERO(T[0])){
        return 2;
    }
    if(ZERO(T[0]-1)){
        return 3;
    }
    if(ZERO(T[1])){
        return 4;
    }
    if(!ray && ZERO(T[1]-1)){
        return 5;
    }
    return 1;
}

//Test whether a and b are on same side of the given curve.
bool is_on_same_side(const matrixr_t &curve,const matrixr_t &a,const matrixr_t &b){
    int cninter = 0,ret,i;
    if(ret = intersect(a,b,curve(colon(),1),curve(colon(),0),true)){
        cninter++;
        if(ret == 4){          //on the end point
            if(curve.size() == 2){
                return false;
            }
            cninter--;
        }
    }
    for(i=1;i<curve.size(2)-2;i++){
        if(ret = intersect(a,b,curve(colon(),i),curve(colon(),i+1),false)){
            cninter++;
            if(ret == 5){
                cninter--;
            }
        }
    }
    if(curve.size(2) >2 && (ret = intersect(a,b,curve(colon(),curve.size(2)-2),curve(colon(),curve.size(2)-1),true))){
        cninter++;
    }
    if(cninter %2 ){
        return false;
    }
    return true;
}

//Test whether point p is on seg AB
//return 0: not on seg;
//return 1: on point A;
//return 2: on point B;
//return 3: inside the seg;
int is_on_seg(const matrixr_t &a,const matrixr_t &b,const matrixr_t p)
{
    std::vector<real_t> testa,testb,testp;
    for(int i=0;i<2;i++){
        testa.push_back(a[i]);
        testb.push_back(b[i]);
        testp.push_back(p[i]);
    }
    matrixr_t ab = b - a;
    matrixr_t ap = p - a;
    matrixr_t bp = p - b;
    if(norm(ap) == 0){
        return 1;
    }
    if(norm(bp) == 0){
        return 2;
    }
    real_t cos_theta = dot(ab,ap) / (norm(ab)*norm(ap));
    real_t cos_theta2 = dot(ab,bp) / (norm(ab)*norm(bp));
    real_t theta = acos(fabs(cos_theta));
    real_t theta2 = acos(fabs(cos_theta2));
    if(fabs(theta) > 0.01 && fabs(theta2) > 0.01){
        return 0;
    }
    real_t t = ap[0] / ab[0];
    if(ZERO(t)){
        return 1;
    }
    if(ZERO(t-1)){
        return 2;
    }
    if(t<0 || t>1){
        return 0;
    }
    return 3;
}

//Test whether point p is inside a poly.
//Note: If p is on the edge or vertex, this function also returns true
bool is_inside_poly(const matrixr_t &poly,const matrixr_t &p){
    matrixr_t a(2,1);
    a[0] = 999999;
    a[1] = p[1];

    int cnInter = 0;
    for(int i=0;i<poly.size(2)-1;i++){
        if(is_on_seg(poly(colon(),i),poly(colon(),i+1),p)){
            return true;
        }
        int inter;
        if(inter = intersect(p,a,poly(colon(),i),poly(colon(),i+1),false)){
            cnInter++;
            if(inter == 5){       //intersects on the tail of the edge
                cnInter--;
            }
        }
    }

    if(is_on_seg(poly(colon(),poly.size(2)-1),poly(colon(),0),p)){
        return true;
    }
    int inter;
    if(inter = intersect(p,a,poly(colon(),poly.size(2)-1),poly(colon(),0),false)){
        cnInter++;
        if(inter == 5){       //intersects on the tail of the edge
            cnInter--;
        }
    }

    if(cnInter % 2){
        return true;
    }
    return false;
}

//Compute area of a triangle
real_t compute_area(const matrixr_t &a, const matrixr_t &b, const matrixr_t &c)
{
    matrixr_t ab = b - a;
    matrixr_t ac = c - a;
    return 0.5 * (norm(cross(ab,ac)));
}

//Tool function used by compute_volume();
float SignedVolumeOfTriangle(const matrixr_t &a, const matrixr_t &b, const matrixr_t &c) {
    real_t v321 = c[0] * b[1] * a[2];
    real_t v231 = b[0] * c[1] * a[2];
    real_t v312 = c[0] * a[1] * b[2];
    real_t v132 = a[0] * c[1] * b[2];
    real_t v213 = b[0] * a[1] * c[2];
    real_t v123 = a[0] * b[1] * c[2];
    return (1.0f/6.0f) * (-v321 + v231 + v312 - v132 - v213 + v123);
}

//Compute volume of a triangle mesh
real_t compute_volume(const matrixr_t &V, const matrixs_t &T)
{
    real_t sum = 0;
    for(int i = 0; i < T.size(2); i++)
    {
        sum += SignedVolumeOfTriangle(V(colon(),T(0,i)), V(colon(),T(1,i)), V(colon(),T(2,i)));
    }
    return fabs(sum);
}

//Compute barycenter coordinates of the point p on trinangle abc.
//return 1 if p is inside the triangle, and 0 instead.
int barycentric(const matrixr_t &a, const matrixr_t &b,
                const matrixr_t &c, const matrixr_t &p,
                matrixr_t &bary)
{
    bary = matrixr_t(3,1);
    matrixr_t ab = b - a;
    matrixr_t ac = c - a;
    matrixr_t bc = c - b;
    matrixr_t ap = p - a;
    matrixr_t bp = p - b;
    matrixr_t cp = p - c;
    real_t Sabc = norm(cross(ab,ac));
    real_t Spab = norm(cross(ab,ap));
    real_t Spac = norm(cross(ac,ap));
    real_t Spbc = norm(cross(bc,bp));
    if(fabs(Sabc-Spab-Spac-Spbc)<1e-10){
        bary[0] = Spbc/Sabc;
        bary[1] = Spac/Sabc;
        bary[2] = Spab/Sabc;
        return 1;
    }
    return 0;
}

//compute intersection between a ray and a triangle abc.
//return the distance. If no intersection, return -1.
real_t compute_intersection_triangle_ray(const matrixr_t &a, const matrixr_t &b, const matrixr_t &c,
                                      const matrixr_t &p, const matrixr_t &dir)
{
    matrixr_t ab = b - a;
    matrixr_t ac = c - a;
    matrixr_t plane_normal = cross(ab, ac);
    plane_normal = plane_normal / norm(plane_normal);

    matrixr_t ap = p - a;
    real_t cos_theta = dot(ap / norm(ap), plane_normal);
    real_t dist_p_to_plane = norm(ap) * cos_theta;
    matrixr_t proj_p = p - dist_p_to_plane * plane_normal;

    matrixr_t pprojp = proj_p - p;
    real_t cos_theta_projp_p_dir = dot(pprojp / norm(pprojp), dir / norm(dir));
    real_t dist = fabs(dist_p_to_plane) / cos_theta_projp_p_dir;
    if(dist < 0)
    {
        return -1;
    }
    matrixr_t intersect_point = p + dist * dir / norm(dir);
    matrixr_t bary;
    if(barycentric(a,b,c,intersect_point,bary))
    {
        return dist;
    }
    return -1;
}

//Generate a ray direction, given the coordinate x,y in screen space.
//fov is represented in degree.
//The origin point is in the left bottom corner.
void generate_ray_dir(const matrixr_t &eye, const matrixr_t& lookAt, const matrixr_t &up,
                      double fov, double x, double y, double screen_width, double screen_height,
                      matrixr_t &output_dir)
{
    matrixr_t front = (lookAt - eye) / norm(lookAt - eye);
    matrixr_t up_new = up / norm(up);
    matrixr_t right = cross(front, up_new);

    double sx = x / screen_width;
    double sy = y /screen_height;
    double fovScale = tan(fov * 0.5 * PI / 180) * 2;

    matrixr_t r = right * ((sx - 0.5) * fovScale) * screen_width / screen_height;
    matrixr_t u = up_new * ((sy - 0.5) * fovScale);

    output_dir = r + u + front;
    output_dir = output_dir / norm(output_dir);
}

//Pick vertex from the screen. If failed to pick, return -1.
//Param: 'error' shows the maximum distance from the vertex to be picked to the intersection between the  \
//         eye ray and the mesh. If the distance is bigger than 'error', the vertex will not be picked.
int pick_mesh_vertex(const matrixr_t &vertices, const matrixs_t &triangles, const matrixr_t &eye,
                     const matrixr_t& lookAt, const matrixr_t &up, double fov,
                     double x, double y, double screen_width, double screen_height,
                     double error)
{

    matrixr_t ray_dir;

    generate_ray_dir(eye, lookAt, up, fov, x, y, screen_width, screen_height, ray_dir);

    double min_dist = std::numeric_limits<double>::max();
    for(int i = 0; i < triangles.size(2); i++)
    {
        double dist = compute_intersection_triangle_ray(vertices(colon(),triangles(0,i)),
                                          vertices(colon(),triangles(1,i)),
                                          vertices(colon(),triangles(2,i)),
                                          eye, ray_dir);
        if(dist < 0 || dist >= min_dist)
        {
            continue;
        }
        min_dist = dist;
    }

    if(min_dist == std::numeric_limits<double>::max())
    {
        return -1;   //The eye ray does not intersect with the mesh.
    }

    matrixr_t intersection = eye + min_dist * ray_dir;
    int picked_vertex = -1;
    min_dist = std::numeric_limits<double>::max();
    for(int i = 0; i < vertices.size(2); i++)
    {
        auto& vertex = vertices(colon(), i);
        double dist = norm(vertex - intersection);
        if(dist < min_dist && dist < error)
        {
            min_dist = dist;
            picked_vertex = i;
        }
    }
    return picked_vertex;
}

//transform barycenter to coordinate
void bary_to_coor(const matrixr_t& vertices, const matrixs_t& triangles, const matrixr_t& bary,
                  matrixr_t& coor)
{
    matrixr_t triangle = vertices(colon(), triangles(colon(), bary[2]));

    coor = bary[0] * triangle(colon(), 0) + bary[1] * triangle(colon(), 1)
            + (1 - bary[0] - bary[1]) * triangle(colon(), 2);
}
