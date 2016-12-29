#pragma once

#include <zjucad/matrix/matrix.h>

typedef double real_t;
typedef zjucad::matrix::matrix<real_t> matrixr_t; // real                                                                                                                                                                                     
typedef zjucad::matrix::matrix<int>    matrixi_t; // int                                                                                                                                                                                      
typedef zjucad::matrix::matrix<size_t> matrixs_t;
typedef zjucad::matrix::matrix<bool>   matrixb_t;

//return the index of the triangle.
//if there is no intersection, return -1
//! @param s, d: 3x1, a point
//!
//!
int project(const matrixr_t &V, const matrixi_t &F, // triangular mesh
            const matrixr_t &FN, //face normal list
            const matrixr_t &s,  const matrixr_t &d,  //s: starting point; d:direction
            matrixr_t &triplet); //barycentric coordinates of the intersection. If there is no intersection, triplet[2] = -1.

//project a point to a triangle,and returns the distance
real_t project2triangle(const matrixr_t &a,const matrixr_t &b,const matrixr_t &c,       //triangle
                     const matrixr_t &p,            //point to project
                     real_t &barya,real_t &baryb      // output barycenter coordinates
                     );




