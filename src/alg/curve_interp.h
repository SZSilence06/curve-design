#ifndef HJ_CURVE_INTERP_H_
#define HJ_CURVE_INTERP_H_

#include "conf.h"

//! @brief approximated curve interpolation in alg.pdf.
int curve_interp(const matrixr_t &V, const matrixs_t &T, // triangular mesh                 
                 const matrixr_t &P, // points picked from the mesh
                 real_t w_m, real_t w_s, real_t L, // parameters
                 matrixr_t &Q,                     // output PWL curve
                 matrixs_t &control_point_pos,
                 bool is_loop
                 );

#endif
