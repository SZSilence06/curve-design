#ifndef SZY_CONF_H
#define SZY_CONF_H

#include<zjucad/matrix/matrix.h>
#include<zjucad/matrix/itr_matrix.h>
#include<zjucad/matrix/conversion.h>
#include<zjucad/matrix/io.h>

#define SZY_EPS 1e-8
typedef double real_t;
typedef zjucad::matrix::matrix<real_t> matrixr_t; // real
typedef zjucad::matrix::matrix<int>    matrixi_t; // int
typedef zjucad::matrix::matrix<size_t> matrixs_t;
typedef zjucad::matrix::matrix<bool>   matrixb_t;

#endif
