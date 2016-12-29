#ifndef HJ_ROT_UTIL_H_
#define HJ_ROT_UTIL_H_

#include <cmath>
#include <zjucad/matrix/matrix.h>
#include <hjlib/math/blas_lapack.h>
#include <zjucad/matrix/lapack.h>
#include <hjlib/math/quaternion.h>

template <typename E1, typename T, typename E2>
void axis_angle2R_by_quat(const zjucad::matrix::matrix_expression<E1> &axis, T angle, zjucad::matrix::matrix_expression<E2> &R)
{
	using namespace zjucad::matrix;
	static const T pi = 3.1415926;
	const T a = angle/(2*pi);
	matrix<T> quat(4);
	assert(fabs(ceil(-0.5-a) - floor(0.5-a)) < 1e-4);
	angle += ceil(-0.5-a)*(2*pi);
	hj::quaternion::axis_angle(axis(), angle, quat);
	R().resize(3, 3);
	hj::quaternion::quat2m33<double>(quat, R());
}

template <typename E1, typename E2>
void axis_angle2R(const zjucad::matrix::matrix_expression<E1> &axis_angle, zjucad::matrix::matrix_expression<E2> &R)
{
	using namespace zjucad::matrix;
	matrix<typename E1::value_type> axis;
	typename E1::value_type theta = norm(axis_angle);
	if(theta < 1e-10) {
		R() = eye<typename E2::value_type>(3);
		return;
	}
	axis = axis_angle/theta;
	axis_angle2R(axis, theta, R());
}

template <typename T1, typename T2, typename T3>
void axis_angle2R(T1 axis, T2 angle, T3 &mat)
{
    T2 c = cos(angle);
    T2 s = sin(angle);
    T2 t = 1.0 - c;
    mat[0] = c + axis[0]*axis[0]*t;
    mat[4] = c + axis[1]*axis[1]*t;
    mat[8] = c + axis[2]*axis[2]*t;

    T2 tmp1 = axis[0]*axis[1]*t;
    T2 tmp2 = axis[2]*s;
    mat[1] = tmp1 + tmp2;
    mat[3] = tmp1 - tmp2;

    tmp1 = axis[0]*axis[2]*t;
    tmp2 = axis[1]*s;
    mat[2] = tmp1 - tmp2;
    mat[6] = tmp1 + tmp2;

    tmp1 = axis[1]*axis[2]*t;
    tmp2 = axis[0]*s;
    mat[5] = tmp1 + tmp2;
    mat[7] = tmp1 - tmp2;
}

template <typename E1, typename E2>
typename E1::value_type get_axis_angle(const zjucad::matrix::matrix_expression<E1> &R, zjucad::matrix::matrix_expression<E2> &axis, double check = 1e-5)
{
	using namespace zjucad::matrix;
	typedef typename E1::value_type value_type;
	assert(R().size(1) == 3 && R().size(2) == 3);
	assert(norm(R()*trans(R())-eye<value_type>(3)) < check);
	value_type quat[4];
	hj::quaternion::m332quat<value_type>(R(), quat);
	axis().resize(3);
	hj::quaternion::axis_angle<value_type>(quat);
	std::copy(&quat[1], &quat[1]+3, axis().begin());
	return quat[0];
}

template <typename E>
void make_right_hand(zjucad::matrix::matrix_expression<E> &R, bool trans)
{
	using namespace zjucad::matrix;
	if(trans) {
		if(dot(R()(2, colon()), cross(R()(0, colon()), R()(1, colon()))) < 0)
			R()(2, colon()) *= -1;
	}
	else {
		if(dot(R()(colon(), 2), cross(R()(colon(), 0), R()(colon(), 1))) < 0)
			R()(colon(), 2) *= -1;
	}
}

template <typename E>
const zjucad::matrix::matrix_expression<E> &polar_by_svd(zjucad::matrix::matrix_expression<E> &A)
{
	using namespace zjucad::matrix;
	matrix<typename E::value_type> U, S, VT;
	svd(A(), U, S, VT);
	make_right_hand(U, false);
	make_right_hand(VT, true);
	A() = U*VT;
	return A;
}


template <typename E1, typename E2>
void get_log_R(const zjucad::matrix::matrix_expression<E1> &R, zjucad::matrix::matrix_expression<E2> &logR)
{
	typename E2::value_type angle = get_axis_angle(R(), logR());
	logR() *= angle;
}


#endif
