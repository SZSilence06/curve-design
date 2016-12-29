#ifndef HJ_UTIL_H_
#define HJ_UTIL_H_

#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include <zjucad/matrix/matrix.h>
#include <hjlib/math/tblas.h>
#include <hjlib/math/quaternion.h>

#undef min
#undef max

template <typename E1, typename E2>
zjucad::matrix::matrix_expression<E1> &bounding_box(zjucad::matrix::matrix_expression<E1> &bb,
										 const zjucad::matrix::matrix_expression<E2> &v)
{
	using namespace zjucad::matrix;
	bb() = zeros<typename E1::value_type>(3, 2);
	if(!v().size()) return bb;

	bb()(0, 0) = min(v()(0, colon()));
	bb()(1, 0) = min(v()(1, colon()));
	bb()(2, 0) = min(v()(2, colon()));
	bb()(0, 1) = max(v()(0, colon()));
	bb()(1, 1) = max(v()(1, colon()));
	bb()(2, 1) = max(v()(2, colon()));
	return bb;
}

template <typename E1, typename E2>
typename E1::value_type bounding_sphere(zjucad::matrix::matrix_expression<E1> &center,
					   const zjucad::matrix::matrix_expression<E2> &bb)
{
	using namespace zjucad::matrix;
	center() = (bb()(colon(), 0)+bb()(colon(), 1))/2.0;
	return norm(bb()(colon(), 0)-bb()(colon(), 1))/2.0;
}

template <typename T1, typename T2, typename T3>
void vertex_normal(zjucad::matrix::matrix<T1> &n, const zjucad::matrix::matrix<T2> &v, const zjucad::matrix::matrix<T3> &t, double eps = 1e-10)
{
    const T3 vn = max(t) +1, tn = t.size(2);
    if(n.size(2) != vn) n.resize(3, vn);
	std::fill(&n[0], &n[0]+n.size(), 0.0f);
	T1 e[2][3], normal[3];

    const T3 *pt = t.begin();
	const T2 *pv = &v[0];
	T1 *pn = &n[0], *pnj;
	T3 i, j, k;
    for(i = 0; i < tn; ++i, pt+=3) {
		const T1 *pvi[3] = {pv+pt[0]*3, pv+pt[1]*3, pv+pt[2]*3};
		for(j = 0; j < 3; ++j) {
			e[0][j] = pvi[1][j]-pvi[0][j];
			e[1][j] = pvi[2][j]-pvi[0][j];
		}
		hj::tblas::cross(e[0], e[1], normal);
		for(j = 0; j < 3; ++j) {
			pnj = pn+pt[j]*3;
			for(k = 0; k < 3; ++k)
				pnj[k] += normal[k];
		}
    }
	for(i = 0; i < vn; ++i, pn+=3) {
		T1 len = hj::tblas::dot<T1, 3>(pn, pn);
		if (len > eps) {
			len = sqrt(len);
			for(j = 0; j < 3; ++j) pn[j] /= len;
        }
		else {
			std::fill(pn, pn + 3, 0);
        }
	}
}

template <typename T1, typename T2, typename T3>
void face_normal(zjucad::matrix::matrix<T1> &n, const zjucad::matrix::matrix<T2> &v, const zjucad::matrix::matrix<T3> &t, double eps = 1e-10)
{
    const T3 tn = t.size(2);
    if(n.size(2) != tn) n.resize(3, tn);
	T1 e[2][3], normal[3];

    const T3 *pt = t.begin();
	const T2 *pv = &v[0];
	T1 *pn = &n[0];
	T3 i, j;
    for(i = 0; i < tn; ++i, pt+=3, pn+=3) {
		const T1 *pvi[3] = {pv+pt[0]*3, pv+pt[1]*3, pv+pt[2]*3};
		for(j = 0; j < 3; ++j) {
			e[0][j] = pvi[1][j]-pvi[0][j];
			e[1][j] = pvi[2][j]-pvi[0][j];
		}
		hj::tblas::cross(e[0], e[1], normal);
		T1 len = hj::tblas::dot<T1, 3>(normal, normal);
		if (len > eps) {
			len = sqrt(len);
			for(j = 0; j < 3; ++j) pn[j] = normal[j]/len;
        }
		else {
			std::fill(pn, pn+3, 0);
        }
    }
}

// array[i][j] == e(i, j)
template <typename E, typename T, int N>
void convert(const zjucad::matrix::matrix_expression<E> &e, T arr[][N])
{
	for(int i = 0; i < e().size(1); ++i)
		for(int j = 0; j < e().size(2); ++j)
			arr[i][j] = e()(i, j);
}

// e must be prealloc to proper size
template <typename E, typename T, int N>
void convert(const T arr[][N], zjucad::matrix::matrix_expression<E> &e)
{
	for(int i = 0; i < e().size(1); ++i)
		for(int j = 0; j < e().size(2); ++j)
			e()(i, j) = arr[i][j];
}

template <typename T1, typename T2>
inline void convert(const std::set<T1> &s, zjucad::matrix::matrix<T2> &m) {
	m.resize(static_cast<int>(s.size()));
	copy(s.begin(), s.end(), m.begin());
}

template <typename T1, typename T2>
inline void convert(const zjucad::matrix::matrix<T1> &m, std::set<T2> &s) {
	s.clear();
	for(int i = 0; i < m.size(); ++i)
		s.insert(m[i]);
}

template <typename T1, typename T2>
inline void convert(const std::vector<T1> &v, zjucad::matrix::matrix<T2> &m) {
	m.resize(int(v.size()));
	copy(v.begin(), v.end(), m.begin());
}

template <typename C>
int find(const C &con, const typename C::value_type &v) {
	typename C::const_iterator i = std::find(con.begin(), con.end(), v);
	if(i == con.end()) return -1;
	return int(i-con.begin());
}

template <typename Pred, typename C>
void order_hit_records(int hits, unsigned int buffer[], C &ob)
{
	ob.resize(hits);
	unsigned int *ptr = buffer;
	for(int i = 0; i < hits; ++i) {
		ob[i] = ptr;
		ptr += 3+ptr[0];
	}
	sort(ob.begin(), ob.end(), Pred());
}

template <typename T1, typename T2, typename T3>
T3 &multi_m44_v3s(const T1 &m44, const T2 &a, T3 &b)
{
	using namespace zjucad::matrix;
	b = m44(colon(0, 2), colon(0, 2))*a
		+ m44(colon(0, 2), colon(3, 3))*ones<typename T1::value_type>(1, a.size(2));
	for(int i = 0; i < b.size(2); ++i)
		b(colon(), i) /= dot(b(colon(), i), m44(colon(3, 3), colon(0, 2)))+m44[15];
	return b;
}

// binary IO
template <typename IS, typename T>
inline void read_raw_val(IS &is, T &data) {
	is.read((char *)&data, sizeof(T));
}

template <typename IS, typename Con>
inline void read_array(IS &is, Con &data) {
	size_t size;
	read_raw_val(is, size);
	data.resize(size);
	is.read((char *)&data[0], typename IS::streamsize(sizeof(typename Con::value_type)*size));
}

template <typename OS, typename T>
inline void write_raw_val(OS &os, const T &data) {
	os.write((const char *)&data, sizeof(T));
}

template <typename OS, typename T>
inline void write_array(OS &os, const T data[], size_t size) {
	write_raw_val(os, size);
	os.write((const char *)data, typename OS::streamsize(sizeof(T)*size));
}

template <typename T1, typename T2, typename T3>
static void mult_ge_di(const T1 &A, const T2 &B, T3 &C)
{
	using namespace zjucad::matrix;
	assert(A.size(2) == B.size());
	C.resize(A.size(1), A.size(2));
	for(int i = 0; i < B.size(); ++i)
		C(colon(), i) = A(colon(), i)*B[i];
}

template <typename T1, typename T2, typename T3>
static void mult_di_ge(const T1 &A, const T2 &B, T3 &C)
{
	using namespace zjucad::matrix;
	assert(A.size() == B.size(1));
	C.resize(B.size(1), B.size(2));
	for(int i = 0; i < A.size(); ++i)
		C(i, colon()) = B(i, colon())*A[i];
}

#include <hjlib/math/blas_lapack.h>
#include <zjucad/matrix/lapack.h>
#include <zjucad/matrix/io.h>
#include <iostream>

inline int rank(const zjucad::matrix::matrix<double> &A, double eps = 1e-5)
{
	zjucad::matrix::matrix<double> A0 = A, U, S, VT;
	zjucad::matrix::svd(A0, U, S, VT);
	int i, rtn = -1;
	for(i = 0; i < S.size(1); ++i) {
		std::cout << i << " " << S(i, i) << std::endl;
		if(rtn < 0 && S(i, i)/S(0, 0) < eps)
			rtn = i;
	}
	return rtn;
}

template <typename T1, typename T2, typename T3>
zjucad::matrix::matrix<T3> &vert_cat(const zjucad::matrix::matrix<T1> &A, const zjucad::matrix::matrix<T2> &B, zjucad::matrix::matrix<T3> &C)
{
	using namespace zjucad::matrix;
	assert(A.size(2) == B.size(2));
	C.resize(A.size(1)+B.size(1), A.size(2));
	C(colon(0, A.size(1)-1), colon(0, A.size(2)-1)) = A;
	C(colon(A.size(1), C.size(1)-1), colon(0, A.size(2)-1)) = B;
	return C;
}

template <typename T>
inline zjucad::matrix::matrix<T> upper2sym(const zjucad::matrix::matrix<T> &upper, int dim)
{
	using namespace zjucad::matrix;
	matrix<T> rtn = zeros<T>(dim, dim);
	int i, base;
	for(i = 0, base = 0; i < dim; ++i) {
		rtn(colon(0, i), colon(i, i)) = upper(colon(base, base+i));
		base += i+1;
	}
	rtn = temp(rtn+trans(rtn))/2;
	return rtn;
}

template <typename T>
static inline zjucad::matrix::matrix<T> sym2upper(const zjucad::matrix::matrix<T> &sym, int dim)
{
	using namespace zjucad::matrix;
	matrix<T> rtn = zeros<T>(dim*(dim+1)/2, 1);
	int i, base;
	for(i = 0, base = 0; i < dim; ++i) {
		rtn(colon(base, base+i)) = sym(colon(0, i), colon(i, i));
		base += i+1;
	}
	return rtn;
}


template <typename V>
inline int find(int a, const V &vec)
{
	typename V::const_iterator i = find(vec.begin(), vec.end(), a);
	if(i == vec.end()) return -1;
	return static_cast<int>(i-vec.begin());
}

template <typename T>
bool inv_by_svd(zjucad::matrix::matrix<T> &A, T eps = 1e-7)
{
	using namespace zjucad::matrix;
	matrix<T> U, S, VT;
	svd(A, U, S, VT);
	int rank;
	for(rank = 0; rank < S.size(1); ++rank) {
		if(S(rank, rank) < eps)
			break;
		S(rank, rank) = 1.0/S(rank, rank);
	}
	--rank;
	if(rank < 0) return false;
	A = U*temp(S*VT);
	return true;
}

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

inline bool file_exist(const char *path) {
#ifdef _WIN32
#	define STAT _stat
#else
#	define STAT stat
#endif
	struct STAT buf;
	return STAT(path, &buf) == 0
		|| errno != ENOENT;	// errno is global variable
#undef STAT
}

#endif
