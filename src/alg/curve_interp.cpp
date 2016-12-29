#include "curve_interp.h"

#include <iostream>
#include <eigen3/Eigen/Sparse>

using namespace std;
using namespace zjucad::matrix;

// TODO: assume uniform for now
void build_LLSQ(const matrixr_t &Q, Eigen::SparseMatrix<real_t> &L,bool is_loop)
{
  std::vector<Eigen::Triplet<double> > triples;
  for (size_t vi = 1; vi < Q.size(2)-1; ++vi) { // TODO: open loop only for now
    triples.push_back(Eigen::Triplet<double>(vi-1, vi-1, -0.5));
    triples.push_back(Eigen::Triplet<double>(vi-1, vi, 1.0));
    triples.push_back(Eigen::Triplet<double>(vi-1, vi+1, -0.5));
  }
  //WKY Adds
  if(is_loop){
    triples.push_back(Eigen::Triplet<double>(Q.size(2)-2,Q.size(2)-2,-0.5));
    triples.push_back(Eigen::Triplet<double>(Q.size(2)-2,Q.size(2)-1,1.0));
    triples.push_back(Eigen::Triplet<double>(Q.size(2)-2,1,-0.5));
    L.resize(Q.size(2)-1,Q.size(2));
  }
  else{
    L.resize(Q.size(2)-2, Q.size(2));
  }
  L.setFromTriplets(triples.begin(), triples.end());
}

void smoothing(matrixr_t &Q, const matrixs_t &p, real_t w_s,bool is_loop)
{
  Eigen::SparseMatrix<real_t> L, LTL;
  build_LLSQ(Q, L, is_loop);
  LTL = L.transpose()*L;
  matrixs_t P = zeros<size_t>(Q.size(2), 1);
  P(p) = 1;
  for(size_t itr = 0; itr < Q.size(2)*10; ++itr) {
    double max_step = 0;
    for(size_t i = 0; i < Q.size(2); ++i) {
      if(P[i] == 1) continue;
      double diag = 0;
      matrix<real_t> rhs = zeros<real_t>(3, 1);
      for (Eigen::SparseMatrix<double>::InnerIterator it(LTL, i); it; ++it) {
        if(it.index() == i)
          diag = it.value();
        else
          rhs -= it.value()*Q(colon(), it.index());
      }
      if(fabs(diag) < 1e-8) {
        std::cerr << "small diag: " << diag << endl;
        continue;
      }
      matrixr_t step = rhs/diag - Q(colon(), i);
      const double max0 = max(fabs(step));
      if(max_step < max0) max_step = max0;
      Q(colon(), i) += step*1.3;
    }
    if(max_step < 1e-8) {
      std::cerr << "# terminate the iteration: " << itr << endl;
      break;
    }
  }
}

int curve_interp(const matrixr_t &V, const matrixs_t &T, // triangular mesh
                 const matrixr_t &P, // points picked from the mesh
                 real_t w_m, real_t w_s, real_t L, // parameters
                 matrixr_t &Q,                     // output PWL curve
                 matrixs_t &control_point_pos,
                 bool is_loop
                 )
{
  if(P.size() < 2) {
    return __LINE__;
  }
  matrixs_t p = zeros<size_t>(P.size(2), 1);
  matrixr_t Q0(3, P.size(2)); // straight line connecting P
  for(size_t i = 0; i < P.size(2); ++i) {
    matrixr_t barycenter = P(colon(), i);
    barycenter[2] = 1-barycenter[0]-barycenter[1];
    Q0(colon(), i) = V(colon(), T(colon(), size_t(floor(P(2, i)+0.5))))*barycenter;
    if(i > 0) {
      const real_t length = norm(Q0(colon(), i) - Q0(colon(), i-1));
      size_t seg_num = size_t(floor(length/L + 0.5));
      if(seg_num == 0) seg_num = 1;
      p[i] = p[i-1] + seg_num;
    }
  }
  matrixr_t Q1(3, p[P.size(2)-1]+1);
  for(size_t i = 1; i < p.size(); ++i) { // for each segment
    for(size_t s = 0; s <= p[i]-p[i-1]; ++s) {
      const real_t t = real_t(s)/(p[i]-p[i-1]);
      Q1(colon(), p[i-1]+s) = (1-t)*Q0(colon(), i-1) + t*Q0(colon(), i);
    }
  }
  Q = Q1;
  smoothing(Q, p, w_s,is_loop);
  control_point_pos = p;
  return 0;
}
