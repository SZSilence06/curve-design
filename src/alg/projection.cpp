#include "projection.h"
#include "../globals/geometry.h"
#include <limits>
//#include "operation.h"

using namespace zjucad::matrix;

int project(const matrixr_t &V, const matrixi_t &F, // triangular mesh
            const matrixr_t &FN, const matrixr_t &s, //
            const matrixr_t &d, matrixr_t &triplet)
{
    int index = -1;
    const double nd = norm(d);
    assert(nd > 1e-6);
    const matrixr_t dn = d / nd;
    matrixr_t p(3), bary(3);
    double min_dist = std::numeric_limits<double>::max();

    for (int fi = 0; fi < F.size(2); ++fi){
        const matrixr_t fn = FN(colon(), fi);
        const double cos_angle = dot(dn, fn);
        if (fabs(cos_angle) < 1e-6){
            continue;
        }
        const double dist = -dot(s - V(colon(), F(0, fi)), fn) / cos_angle;
        p = s + dist * dn;
        if (barycentric(V(colon(), F(0, fi)),
            V(colon(), F(1, fi)), V(colon(), F(2, fi)), p, bary)){
            if (min_dist > fabs(dist)){
                index = fi;
                min_dist = fabs(dist);
                triplet = bary;
            }
        }
    }
    if (index < 0){
        triplet[2] = -1;
    }
    triplet[2] = index;
    return index;

    /*double min_dist = std::numeric_limits<double>::max();
    for(int i=0;i<F.size(2);i++){
        if(i==183){
            int test = 1;
        }
        matrixr_t bary2(3,1);
        real_t dist = project2triangle(V(colon(),F(0,i)),V(colon(),F(1,i)),V(colon(),F(2,i)),s,bary2[0],bary2[1]);
        bary2[2] = i;
        if(dist<min_dist){
            min_dist = dist;
            triplet = bary2;
        }
    }
    std::vector<real_t> test;
    for(int i=0;i<3;i++){
        test.push_back(triplet[i]);
    }
    return triplet[2];*/
}


real_t dist_p2line(const matrixr_t &a,const matrixr_t &b,const matrixr_t &p,real_t &barya){
    matrixr_t ab = b-a;
    matrixr_t ap = p-a;
    real_t cos_theta;
    if(norm(ap)==0){
        cos_theta = 0;
    }
    else{
        cos_theta = dot(ap/norm(ap),ab/norm(ab));
    }
    real_t l = norm(ap);
    real_t l2 = l*cos_theta;
    if(l2<0 || l2 > norm(ab)){
        if(l2<0){
            barya = 1;
            return norm(ap);
        }
        barya = 0;
        return norm(p-b);
    }
    barya = 1 - l2/norm(ab);
    return l*norm(cross(ap/norm(ap),ab/norm(ab)));
}


//project a point to a triangle,and returns the distance
real_t project2triangle(const matrixr_t &a,const matrixr_t &b,const matrixr_t &c,       //triangle
                     const matrixr_t &p,            //point to project
   real_t &barya,real_t &baryb      // output barycenter coordinates
                     )
{
    matrixr_t fn = cross(a-b,a-c);
    fn = fn/norm(fn);
    matrixr_t ap = p - a;
    real_t cos_theta;
    if(fabs(norm(ap)) == 0){
        cos_theta = 0;
    }
    else{
        cos_theta = dot(fn,ap/norm(ap));
    }
    real_t distance = -norm(ap) * cos_theta;
    if(fabs(distance)<1e-10){
        distance = 0;
    }
    matrixr_t p2 = p + distance*fn;
    matrixr_t bary(3,1);
    if(barycentric(a,b,c,p2,bary)){
        barya = bary(0,0);
        baryb = bary(1,0);
        double baryc = bary(2,0);
        barycentric(a,b,c,p2,bary);
        return fabs(distance);
    }
    real_t bab,bac,bbc;
    real_t dab = dist_p2line(a,b,p,bab);
    real_t dac = dist_p2line(a,c,p,bac);
    real_t dbc = dist_p2line(b,c,p,bbc);
    if(dab <= dac && dab<=dbc){
        barya = bab;
        baryb = 1 - bab;
        return dab;
    }
    if(dac <= dbc){
        barya = bac;
        baryb = 0;
        return dac;
    }
    barya = 0;
    baryb = bbc;
    return dbc;
}




